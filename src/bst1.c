/* Created by: Ammar Ahmed
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yelp1.h"


/* A recursive tree insertion algorithm is used here which inserts a new
 * node if a pointer to a tree is NULL, puts it to the left (calls itself)
 * if the keys are less than the current tree key or to the right, otherwise */
void bst_insert(tree_t **t, tree_t *parent, my_key k, my_data ydata)
{
    if (*t == NULL)
    {
	   /* creating a temporary tree pointer */
       tree_t *p;

       /* allocate new node */
       p = malloc(sizeof(*p));

       /* initialize and copy values to all of the relevant fields and the
        * assign the current pointer to the tree to this temporary pointer */
       strcpy(p->key, k);
       strcpy(p->yelpdata, ydata);
       p->left = p->right = NULL;
       p->parent = parent;
       *t = p;
	   return;
    }

    if (strcmp(k, (*t)->key) < 0)
    {
        bst_insert(&((*t)->left), *t, k, ydata);
    }
    else
    {
        bst_insert(&((*t)->right), *t, k, ydata);
    }
}


/* In this funciton the input key is compared with the current tree's key
 * and if there is a match the key's data is written to the input file.
 * Otherwise the funciton calls itself with the left or right key and adds
 * 1 as the number of comparisons would have increased by 1.
 * Also note, that once a match is found, the found flag is set as true.
 * This is to make sure that NOTFOUND is written only when there is no
 * match of it found in the whole tree. */
int bst_search_insert(tree_t *t,my_key k, FILE *fp, int found_flag)
{
    if (t != NULL)
    {
    	if (strcmp(t->key, k) == 0)
    	{
        	fprintf(fp, "%s --> %s\n", k, t->yelpdata);
        	return bst_search_insert(t->right, k, fp, 1)+1;
		}

    	/* Now the function will look to the left or right if the value
     	 * pointed towards if less than or greater than the key, respectively
     	 * and then calls itself with one of those left/right pointers */
     	if (strcmp(k, t -> key) < 0)
     	{
         	return bst_search_insert(t->left, k, fp, found_flag) + 1;
     	}
     	else if (strcmp(k, t -> key) > 0)
     	{
         	return bst_search_insert(t->right, k, fp, found_flag) + 1;
     	}
	}

    /* Note that t could be NULL even if a match was found earlier, so we have
     * to use this extra condition to ensure that no match was found in the
     * entire tree */
    if (found_flag == 0)
    {
        fprintf(fp, "%s --> NOTFOUND\n", k);
    }
    return 0;
}

/* The input file is opened here first and then read character-by-character.
 * The string is then parsed only if a new-line or a comma is reached. It
 * then adds the null byte to the character array to make it a string and
 * resets the array index. When both the name and data are extracted in this
 * way, they are then sent to the bst_insert funciton to be inserted into
 * the BST. */
void insert_from_file(char *file, tree_t **t)
{
    FILE *fp = fopen(file, "r");
    char name [NAMEBUFFER];
    char data [DATABUFFER];
    char c [DATABUFFER];
    char ch;
    int c_index = 0;

    while ((ch = fgetc(fp))!= EOF)
    {
        if(ch == ',')
        {
            c[c_index] = '\0';
            strcpy(name, c);
            c_index = 0;
        }
        else if( ch == '\n')
        {
            c[c_index] = '\0';
            strcpy(data, c);

            bst_insert(t, NULL , name, data);
            c_index = 0;
        }
        else
        {
            c[c_index] = ch;
            c_index++;
        }
    }
    fclose(fp);
}
