/* ========================================================================== */
/* AVIS SYSTEM BENCHMARK SUITE                                                */
/* FILE: /avis_core/src/BenchmarkMatrixLoad.java                              */
/* DESCRIPTION: High-concurrency Java-to-C performance stress testing harness.*/
/* ========================================================================== */

package src;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class BenchmarkMatrixLoad {

    private static final int VECTOR_DIM = 1536;
    private static final int CONCURRENT_WORKERS = 32;
    private static final int TOTAL_STRESS_QUERIES = 1000;
    private static final String SO_RELATIVE_PATH = "bin/memory_vector_graph/memory_graph.so";

    // ==========================================================================
    // JNA STRUCT AND INTERFACE BINDINGS FOR NATIVE MEMORY ENCLAVE
    // ==========================================================================

    public interface MemoryGraphLib extends Library {
        public static class PluginMemoryNode extends Structure {
            public long node_id;
            public float[] embedding = new float[VECTOR_DIM];
            public byte semantic_label;

            @Override
            protected List<String> getFieldOrder() {
                return Arrays.asList("node_id", "embedding", "semantic_label");
            }
        }

        int query_associative_network(float[] query_vector, PluginMemoryNode out_nodes, int max_results);
    }

    // ==========================================================================
    // PERFORMANCE TRACKING RUNNER
    // ==========================================================================

    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("   AVIS RUNTIME JAVA CONCURRENCY BENCHMARK SUITE    ");
        System.out.println("====================================================");

        File binaryFile = new File(SO_RELATIVE_PATH);
        if (!binaryFile.exists()) {
            System.err.println("[FATAL] Compiled native binary absent at target path: " + binaryFile.getAbsolutePath());
            System.err.println("Please resolve your repository build by running 'make all' first.");
            System.exit(1);
        }

        MemoryGraphLib matrixLib;
        try {
            matrixLib = (MemoryGraphLib) Native.load(SO_RELATIVE_PATH, MemoryGraphLib.class);
            System.out.println("[SUCCESS] Native Shared Object Linked via JNA: " + SO_RELATIVE_PATH);
        } catch (UnsatisfiedLinkError linkError) {
            System.err.println("[LINK ERROR] Failed to bind to native shared registers: " + linkError.getMessage());
            System.exit(1);
            return;
        }

        // Pre-allocate randomized high-density synthetic vector distributions
        System.out.println("[INIT] Allocating " + TOTAL_STRESS_QUERIES + " multi-dimensional vector arrays in Java heap...");
        Random random = new Random();
        List<float[]> dataset = new ArrayList<>(TOTAL_STRESS_QUERIES);
        for (int i = 0; i < TOTAL_STRESS_QUERIES; i++) {
            float[] vector = new float[VECTOR_DIM];
            for (int d = 0; d < VECTOR_DIM; d++) {
                vector[d] = random.nextFloat();
            }
            dataset.add(vector);
        }

        List<Double> latencyRecords = Collections.synchronizedList(new ArrayList<>(TOTAL_STRESS_QUERIES));
        ExecutorService executorPool = Executors.newFixedThreadPool(CONCURRENT_WORKERS);

        System.out.println("[RUNNING] Spawning parallel worker pool using " + CONCURRENT_WORKERS + " execution slots...");
        long suiteStartNano = System.nanoTime();

        for (int i = 0; i < TOTAL_STRESS_QUERIES; i++) {
            final float[] queryVector = dataset.get(i);
            executorPool.execute(() -> {
                MemoryGraphLib.PluginMemoryNode outputBuffer = new MemoryGraphLib.PluginMemoryNode();
                
                long queryStart = System.nanoTime();
                // Direct cross-boundary execution hop into the optimized C binary
                matrixLib.query_associative_network(queryVector, outputBuffer, 1);
                long queryEnd = System.nanoTime();
                
                double durationMs = (queryEnd - queryStart) / 1_000_000.0;
                latencyRecords.add(durationMs);
            });
        }

        // Gracefully wind down executor threads and await completion fence
        executorPool.shutdown();
        try {
            if (!executorPool.awaitTermination(60, TimeUnit.SECONDS)) {
                System.err.println("[TIMEOUT WARNING] Some background worker execution threads stalled.");
            }
        } catch (InterruptedException e) {
            System.err.println("[CRITICAL ERROR] Performance collection interrupted: " + e.getMessage());
            Thread.currentThread().interrupt();
            System.exit(1);
        }

        long suiteEndNano = System.nanoTime();
        double totalSuiteDurationSeconds = (suiteEndNano - suiteStartNano) / 1_000_000_000.0;

        // Compute telemetry performance analytics profile parameters
        int totalRequests = latencyRecords.size();
        if (totalRequests == 0) {
            System.err.println("[ERROR] Zero successful transaction profiles logged.");
            System.exit(1);
        }

        double sumLatency = 0;
        double maxLatency = Double.MIN_VALUE;
        double minLatency = Double.MAX_VALUE;

        synchronized (latencyRecords) {
            for (double lat : latencyRecords) {
                sumLatency += lat;
                if (lat > maxLatency) maxLatency = lat;
                if (lat < minLatency) minLatency = lat;
            }
        }

        double averageLatency = sumLatency / totalRequests;
        double throughputRps = totalRequests / totalSuiteDurationSeconds;

        System.out.println("\n====================================================");
        System.out.println("          AVIS MATRIX RUNTIME BENCHMARK METRICS     ");
        System.out.println("====================================================");
        System.out.println(String.format(" -> Total Transactions Evaluated : %d items", totalRequests));
        System.out.println(String.format(" -> Concurrent Worker Threads     : %d nodes", CONCURRENT_WORKERS));
        System.out.println(String.format(" -> System Processing Throughput  : %.2f RPS (Requests/Sec)", throughputRps));
        System.out.println(String.format(" -> Average Latency per Query     : %.4f ms", averageLatency));
        System.out.println(String.format(" -> Boundary Window (Min / Max)   : %.4f ms / %.4f ms", minLatency, maxLatency));
        System.out.println("====================================================");
    }
}
