# ==========================================================================
# AVIS SYSTEM CORE COMPONENT
# FILE: /avis_core/Makefile
# DESCRIPTION: Master build system for LLM IQ boost applications.
# ==========================================================================

# Toolchain definitions
CC      := gcc
CFLAGS  := -Wall -Wextra -O3 -std=c99 -fPIC -I.
LDFLAGS := -shared

# Target directory definitions
BIN_DIR := bin
APP_1   := $(BIN_DIR)/memory_vector_graph
APP_2   := $(BIN_DIR)/symbolic_logic_engine
APP_3   := $(BIN_DIR)/recursive_refiner
APP_4   := $(BIN_DIR)/code_sandbox_runtime

# Collection arrays for build automation
TARGETS_SO  := $(APP_1)/memory_graph.so \
               $(APP_2)/logic_solver.so \
               $(APP_3)/path_refiner.so \
               $(APP_4)/sandbox_exec.so

TARGETS_BIN := $(APP_1)/memory_graph_exec \
               $(APP_2)/logic_solver_exec \
               $(APP_3)/path_refiner_exec \
               $(APP_4)/sandbox_exec_exec

# Default macro target: Build all binaries and shared libraries
.PHONY: all
all: directories $(TARGETS_SO) $(TARGETS_BIN)
	@echo "===================================================="
	@echo " AVIS CORE SYSTEM BUILD SUCCESSFUL "
	@echo " All targets compiled with optimizations (-O3)."
	@echo "===================================================="

# Validation macro target: Ensure required structural directories exist
.PHONY: directories
directories:
	@mkdir -p $(APP_1) $(APP_2) $(APP_3) $(APP_4)

# ==========================================================================
# COMPILATION RULES FOR INDIVIDUAL ECOSYSTEM APPS
# ==========================================================================

# App 1: Memory Vector Graph
$(APP_1)/memory_graph.so: $(APP_1)/memory_graph.c $(APP_1)/memory_graph.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

$(APP_1)/memory_graph_exec: $(APP_1)/memory_graph.c $(APP_1)/memory_graph.h
	$(CC) $(CFLAGS) $< -DMAIN_TEST_RUN -o $@

# App 2: Symbolic Logic Engine
$(APP_2)/logic_solver.so: $(APP_2)/logic_solver.c $(APP_2)/logic_solver.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

$(APP_2)/logic_solver_exec: $(APP_2)/logic_solver.c $(APP_2)/logic_solver.h
	$(CC) $(CFLAGS) $< -DMAIN_TEST_RUN -o $@

# App 3: Recursive Refiner
$(APP_3)/path_refiner.so: $(APP_3)/path_refiner.c $(APP_3)/path_refiner.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

$(APP_3)/path_refiner_exec: $(APP_3)/path_refiner.c $(APP_3)/path_refiner.h
	$(CC) $(CFLAGS) $< -DMAIN_TEST_RUN -o $@

# App 4: Code Sandbox Runtime
$(APP_4)/sandbox_exec.so: $(APP_4)/sandbox_exec.c $(APP_4)/sandbox_exec.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

$(APP_4)/sandbox_exec_exec: $(APP_4)/sandbox_exec.c $(APP_4)/sandbox_exec.h
	$(CC) $(CFLAGS) $< -DMAIN_TEST_RUN -o $@

# ==========================================================================
# SYSTEM WORKSPACE MAINTENANCE COMMANDS
# ==========================================================================

# Clean macro target: Scrub built outputs and temporary artifacts
.PHONY: clean
clean:
	rm -f $(TARGETS_SO) $(TARGETS_BIN)
	rm -f $(BIN_DIR)/*/*.o
	@echo "Workspace cleaned of binary artifacts."

# Status macro target: Display diagnostic overview of target items
.PHONY: status
status:
	@echo "Current AVIS Core Inventory:"
	@echo "----------------------------"
	@ls -R $(BIN_DIR)
