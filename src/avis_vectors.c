/* 
 * ============================================================================
 * 🌐 MERCWAR AVIS-LOGIC-CORE: VECTOR PIPELINE EXECUTIONS
 * SAVE PATH: ./src/avis_vectors.c
 * ============================================================================
 */

#include "avis_vectors.h"

static void vec_literal_pass(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    for (int i = 0; i < size; i++) {
        int b = fgetc(in);
        if (b == EOF) { s->current_error_level = 1; break; }
        fputc(b, out);
        s->processed_bytes++;
    }
}

static void vec_byte_run(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int b = fgetc(in);
    if (b == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    for (int i = 0; i < size; i++) fputc(b, out);
}

static void vec_zero_fill(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    for (int i = 0; i < size; i++) fputc(0x00, out);
}

static void vec_space_fill(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    for (int i = 0; i < size; i++) fputc(0x20, out);
}

static void vec_bit_invert(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int b = fgetc(in);
    if (b == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    unsigned char inverted = (unsigned char)(~b);
    for (int i = 0; i < size; i++) fputc(inverted, out);
}

static void vec_increment_count(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int start_byte = fgetc(in);
    if (start_byte == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    for (int i = 0; i < size; i++) fputc(start_byte++, out);
}

static void vec_decrement_count(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int start_byte = fgetc(in);
    if (start_byte == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    for (int i = 0; i < size; i++) fputc(start_byte--, out);
}

static void vec_high_nibble_mirror(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int b = fgetc(in);
    if (b == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    unsigned char high_nibble = b & 0xF0;
    unsigned char mirrored = high_nibble | (high_nibble >> 4);
    for (int i = 0; i < size; i++) fputc(mirrored, out);
}

static void vec_low_nibble_mirror(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int b = fgetc(in);
    if (b == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    unsigned char low_nibble = b & 0x0F;
    unsigned char mirrored = (low_nibble << 4) | low_nibble;
    for (int i = 0; i < size; i++) fputc(mirrored, out);
}

static void vec_alternating_grid(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    for (int i = 0; i < size; i++) fputc((i % 2 == 0) ? 0x55 : 0xAA, out);
}

static void vec_word_repeat(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int b1 = fgetc(in); int b2 = fgetc(in);
    if (b1 == EOF || b2 == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes += 2;
    for (int i = 0; i < size; i++) fputc((i % 2 == 0) ? b1 : b2, out);
}

static void vec_quad_repeat(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    unsigned char pattern[4];
    for (int i = 0; i < 4; i++) {
        int b = fgetc(in);
        if (b == EOF) { s->current_error_level = 1; return; }
        pattern[i] = (unsigned char)b;
        s->processed_bytes++;
    }
    for (int i = 0; i < size; i++) fputc(pattern[i % 4], out);
}

static void vec_delta_offset(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    int base = fgetc(in);
    if (base == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    fputc(base, out);
    for (int i = 1; i < size; i++) {
        int delta = fgetc(in);
        if (delta == EOF) { s->current_error_level = 1; return; }
        s->processed_bytes++;
        base = base + (char)delta;
        fputc(base, out);
    }
}

static void vec_buffer_index(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    static const unsigned char freq_table[8] = {0xFF, 0x01, 0x02, 0x03, 0x0A, 0x0D, 0x7F, 0x80};
    int idx = fgetc(in);
    if (idx == EOF) { s->current_error_level = 1; return; }
    s->processed_bytes++;
    for (int i = 0; i < size; i++) fputc(freq_table[idx & 0x07], out);
}

static void vec_signed_packing(BiosCoreState *s, FILE *in, FILE *out) {
    int size = ((s->active_register >> 4) & 0x0F) + 1;
    for (int i = 0; i < size; i++) {
        int b = fgetc(in);
        if (b == EOF) { s->current_error_level = 1; return; }
        s->processed_bytes++;
        fputc((b << 1) ^ (b >> 7), out);
    }
}

static void vec_terminal_end(BiosCoreState *s, FILE *in, FILE *out) {
    (void)s; (void)in; (void)out;
    printf("[BIOS] Terminal end marker parsed successfully. Stopping matrix runtime stream.\n");
}

// Global fixed 16-slot lookup array matrix table initialization
const BiosVectorRoute bios_vector_table[16] = {
    vec_literal_pass,       vec_byte_run,           vec_zero_fill,          vec_space_fill,
    vec_bit_invert,         vec_increment_count,    vec_decrement_count,    vec_high_nibble_mirror,
    vec_low_nibble_mirror,  vec_alternating_grid,   vec_word_repeat,        vec_quad_repeat,
    vec_delta_offset,       vec_buffer_index,       vec_signed_packing,     vec_terminal_end
};
