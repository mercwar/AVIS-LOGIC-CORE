#!/bin/bash
set -e
echo -e "\033[0;33m[BUILD] Compiling high-utility GGUF matrix injection layers...\033[0m"
gcc -O3 -shared -fPIC gguf_metadata_injector.c -o gguf_metadata_injector.so
javac AvisGgufInterface.java
echo -e "\033[0;32m[SUCCESS] GGUF system libraries compiled.\033[0m"
