package ggml;

import com.sun.jna.Library;

public interface AvisGgmlInterface extends Library {
    int run_accelerated_tensor_reduction(float[] raw_weights, int total_rows, int total_columns, float[] out_result);
}
