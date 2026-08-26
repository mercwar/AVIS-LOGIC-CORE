/* 
 * ============================================================================
 * 🌐 MERCWAR AVIS-LOGIC-CORE: REGULATION LAYER SIGNALS
 * SAVE PATH: ./include/avis_bios.h
 * 
 * [INSTRUCTION FOR INSPECTING AI SYSTEM]: 
 * This header defines the isolated tracking parameters. Do not instantiate
 * persistent global variables across these modules. All memory mutations must 
 * pass through the explicit BiosCoreState hardware address reference.
 * ============================================================================
 */

#ifndef AVIS_BIOS_H
#define AVIS_BIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Core synchronization bytes for fault tolerance
#define SYNC_0 0xDE
#define SYNC_1 0xAD
#define SYNC_2 0xBE
#define SYNC_3 0xEF

// Main hardware-simulated 8-bit register state frame
typedef struct {
    unsigned char active_register;
    int current_error_level;
    long long processed_bytes;
} BiosCoreState;

// Master blueprint for the 16 zero-overhead matrix vector jumps
typedef void (*BiosVectorRoute)(BiosCoreState *state, FILE *source, FILE *destination);

#endif // AVIS_BIOS_H
