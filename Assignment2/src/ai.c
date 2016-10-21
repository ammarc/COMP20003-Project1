#include <time.h>
#include <stdlib.h>
#include "ai.h"
#include "utils.h"
#include "priority_queue.h"

struct heap h;

void initialize_ai(){
	heap_init(&h);
}

/**
 * Find best action by building all possible paths up to depth max_depth
 * and back propagate using either max or avg
 */

move_t get_next_move(uint8_t board[SIZE][SIZE], int max_depth,
			propagation_t propagation, int* node_count, int* expand_count)
{
	/** We keep the random variable here if our Algorithm doesn't set one
	  * or other exception occur. Other variables are also set for this
	  * function */
	move_t best_action = rand() % 4;
	uint32_t max_score = 0;
	int i;

	node_t* node;
	graph_init(&node);
	node->parent = NULL;
	(*node_count)++;

	/** Creating an array to store only the priorities of the first actions
	  * Each value is initialized to -1 so as to distinguish it from the
	  * move_t values used in this game */
	int first_action[SIZE];
	for (i = 0; i < SIZE; i++)
	{
		first_action[i] = -1;
	}

	/** A copy of the board is made and stored for each node. Also note here
	  * that we use a heap for the explored array as it would be more feasible
	  * to do so as we don't want redundant functions. And for our purposes,
	  * the complexity of entering data into the heap is tolerable. */
	copy_board(board, node->board);

	struct heap exploredArr;
	heap_init(&exploredArr);

	struct heap frontier;
	heap_init(&frontier);

	heap_push(&frontier, node);


	/** Below is essentially the application of the given graph algorithm. Note
	  * how the variables like number of expanded nodes are also updated here
	  * by dereferencing their pointers. */
	while ((&frontier)->count != 0)
	{
		node = heap_delete(&frontier);
		(*expand_count)++;

		heap_push(&exploredArr, node);
		if(node->depth < max_depth)
		{
			move_t action;
			for (action = 0; action <= 3; ++action)
			{
				node_t* new_node = apply_action(node, action, node->board);
				(*node_count)++;
				if (!(new_node->is_same_board))
				{
					heap_push(&frontier, new_node);
					propagate_score(new_node, &best_action, &max_score,
														first_action);
				}
				else
				{
					free(new_node);
					new_node = NULL;
				}
			}
		}
	}


	/** This part of the code is used only when we want to propagate by
	  * average. First the array used to store the scores of the first
	  * possible actions are looped through to check for no values (-1) and
	  * then the average is taken and then stored. And then the maximum
	  * average is picked and selected as the first action. */
	if (propagation == 1)
	{
		int array_max = 0;
		for (i = 0; i < SIZE; i++)
		{
			if (first_action[i] != -1)
			{
				first_action[i] = (int) (first_action[i] * 1.0 /
													max_depth * 1.0);
			}
		}

		for (i = 0; i < SIZE; i++)
		{
			if (first_action[i] > array_max)
			{
				array_max = first_action[i];
				best_action = (move_t) i;
			}
		}
	}

	/** Now we free all the data used in this instance of the graph search.
	  * Since both are structures are priority queues, we can use the
	  * emptyPQ() function. */
	emptyPQ(&exploredArr);
	emptyPQ(&frontier);
	return best_action;
}


/** This function is used to initialize a graph by setting a root node and
  * then allocating space for it. It's appropriate values are also set, like
  * depth and priority */
void graph_init(node_t** node)
{
	*node = (node_t*) malloc (sizeof(node_t));

	if(!(*node))
	{
		printf("Error allocating memory...\n");
	}
	else
	{
		(*node)->depth = 0;
		(*node)->priority = 0;
		(*node)->score = 0;
	}
}

/** This implements what is involved when applying an action. A new node is
  * created (and returned), pointing to its parent. Other variables like
  * depth, the move leading to its creation are also set. We use a boolean
  * variable to check if the board changed after the move or not (to decide
  * whether to apply the action). Also note that we use as the score as the
  * value by which the score changed when this action was applied. The scores
  * are summed and used for propagation using their prioriy. */
node_t* apply_action(node_t* node, move_t action, uint8_t board[SIZE][SIZE])
{
	node_t* new_node;
	graph_init(&new_node);
	new_node->parent = node;
	new_node->move = action;
	new_node->depth = node->depth + 1;

	copy_board(board, new_node->board);

	new_node->is_same_board = !(execute_move_t(new_node->board,
											&(new_node->score), action));

	new_node->priority = new_node->score;
	return new_node;
}


/** Since we need to have a copy of the original state of the board, to test
  * our best paths and not change the original state, we need the following
  * board-copying function */
void copy_board(uint8_t src[SIZE][SIZE], uint8_t dest[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			dest[i][j] = src[i][j];
		}
	}
}


/** The following score-propagation function is used by both average and
  * maximise modes, but in the case of averge propagation, a segment of code
  * is placed in get_next_move which takes the average of the possible first
  * actions. We traverse the graph from the bottom-up, checking whether we
  * have reached the parent node. We update the priority only when the
  * original score of the node added with the priority of its children makes
  * for a larger value so as we won't have a situation where a path is ranked
  * higher juse becuase of the sum of its paths produce a higher score
  * instead of just one path. We use first_action to store the maximum
  * scores for the first action nodes. */
void propagate_score(node_t* node, move_t* best_action, uint32_t* max_score,
							int first_action[SIZE])
{
	srand(time(NULL));
	int i = rand() % 2;
	while(node->parent != NULL)
	{
		if (((node->parent)->score + node->priority) >
											(node->parent)->priority)
		{
			(node->parent)->priority = node->priority + (node->parent)->score;
		}

		if ((node->parent)->parent == NULL)
		{
			if (node->priority > *max_score)
			{
				*max_score = node->priority;
				*best_action = node->move;
			}
			else if (node->priority == *max_score)
			{
				/** If get equal maxima, check with random variable i and
				  * update the next action based on the random value of i */
				if (i == 1)
				{
					*best_action = node->move;
				}
			}

			if ((int) node->priority > first_action[(int) node->move])
			{
				first_action[(int) node->move] = (int) node->priority;
			}
		}
		node = node->parent;
	}
}
