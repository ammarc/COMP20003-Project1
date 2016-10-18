#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PTRS 3

int main (int argc, char *argv[]){
    char *p[PTRS];
    size_t nbytes = 10;
    int i;

    for (i = 0; i < PTRS; i++) {
        printf("malloc of %6lu bytes ", nbytes);
        if ((p[i] = (char *) malloc (nbytes)) == NULL) {
            printf("failed\n");
        } else {
            printf("succeeded\n");
        }
        nbytes *= 100;
    }

    /* now freeing the memory allocated */
    for (i = 0; i < PTRS; i++) {
        if (p[i]) {
            free (p[i]);
            p[i] = NULL;
        }
    }
    
    return 0;
}
