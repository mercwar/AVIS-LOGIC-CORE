#!/bin/bash
# ==========================================================================
# AVIS SYSTEM AUTOMATION UTILITY
# FILE: /avis_core/MercwarAI/bootstrap_interface.sh
# ==========================================================================
set -e

# Terminal formatting
CYAN='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -e "${CYAN}[MERCWAR_AI] Bootstrapping native model interface layer...${NC}"

# 1. Compile C++ Code into a thread-safe shared object module
g++ -O3 -shared -fPIC -std=c++11 mercwar_ai_bridge.cpp -o libmercwar_ai.so

# 2. Transpile Java JNA Binding controllers
cd ..
javac -cp .:lib/jna.jar MercwarAI/AvisModelBridge.java

echo -e "${GREEN}[SUCCESS] Interface linked. Running evaluation verification trace...${NC}"
java -cp .:lib/jna.jar MercwarAI.AvisModelBridge
