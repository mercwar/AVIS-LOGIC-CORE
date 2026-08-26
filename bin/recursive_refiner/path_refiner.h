/* ========================================================================== */
/* AVIS SYSTEM CORE COMPONENT                                                */
/* FILE: /avis_core/bin/recursive_refiner/path_refiner.h                      */
/* DESCRIPTION: State structures for multi-path tracking routines.            */
/* ========================================================================== */

#ifndef PATH_REFINER_H
#define PATH_REFINER_H

typedef struct {
    int step_id;
    float reward_score;
    char hypothesis_string[512];
} SearchStep;

typedef struct {
    SearchStep execution_path[128];
    int current_depth;
    int max_explored_depth;
} TreeSearchTracker;

void register_step_outcome(TreeSearchTracker* tracker, const char* hypothesis, float score);
int check_backtrack_condition(TreeSearchTracker* tracker, float threshold);

#endif /* PATH_REFINER_H */
