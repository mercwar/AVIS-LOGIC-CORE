#!/bin/bash
set -e
echo -e "\033[0;33m[BUILD] Compiling localized LLM context refresh nodes...\033[0m"
gcc -O3 -shared -fPIC llm_context_refresher.c -o llm_context_refresher.so
javac AvisLlmInterface.java
echo -e "\033[0;32m[SUCCESS] LLM system libraries compiled.\033[0m"
