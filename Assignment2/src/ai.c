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

move_t get_next_move(uint8_t board[SIZE][SIZE], int max_depth, propagation_t propagation)
{
	//we keep the random variable here if our Algorithm doesn't set one
	move_t best_action = rand() % 4;
	uint32_t max_score = 0;
	//move_t best_action;
	//creating a new graph (a root node)
	node_t* node;
	graph_init(&node);
	node->parent = NULL;


	//uint8_t** node_board = NULL;
	copy_board(board, node->board);

	//initBoard(board, &max_score);

	//printf("%d %d\n", board[1][1], node->board[1][1]);

	//Now, let us try to use the given heap as our explored array
	//Since it will also contain nodes and will have to be dynamic
	struct heap exploredArr;
	heap_init(&exploredArr);


	//Making frontier
	struct heap frontier;
	heap_init(&frontier);

	//Adding node to frontier
	heap_push(&frontier, node);

	while ((&frontier)->count != 0)
	{
		//assuming this is the pop() funciton
		node = heap_delete(&frontier);

		heap_push(&exploredArr, node);

		if(node->depth < max_depth)
		{
			move_t action;
			for (action = 0; action <= 3; ++action)
			{
				node_t* new_node = apply_action(node, action, node->board);

				if (!(new_node->is_same_board))
				{
					heap_push(&frontier, new_node);
					//update best action
					propagate_score(new_node, &best_action, &max_score);
					//if max must lead to max score and avg score for avg
				}
				else
				{
					//delete newNode
					free(new_node);
					new_node = NULL;
					node->num_childs -= 1;
				}
			}
		}
	}


	//freeing that node
	//free(node);

	//free all explored nodes
	/*
	int i;
	for (i = 0; i < (&exploredArr)->count; i++)
	{
		free((&exploredArr)->heaparr[i]);
	}
	*/

	//freeing the explored array and frontier
	emptyPQ(&exploredArr);
	emptyPQ(&frontier);

	//free everything

	//pick best action randomly

	return best_action;
}

//let us define the graph initialization function
//perhaps change name to node init?
void graph_init(node_t** node)
{

	//basically allocating space
	*node = (node_t*) malloc (sizeof(node_t));

	//Malloc error check
	if(!(*node))
	{
		printf("Error allocating memory...\n");
	}
	else
	{
		(*node)->depth = 0;
		(*node)->num_childs = 0;
		(*node)->priority = 0;
		(*node)->score = 0;
	}
}

node_t* apply_action(node_t* node, move_t action, uint8_t board[SIZE][SIZE])
{

	//create new node, and point it to the parent
	node_t* new_node;
	graph_init(&new_node);
	new_node->parent = node;
	new_node->move = action;
	new_node->depth = node->depth + 1;
	node->num_childs += 1;

	copy_board(board, new_node->board);

	//update board with action chosen
	//We assume this has built-in validation check if e.g. edge is reached
	new_node->is_same_board = !(execute_move_t(new_node->board, &(new_node->score), action));

	new_node->priority = new_node->score;

	//update PQ with new score
	return new_node;
}

//Used to copy one board array onto another
void copy_board(uint8_t src[SIZE][SIZE], uint8_t dest[SIZE][SIZE])
{
	int i;
	int j;

	/*
	if ((dest = malloc(SIZE * sizeof(uint8_t*))) == NULL)
	{
		printf("Error allocating memory...\n");
	}

	for (i = 0; i < SIZE; i++)
	{

  		if (( dest[i] = malloc(SIZE * sizeof(uint8_t))) == NULL )
  		{
			printf("Error allocating memory...\n");
		}
	}
	*/
	//Let us now copy the array content
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			dest[i][j] = src[i][j];
		}
	}

}

void propagate_score(node_t* node, move_t* best_action, uint32_t* max_score)
{
	while(node->parent != NULL)
	{
		if(((node->parent)->score + node->priority) > (node->parent)->priority)
		{
			(node->parent)->priority = node->priority + (node->parent)->score;
		}


		if (((node->parent)->parent == NULL) && (node->priority > *max_score))
		{
			*max_score = node->priority;
			//printf("max_score is %d\n", max_score);
			*best_action = node->move;
		}


		//not sure about this:
		node = node->parent;
	}
}
