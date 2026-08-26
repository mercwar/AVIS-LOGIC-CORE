/* 
 * ============================================================================
 * 🌐 MERCWAR AVIS-LOGIC-CORE: FAULT RECOVERY LAYER
 * SAVE PATH: ./src/avis_recovery.c
 * ============================================================================
 */

#include "avis_recovery.h"

long long resynchronize_stream(FILE *in) {
    int current_byte;
    int alignment_state = 0;
    long long skipped_bytes = 0;

    printf("[RECOVERY] Format mismatch detected. Re-aligning data boundaries...\n");

    while ((current_byte = fgetc(in)) != EOF) {
        switch (alignment_state) {
            case 0:
                if (current_byte == SYNC_0) alignment_state = 1;
                else { alignment_state = 0; skipped_bytes++; }
                break;
            case 1:
                if (current_byte == SYNC_1) alignment_state = 2;
                else { alignment_state = 0; skipped_bytes++; }
                break;
            case 2:
                if (current_byte == SYNC_2) alignment_state = 3;
                else { alignment_state = 0; skipped_bytes++; }
                break;
            case 3:
                if (current_byte == SYNC_3) {
                    printf("[RECOVERY SUCCESS] Synced onto valid matrix block. Skipped %lld bytes.\n", skipped_bytes);
                    return ftell(in); // Return the newly aligned file pointer address
                }
                alignment_state = 0;
                skipped_bytes++;
                break;
        }
    }
    
    printf("[RECOVERY CRITICAL] End of stream reached without alignment lock.\n");
    return -1;
}
