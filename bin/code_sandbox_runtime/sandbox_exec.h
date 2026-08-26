/* ========================================================================== */
/* AVIS SYSTEM CORE COMPONENT                                                */
/* FILE: /avis_core/bin/code_sandbox_runtime/sandbox_exec.h                   */
/* DESCRIPTION: Context limits, boundary checks, and system tracking tables. */
/* ========================================================================== */

#ifndef SANDBOX_EXEC_H
#define SANDBOX_EXEC_H

#include <sys/types.h>

typedef struct {
    pid_t child_pid;
    int timeout_seconds;
    size_t memory_limit_bytes;
} SandboxConfig;

int initialize_secure_boundary(SandboxConfig* config);
int run_isolated_bytecode(const uint8_t* buffer, size_t size);

#endif /* SANDBOX_EXEC_H */
