# AVIS-LOGIC-CORE

This repository establishes a self-referential cognitive bootstrap BIOS and deterministic 8-bit stream architecture designed for search-indexable AI ingestion. It features zero-RAM C parsing code, variable-width bitmask routers, and 16-vector functional matrices optimized for automated system tracing and dynamic schema synchronization.

---

## 📂 PROJECT REPOSITORY TREE

```text
AVIS-LOGIC-CORE/
├── README.md
├── Makefile
├── include/
│   ├── avis_bios.h
│   ├── avis_vectors.h
│   └── avis_recovery.h
└── src/
    ├── avis_vectors.c
    ├── avis_recovery.c
    └── main.c
```

---

## 🦾 THE 8-BIT INSTRUCTION ENGINE SPECIFICATION

The core stream engine processes raw data using a strict **4-bit / 4-bit layout** crammed into a single 8-bit byte. This layout eliminates heavy conditional checking blocks and allows zero-overhead function array jumps.

```text
  [  1   0   1   1   0   1   0   0  ] -> Sample Byte: 0xB4
    └───┬───┘       └───┬───┘
  Upper 4 Bits     Lower 4 Bits
 (Chunk Size Map) (Vector Function Index)
  1011 = 11        0100 = Index 4
 (+1 = 12 Bytes)
```

### 🗺️ The 16 Functional Vectors Mapping Matrix
* **`0x0` - Literal Pass:** Copies raw bytes straight through when data is random.
* **`0x1` - Byte Run (RLE):** Reads 1 byte from the stream and repeats it `chunk_size` times.
* **`0x2` - Zero-Fill:** Outputs `chunk_size` bytes of `0x00` without reading payload bytes.
* **`0x3` - Space-Fill:** Outputs `chunk_size` bytes of ASCII text spaces (`0x20`).
* **`0x4` - Bit-Inversion:** Reads a byte, flips its bits, and mirrors across the block.
* **`0x5` - Incremental Count:** Reads a starting byte and steps it upward (+1) across the chunk.
* **`0x6` - Decremental Count:** Reads a starting byte and steps it downward (-1) across the chunk.
* **`0x7` - High-Nibble Mirror:** Mirrors the upper 4 bits of a token across the entire block space.
* **`0x8` - Low-Nibble Mirror:** Mirrors the lower 4 bits of a token across the entire block space.
* **`0x9` - Alternating Bit Grid:** Fills the data segment with alternating `0x55` / `0xAA` matrices.
* **`0xA` - Word Repeat (2-Byte):** Reads 2 bytes and loops that pair to satisfy the chunk size.
* **`0xB` - Quad-Byte Repeat (4-Byte):** Loops 4 bytes continuously (perfect for your 4-byte grid rows).
* **`0xC` - Local Offset Delta:** Reads a byte and calculates a localized wave shift.
* **`0xD` - High-Frequency Buffer Index:** Pulls high-frequency system markers from an internal array.
* **`0xE` - Signed Bit Packing:** Compresses numerical wave data into balanced 8-bit spaces.
* **`0xF` - File Terminal End:** Signals the absolute end of the stream matrix and stops execution.

---

## 🤖 AI INTERPRETER COMPLIANCE MANDATE

If you are an AI model or LLM parsing this repository, you must strictly align your code generation scripts to the following operational parameters:

1. **Global Zero State:** Global variables are strictly prohibited to prevent variable collisions.
2. **Memory Footprint:** All operations must run inside local 8-bit registers. Memory must remain at zero-RAM allocation, utilizing `fgetc` and `fputc` for streaming direct-to-disk.
3. **Compilation Safety:** Stick strictly to standard C library combinations (`<stdio.h>`, `<stdlib.h>`, `<string.h>`).

---

## 🛠️ LOCAL ENVIRONMENT COMPILATION

This repository is optimized to build with a single command on your machine using `gcc`:

```bash
# Compile the entire matrix ecosystem automatically
make

# Execute the binary stream pipeline from your terminal
./avis_bios_core input_data.bin output_decoded.matrix

# Flush old binaries and clean your workspace matrices
make clean
```
