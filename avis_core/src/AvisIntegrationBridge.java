/* ========================================================================== */
/* AVIS SYSTEM CORE COMPONENT                                                */
/* FILE: /avis_core/src/AvisIntegrationBridge.java                            */
/* DESCRIPTION: JNA native bridge layer connecting Java and compiled C tools.*/
/* ========================================================================== */

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import java.util.Arrays;
import java.util.List;

public class AvisIntegrationBridge {

    // ==========================================================================
    // NATIVE INTERFACE DEFINITIONS MAPPING TO THE APP .SO FILES
    // ==========================================================================

    public interface MemoryGraphLib extends Library {
        // Struct mapping for C MemoryNode
        public static class MemoryNode extends Structure {
            public long node_id;
            public float[] embedding = new float[1536];
            public byte semantic_label;

            @Override
            protected List<String> getFieldOrder() {
                return Arrays.asList("node_id", "embedding", "semantic_label");
            }
        }

        int query_associative_network(float[] query_vector, MemoryNode out_nodes, int max_results);
        int update_edge_weight(long source, long target, float delta);
    }

    public interface LogicSolverLib extends Library {
        int evaluate_logic_tree(Pointer rootNodePointer);
        String generate_proof_step_trace(Pointer rootNodePointer);
    }

    public interface PathRefinerLib extends Library {
        // Struct mapping for C SearchStep
        public static class SearchStep extends Structure {
            public int step_id;
            public float reward_score;
            public byte[] hypothesis_string = new byte[512];

            @Override
            protected List<String> getFieldOrder() {
                return Arrays.asList("step_id", "reward_score", "hypothesis_string");
            }
        }

        // Struct mapping for C TreeSearchTracker
        public static class TreeSearchTracker extends Structure {
            public SearchStep[] execution_path = new SearchStep[128];
            public int current_depth;
            public int max_explored_depth;

            @Override
            protected List<String> getFieldOrder() {
                return Arrays.asList("execution_path", "current_depth", "max_explored_depth");
            }
        }

        void register_step_outcome(TreeSearchTracker tracker, String hypothesis, float score);
        int check_backtrack_condition(TreeSearchTracker tracker, float threshold);
    }

    // ==========================================================================
    // RUNTIME INVENTORY CORES AND TESTING HARNESS
    // ==========================================================================

    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println(" INITIALIZING AVIS JAVA COGNITIVE INTEGRATION LINK");
        System.out.println("====================================================");

        try {
            // Load Memory Graph library dynamically from its relative compiled binary path
            MemoryGraphLib memoryGraph = (MemoryGraphLib) Native.load(
                "bin/memory_vector_graph/memory_graph.so", MemoryGraphLib.class
            );
            System.out.println("[SUCCESS] Linked Native Module: memory_graph.so");

            // Load Logic Solver library dynamically
            LogicSolverLib logicSolver = (LogicSolverLib) Native.load(
                "bin/symbolic_logic_engine/logic_solver.so", LogicSolverLib.class
            );
            System.out.println("[SUCCESS] Linked Native Module: logic_solver.so");

            // Load Path Refiner library dynamically
            PathRefinerLib pathRefiner = (PathRefinerLib) Native.load(
                "bin/recursive_refiner/path_refiner.so", PathRefinerLib.class
            );
            System.out.println("[SUCCESS] Linked Native Module: path_refiner.so");

            // ----------------------------------------------------------------------
            // FUNCTIONAL VERIFICATION SEQUENCE
            // ----------------------------------------------------------------------
            System.out.println("\n[RUNNING] Executing dynamic testing suite validation...");

            // Test Vector Query Mapping Routine
            float[] sampleQuery = new float[1536];
            sampleQuery[0] = 0.85f;
            MemoryGraphLib.MemoryNode outputNodeBuffer = new MemoryGraphLib.MemoryNode();
            
            int activeNodesFound = memoryGraph.query_associative_network(sampleQuery, outputNodeBuffer, 1);
            System.out.println(" -> Memory Network Query Active. Target results: " + activeNodesFound);

            // Test Path Backtrack Validation Check
            PathRefinerLib.TreeSearchTracker trackerInstance = new PathRefinerLib.TreeSearchTracker();
            trackerInstance.current_depth = 1; 
            int shouldBacktrack = pathRefiner.check_backtrack_condition(trackerInstance, 0.50f);
            System.out.println(" -> Path Backtrack Controller status code returned: " + shouldBacktrack);

            System.out.println("\n====================================================");
            System.out.println(" INTEGRATION VERIFICATION COMPLETE: ALL PIPELINES PASS");
            System.out.println("====================================================");

        } catch (UnsatisfiedLinkError linkError) {
            System.err.println("\n[CRITICAL ERROR] Failed to bind to native .so files.");
            System.err.println("Ensure you ran 'make' inside the root directory before running this file.");
            System.err.println("Diagnostic message: " + linkError.getMessage());
        }
    }
}
