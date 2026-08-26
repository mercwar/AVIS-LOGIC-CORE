/* ========================================================================== */
/* AVIS SYSTEM CORE INTERFACE EXPORT                                         */
/* FILE: /avis_core/MercwarAI/mercwar_ai_bridge.h                            */
/* DESCRIPTION: C-compatible linkage declarations for external GGUF engines.  */
/* ========================================================================== */

#ifndef MERCWAR_AI_BRIDGE_H
#define MERCWAR_AI_BRIDGE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TOKEN_RESERVE 4096

typedef struct {
    uint64_t session_id;
    int32_t context_tokens_active;
    float cumulative_loss_score;
    int8_t strict_guardrail_enforced;
} InferenceSessionState;

/* Exported Symbol Mappings for JNA / External C++ Callers */
int32_t mercwar_ai_initialize_link(InferenceSessionState* state, const char* config_json_path);
int32_t mercwar_ai_process_token_stream(InferenceSessionState* state, const int32_t* token_array, size_t array_length, char* out_response_json);
void mercwar_ai_terminate_link(InferenceSessionState* state);

#ifdef __cplusplus
}
#endif

#endif /* MERCWAR_AI_BRIDGE_H */
