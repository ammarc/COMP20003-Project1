/* Created by: Ammar Ahmed
 * University of Melbourne ID: 728926
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "yelp2.h"

/* making the basic program */
int main (int argc, char *argv[])
{
    int j;
    char myinput[NAMEBUFFER];
    char outcome[DATABUFFER];
    tree_t *tree  = NULL;
    char searchterm [NAMEBUFFER];

    insert_from_file(argv[1] , &tree);
    /* now we will open the output file */
    FILE *fp = fopen(argv[2], "w");

    /* we use fgets here to get the entire line rather than
     * words separted by space from stdin */
    while (fgets(myinput, NAMEBUFFER, stdin))
    {
        /* remove the newline character from the input */
        strtok(myinput, "\n");
        j = bst2_search_insert(tree, myinput, fp, 0);
	    printf("%s --> %d\n", myinput, j);
    }

    /* closing the input data file */
    fclose(fp);

    return 0;
}
