/* ========================================================================== */
/* AVIS SYSTEM CORE COMPONENT                                                */
/* FILE: /avis_core/bin/recursive_refiner/path_refiner.c                      */
/* DESCRIPTION: Tracks tree depth configurations and scoring metrics.         */
/* ========================================================================== */

#include "path_refiner.h"
#include <string.h>

void register_step_outcome(TreeSearchTracker* tracker, const char* hypothesis, float score) {
    if (tracker->current_depth < 128) {
        int d = tracker->current_depth;
        tracker->execution_path[d].step_id = d;
        tracker->execution_path[d].reward_score = score;
        strncpy(tracker->execution_path[d].hypothesis_string, hypothesis, 511);
        tracker->current_depth++;
    }
}

int check_backtrack_condition(TreeSearchTracker* tracker, float threshold) {
    if (tracker->current_depth == 0) return 0;
    /* Triggers backtrack flag if score dips below structural threshold */
    return (tracker->execution_path[tracker->current_depth - 1].reward_score < threshold);
}
