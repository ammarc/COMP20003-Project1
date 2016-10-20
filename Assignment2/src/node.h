#ifndef __NODE__
#define __NODE__

#include "utils.h"

/**
 * Data structure containing the node information
 */
struct node_s
{
    uint32_t priority;
    uint32_t score;
    int depth;
    int num_childs;
    move_t move;
    uint8_t board[SIZE][SIZE];
    struct node_s* parent;
    //adding an additional variable to check if the board is the same
    bool is_same_board;
};

typedef struct node_s node_t;


//Move these to ai.h
void graph_init(node_t** node);

node_t* apply_action(node_t* node, move_t action, uint8_t board[SIZE][SIZE]);

void copy_board(uint8_t src[SIZE][SIZE], uint8_t dest[SIZE][SIZE]);

void propagate_score(node_t* node, move_t* best_action, uint32_t* max_score);

#endif
