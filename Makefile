# ============================================================================
# 🌐 AVIS PATH SYSTEM CONFIGURATION ARCHITECTURE
# SAVE PATH: ./Makefile
# TARGET: Automation Build Script for GCC compiler link loops
# ============================================================================

CC = gcc
CFLAGS = -Wall -Wextra -O3 -Iinclude
TARGET = avis_bios_core
SRC = src/main.c src/avis_vectors.c src/avis_recovery.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo "=================================================="
	@echo "✓ AVIS SYSTEM COMPILATION COMPLETE: $(TARGET)"
	@echo "=================================================="

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
	@echo "✓ Workspace matrices flushed cleanly from storage."
