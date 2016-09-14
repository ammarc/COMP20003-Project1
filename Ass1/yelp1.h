/* Created by: Ammar Ahmed
 * University of Melbourne ID: 728926
 */

/* Note: that 1 and 2 is added to accomodate for the null byte and the extra
 * space at the end of the data field */
#define NAMEBUFFER 64 + 1
#define DATABUFFER 1465 + 2

/* Defining a special data type for the key and the data so that the
 * appropriate space can be allocated */
typedef char my_key[NAMEBUFFER+1];
typedef char my_data[DATABUFFER+1];

/* Defining tree struct type here as it is recursive data structure */
typedef struct node tree_t;

/* Defining a BST node with left, right node and parent nodes */
struct node
{
    my_key key;
    my_data yelpdata;
    tree_t* parent;
    tree_t* left;
    tree_t* right;
};

/* Defining a function for bst insertion. It takes
 * the pointer to the pointer to the tree as the pointer to the tree
 * is changed in the function
 * it takes the parent pointer to keep track of where it is in the tree
 * it also takes the key and data it needs to insert */
void bst_insert(tree_t **t, tree_t *parent, my_key k, my_data ydata);

/* Let us define a function to search a BST and then insert the found
 * records into the output file
 * it takes a pointer to the tree, a file pointer and also has
 * a flag which is set to 1 once an entry with the input key is found */
int bst_search_insert(tree_t *t, my_key k, FILE *fp, int found_flag);

/* This funciton reads the data from the source file and then feeds that
 * into the bst_insert funciton */
void insert_from_file(char *file, tree_t **t);
