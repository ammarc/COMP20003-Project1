/* Created by: Ammar Ahmed
 * University of Melbourne ID: 728926
 */

 /* It is worthy to note that we have to header files to accomodate for the
  * different structures of the BST as in this one we have an additional
  * pointer to a list. This practice should save us some space that as we
  * won't have to store any additional information. */

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

/* Let us create a linked list to implement stage 2 */
typedef struct lst_node list_t;

/* Defining a BST node with left, right node and parent nodes. Note that
 * a list pointer is also added to implement Stage 2. */
struct node
{
    my_key key;
    my_data yelpdata;
    tree_t* parent;
    tree_t* left;
    tree_t* right;
    list_t* my_list;
};

/* Defining a node of list with a next pointer and a field for just storing
 * the data */
struct lst_node
{
    my_data yelpdata;
    list_t *next;
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
int bst2_search_insert(tree_t *t, my_key k, FILE *fp, int found_flag);

/* This funciton reads the data from the source file and then feeds that
 * into the bst_insert funciton */
void insert_from_file(char *file, tree_t **t);

/* Function to insert into our linked list for duplicate keys */
void list_insert(list_t **l, my_data ydata);
