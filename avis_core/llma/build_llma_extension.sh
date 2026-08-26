#!/bin/bash
set -e
echo -e "\033[0;33m[BUILD] Compiling localized LLMA tracking networks...\033[0m"
gcc -O3 -shared -fPIC llma_path_validator.c -o llma_path_validator.so
javac AvisLlmaInterface.java
echo -e "\033[0;32m[SUCCESS] LLMA system libraries compiled.\033[0m"
