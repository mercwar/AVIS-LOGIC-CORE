/* ========================================================================== */
/* AVIS SYSTEM CORE COMPONENT                                                */
/* FILE: /avis_core/bin/symbolic_logic_engine/logic_solver.h                  */
/* DESCRIPTION: Structural nodes and parsing schemas for logic validation.   */
/* ========================================================================== */

#ifndef LOGIC_SOLVER_H
#define LOGIC_SOLVER_H

typedef enum { OP_AND, OP_OR, OP_NOT, OP_IMPLIES, OP_EQUIV } OpType;

typedef struct LogicNode {
    int is_variable;
    char var_name[32];
    int truth_value;
    OpType operation;
    struct LogicNode* left;
    struct LogicNode* right;
} LogicNode;

int evaluate_logic_tree(LogicNode* root);
char* generate_proof_step_trace(LogicNode* root);

#endif /* LOGIC_SOLVER_H */
