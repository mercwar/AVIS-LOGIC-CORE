#!/bin/bash
set -e
echo -e "\033[0;33m[BUILD] Compiling optimized GGML tensor matrix layers...\033[0m"
gcc -O3 -shared -fPIC ggml_tensor_optimizer.c -o ggml_tensor_optimizer.so
javac AvisGgmlInterface.java
echo -e "\033[0;32m[SUCCESS] GGML system libraries compiled.\033[0m"
