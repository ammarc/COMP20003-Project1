/* Created by: Ammar Ahmed
 */

/* Note that we have 2 versions of each source file due to their fucntional
 * definitions. They can easily be exported to any other program. The header
 * files are also different to avoid conflict with the different structures
 * from Stage 1 and 2. This should also save us some space and Stage 2 has
 * additional information in the BST. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "yelp1.h"

int main (int argc, char *argv[])
{
    int j;
    char myinput[NAMEBUFFER];
    tree_t *tree  = NULL;

    insert_from_file(argv[1] , &tree);

    /* Now we will open the output file here so that we can pass
     * the pointer directly into the search function and file can be
     * passed recursively */
    FILE *fp = fopen(argv[2], "w");

    /* We use fgets here to get the entire line rather than
     * words separted by space from stdin */
    while (fgets(myinput, NAMEBUFFER, stdin))
    {
        /* Remove the newline character from stdin */
        strtok(myinput, "\n");
        j = bst_search_insert(tree, myinput, fp, 0);
	    printf("%s --> %d\n", myinput, j);
    }

    /* Closing the output data file */
    fclose(fp);

    return 0;
}
