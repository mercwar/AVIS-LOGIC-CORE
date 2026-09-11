/* ========================================================================== */
/* AVIS SYSTEM CORE COMPONENT                                                */
/* FILE: /avis_core/bin/memory_vector_graph/memory_graph.h                    */
/* DESCRIPTION: Architecture mappings for associative semantic graph storage.*/
/* ========================================================================== */

#ifndef MEMORY_GRAPH_H
#define MEMORY_GRAPH_H

#include <stdint.h>

#define MAX_RELATIONS 64
#define VECTOR_DIM 1536

typedef struct {
    uint64_t node_id;
    float embedding[VECTOR_DIM];
    char semantic_label[256];
} MemoryNode;

typedef struct {
    uint64_t source_id;
    uint64_t target_id;
    float association_weight;
} GraphEdge;

int query_associative_network(const float* query_vector, MemoryNode* out_nodes, int max_results);
int update_edge_weight(uint64_t source, uint64_t target, float delta);

#endif /* MEMORY_GRAPH_H */
