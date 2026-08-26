#!/bin/bash

# ==========================================================================
# AVIS SYSTEM CORE SETUP, BUILD & DOCUMENTATION UTILITY (V2026.08.26)
# DESCRIPTION: Automates cloning, layout configuration, compilation, and 
#              injects runtime context instructions for GGUF/LLM developers.
# ==========================================================================

set -e

# Terminal formatting definitions
GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m' 

clear
echo -e "${CYAN}======================================================================${NC}"
echo -e "${CYAN}${BOLD}                 AVIS ENGINE PROTOCOL CODEBASE LAUNCHER               ${NC}"
echo -e "${CYAN}======================================================================${NC}"

# ----------------------------------------------------------------------
# EXPLICIT SYSTEM EXPLANATION FOR PROGRAMMERS
# ----------------------------------------------------------------------
echo -e "\n${BOLD}💡 WHAT IS THIS ECOSYSTEM?${NC}"
echo -e "This repository bridges an LLM (running via GGUF, llama.cpp, or vLLM) with native"
echo -e "high-performance C libraries to bypass common cognitive limitations (IQ Boost)."
echo -e "The layout consists of:"
echo -e "  1. ${BOLD}C Backends:${NC} High-speed graph memories, logic solvers, and sandboxes."
echo -e "  2. ${BOLD}Java JNA Layer:${NC} Handles hardware lifecycle and structural database logging."
echo -e "  3. ${BOLD}.avis Protocols:${NC} The routing maps your LLM parses to call tools cleanly."

# ----------------------------------------------------------------------
# STEP 1: REPOSITORY CLONING PIPELINE
# ----------------------------------------------------------------------
echo -e "\n${YELLOW}[STEP 1/5] Checking Git Status and Repository Allocation...${NC}"
REPO_URL="https://github.com"
TARGET_DIR="avis_core"

if [ ! -d ".git" ] && [ ! -d "$TARGET_DIR" ]; then
    echo -e "Target repository directory missing. Triggering remote clone sequence..."
    git clone "$REPO_URL" "$TARGET_DIR"
    cd "$TARGET_DIR"
else
    echo -e "${GREEN}[INFO]${NC} Existing workspace directory recognized. Transitioning to root..."
    if [ -d "$TARGET_DIR" ]; then cd "$TARGET_DIR"; fi
fi

# ----------------------------------------------------------------------
# STEP 2: FILE SYSTEM ARCHITECTURE INITIALIZATION
# ----------------------------------------------------------------------
echo -e "\n${YELLOW}[STEP 2/5] Creating Directory Mappings...${NC}"
mkdir -p bin/memory_vector_graph \
         bin/symbolic_logic_engine \
         bin/recursive_refiner \
         bin/code_sandbox_runtime \
         templates/java config lib
echo -e "${GREEN}[SUCCESS]${NC} Directories verified."

# ----------------------------------------------------------------------
# STEP 3: NATIVE HARDWARE LAYER COMPILATION
# ----------------------------------------------------------------------
echo -e "\n${YELLOW}[STEP 3/5] Compiling Shared Objects via C Toolchain...${NC}"
if ! command -v gcc &> /dev/null; then
    echo -e "${RED}[FATAL ERROR] GCC compiler is missing. Install build-essential first.${NC}"
    exit 1
fi

if [ -f "Makefile" ]; then
    make clean && make all
else
    echo -e "${YELLOW}[WARNING] Makefile missing. Compiling fallback objects manually...${NC}"
    gcc -O3 -shared -fPIC bin/memory_vector_graph/memory_graph.c -o bin/memory_vector_graph/memory_graph.so
    gcc -O3 -shared -fPIC bin/symbolic_logic_engine/logic_solver.c -o bin/symbolic_logic_engine/logic_solver.so
    gcc -O3 -shared -fPIC bin/recursive_refiner/path_refiner.c -o bin/recursive_refiner/path_refiner.so
    gcc -O3 -shared -fPIC bin/code_sandbox_runtime/sandbox_exec.c -o bin/code_sandbox_runtime/sandbox_exec.so
fi
echo -e "${GREEN}[SUCCESS]${NC} Native shared binaries compiled successfully."

# ----------------------------------------------------------------------
# STEP 4: DEPENDENCY AND JAVA RUNTIME MANAGEMENT
# ----------------------------------------------------------------------
echo -e "\n${YELLOW}[STEP 4/5] Loading Java Native Access (JNA) Dependencies...${NC}"
if [ ! -f "lib/jna.jar" ]; then
    echo -e "Fetching missing JNA runtime engine package from Maven central archives..."
    curl -sSL "https://maven.org" -o "lib/jna.jar"
fi
echo -e "${GREEN}[SUCCESS]${NC} Java compilation dependencies verified."

# ----------------------------------------------------------------------
# STEP 5: ECOSYSTEM COMPILATION AND INTERFACE RUNTIME
# ----------------------------------------------------------------------
echo -e "\n${YELLOW}[STEP 5/5] Building Java JNA Orchestration Classes...${NC}"
if ! command -v javac &> /dev/null; then
    echo -e "${RED}[FATAL ERROR] JDK (javac) not found. Cannot compile runtime manager.${NC}"
    exit 1
fi
javac -cp .:lib/jna.jar templates/java/AvisProtocolStructure.java templates/java/Avis2026Engine.java
echo -e "${GREEN}[SUCCESS]${NC} Codebase build operations fully concluded."

# ----------------------------------------------------------------------
# HOW-TO MANUAL GENERATION FOR THE GGUF RUNNER
# ----------------------------------------------------------------------
echo -e "\n${CYAN}======================================================================${NC}"
echo -e "${CYAN}${BOLD}              LLM INTERACTION GUIDE FOR GGUF DEVELOPERS               ${NC}"
echo -e "${CYAN}======================================================================${NC}"
echo -e "To make your local model use this system, configure your inference engine"
echo -e "to read the files inside the '${BOLD}/templates/${NC}' directory. Your model must follow"
echo -e "this exact execution sequence:"
echo -e ""
echo -e "  1. Read raw user input text."
echo -e "  2. Evaluate intent against ${BOLD}templates/json/input_guardrail_schema.json${NC}."
echo -e "  3. Prompt choices using ${BOLD}templates/json/conversation_switch_schema.json${NC} to clear up confusion."
echo -e "  4. Format tool calls matching the targets in ${BOLD}templates/core_orchestration.avis${NC}."
echo -e ""
echo -e "${BOLD}💻 MINIMAL PYTHON LLM PROMPT BINDING EXAMPLE:${NC}"
cat << 'EOF'
    import json
    
    # Instruct your GGUF inference model via System Prompt:
    system_instruction = """
    You are an IQ-Boosted agent running on the AVIS Core platform.
    When a user query is received, you MUST output a structured JSON command
    matching the AvisInputGuardrailSchema instead of responding with loose conversational text.
    """
EOF
echo -e "\n${CYAN}======================================================================${NC}"

# Bootstrapping prompt execution
read -p "Would you like to run the compiled system verification suite right now? (y/n): " confirm_run
if [[ "$confirm_run" =~ ^[Yy]$ ]]; then
    echo -e "\n${YELLOW}[RUNNING] Bootstrapping Avis2026Engine...${NC}"
    java -cp .:lib/jna.jar templates.java.Avis2026Engine
else
    echo -e "\nExecution paused. Repository is fully prepared and documented."
fi
