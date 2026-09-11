/* 
 * ============================================================================
 * 🌐 MERCWAR AVIS-LOGIC-CORE: STREAM RESYNCHRONIZATION DEFIANT LAYER
 * SAVE PATH: ./include/avis_recovery.h
 * ============================================================================
 */

#ifndef AVIS_RECOVERY_H
#define AVIS_RECOVERY_H

#include "avis_bios.h"

// Returns the newly aligned file descriptor offset, or -1 if stream ends
long long resynchronize_stream(FILE *in);

#endif // AVIS_RECOVERY_H
