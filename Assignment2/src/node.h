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
    move_t move;
    uint8_t board[SIZE][SIZE];
    struct node_s* parent;
    bool is_same_board;
};

typedef struct node_s node_t;

#endif
