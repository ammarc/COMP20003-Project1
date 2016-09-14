/* Created by: Ammar Ahmed
 * University of Melbourne ID: 728926
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yelp2.h"

/* This funciton is exactly the same as our funciton for Stage 1 but implements
 * Stage 2 by inserting duplicate records into a linked list. */
void bst2_insert(tree_t **t, tree_t *parent, my_key k, my_data ydata)
{
    if (*t == NULL)
    {
       tree_t *p;

       p = malloc(sizeof(*p));

       strcpy(p->key, k);
       strcpy(p->yelpdata, ydata);
       p->left = p->right = NULL;
       p->my_list = NULL;
       p->parent = parent;
       *t = p;
	   return;
    }

    if (strcmp(k, (*t)->key) < 0)
    {
        bst2_insert(&((*t)->left), *t, k, ydata);
    }
    else if(strcmp(k, (*t)->key) == 0)
    {
        /* this recursively adds data onto our list */
        list_insert(&((*t)->my_list), ydata);
    }
    else
    {
        bst2_insert(&((*t)->right), *t, k, ydata);
    }
}


/* This function is also the same as our previous one but for the linked
 * list implementation. */
int bst2_search_insert(tree_t *t,my_key k, FILE *fp, int found_flag)
{
    if (t != NULL)
    {
    	if (strcmp(t->key, k) == 0)
    	{
        	fprintf(fp, "%s --> %s\n", k, t->yelpdata);

            /* Here we loop through all the next poiner until we find a NULL
             * pointer at which point we stop printing into the output file. */
            if (t->my_list != NULL)
            {
                list_t *list_ptr = t->my_list;
                while(list_ptr != NULL)
                {
                    fprintf(fp, "%s --> %s\n", k, list_ptr->yelpdata);
                    list_ptr = list_ptr->next;
                }

            }
        	return bst2_search_insert(t->right, k, fp, 1)+1;
		}

     	if (strcmp(k, t -> key) < 0)
     	{
         	return bst2_search_insert(t->left, k, fp, found_flag) + 1;
     	}
     	else if (strcmp(k, t -> key) > 0)
     	{
         	return bst2_search_insert(t->right, k, fp, found_flag) + 1;
     	}
	}

    if (found_flag == 0)
    {
        fprintf(fp, "%s --> NOTFOUND\n", k);
    }
    return 0;
}

/* A simple list insertion algorithm which recursively finds a NULL pointer
 * to the next node and then stores the data at that node. */
void list_insert(list_t **l, my_data ydata)
{
    if (*l == NULL)
    {
        list_t *p;

        p = malloc(sizeof(*p));
        p->next = NULL;
        strcpy(p->yelpdata, ydata);
        *l = p;
        return;
    }
    else
    {
        list_insert(&((*l)->next), ydata);
    }
}

/* Same function as in Stage 1 */
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

            bst2_insert(t, NULL , name, data);
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
