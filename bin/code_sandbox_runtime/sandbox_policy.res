# ==========================================================================
# AVIS SYSTEM CORE RESOURCE
# FILE: /avis_core/bin/code_sandbox_runtime/sandbox_policy.res
# DESCRIPTION: System call security tables for runtime boundary limits.
# ==========================================================================
ALLOWED_SYSCALLS=[sys_read, sys_write, sys_exit, sys_brk]
MEMORY_CEILING_MB=64
CPU_TIME_LIMIT_MS=500
