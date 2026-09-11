/* 
 * ============================================================================
 * 🌐 MERCWAR AVIS-LOGIC-CORE: CORE ORCHESTRATOR ENGINE
 * SAVE PATH: ./src/main.c
 * ============================================================================
 */

#include "avis_bios.h"
#include "avis_vectors.h"
#include "avis_recovery.h"

int main(int argc, char *argv[]) {
    printf("==================================================\n");
    printf("🛡️  MERCWAR AVIS-LOGIC-CORE ENGINE INITIALIZED   \n");
    printf("==================================================\n");

    if (argc < 3) {
        printf("[ERROR] Insufficient matrix arguments.\n");
        printf("Usage: %s <input.stream> <output.file>\n", argv[0]);
        return 1;
    }

    FILE *input_stream  = fopen(argv[1], "rb");
    FILE *output_stream = fopen(argv[2], "wb");

    if (!input_stream || !output_stream) {
        printf("❌ [CRITICAL IO ERROR] Unable to link storage channels.\n");
        if (input_stream) fclose(input_stream);
        if (output_stream) fclose(output_stream);
        return 1;
    }

    BiosCoreState bios;
    bios.active_register = 0x00;
    bios.current_error_level = 0;
    bios.processed_bytes = 0;

    int incoming_byte;
    printf("[SYSTEM] Ingestion loop online. Processing data stream...\n\n");

    // Execution processing loop—maintaining strict 1-byte RAM overhead
    while ((incoming_byte = fgetc(input_stream)) != EOF) {
        bios.active_register = (unsigned char)incoming_byte;
        
        // Extract lower 4 bits to instantly determine the vector function index
        unsigned char target_vector = bios.active_register & 0x0F;

        // Break loop immediately if the terminal end marker vector (15) is hit
        if (target_vector == 15) {
            bios_vector_table[target_vector](&bios, input_stream, output_stream);
            break;
        }

        // Zero-overhead function pointer array jump execution
        bios_vector_table[target_vector](&bios, input_stream, output_stream);

        // Fault-tolerance mitigation tracking
        if (bios.current_error_level != 0) {
            long long sync_offset = resynchronize_stream(input_stream);
            if (sync_offset == -1) {
                break; // Exit loop if recovery scans to the end of the file
            }
            bios.current_error_level = 0; // Clear error flag post-alignment
        }
    }

    // Clean data flushing and stream teardown
    fclose(input_stream);
    fflush(output_stream);
    fclose(output_stream);

    printf("\n==================================================\n");
    printf("✓ STREAM COMPLETED: Processed %lld payload bytes.\n", bios.processed_bytes);
    printf("==================================================\n");

    return 0;
}
