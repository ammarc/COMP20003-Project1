#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "node.h"
#include "priority_queue.h"


void initialize_ai();

move_t get_next_move( uint8_t board[SIZE][SIZE], int max_depth,
            propagation_t propagation, int* node_count, int* generated_count);


void graph_init(node_t** node);

node_t* apply_action(node_t* node, move_t action, uint8_t board[SIZE][SIZE]);

void copy_board(uint8_t src[SIZE][SIZE], uint8_t dest[SIZE][SIZE]);

void propagate_score(node_t* node, move_t* best_action, uint32_t* max_score,
                                    int first_action[SIZE]);


#endif
