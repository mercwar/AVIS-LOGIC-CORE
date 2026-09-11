#!/bin/bash
# ==========================================================================
# AVIS SYSTEM AUTOMATION UTILITY
# FILE: /avis_core/LM/setup_lm.sh
# ==========================================================================
set -e

echo -e "\033[0;36m[LM-CORE] Initializing cross-compilation pipeline triggers...\033[0m"

# Direct loops to sequence through individual architecture sub-folders
for arch in gguf ggml llma llm; do
    if [ -d "../$arch" ]; then
        echo -e "\033[0;32m -> Transferring control to target node: /$arch\033[0m"
        (cd "../$arch" && bash *.sh)
    fi
done
