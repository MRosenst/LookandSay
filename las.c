/** [c90] las.c:  Generates the "look and say" sequence. 
 * i.e. a[0] = 1
 * So there is one "1". Therefore a[1] = 11 ("one one").
 * and so on: 1, 11, 21, 1211, 111221, 312211, 13112221 ...
 * A property of this sequence is that all digits are 1s, 2s, and 3s.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

/* This macro is the main algorithm in the say part of "look and say" */
#define SAY(n) { \
                if (count[(n)]) { \
                    cur[j++] = count[(n)] + '0'; \
                    cur[j++] = (n) + '0'; \
                    count[(n)] = 0; \
                    MEM_ERR(prev, cur) \
                } \
}

/* Checking for out of bounds. reallocate double the memory if so.
 * n specifies a buffer, op specifies operation [+ or *] (no need to double
 * if we're only off by a bit) */
#define MAX_ERR(n, op) { \
        if (i >= prev_size - (n) || j >= cur_size - (n)) { \
            prev = (char *) realloc(prev, prev_size op 2); \
            prev_size = prev_size op 2; \
            cur = (char *) realloc(cur, cur_size op 2); \
            cur_size = cur_size op 2; \
            free(tmp); \
            tmp = (char *) malloc(cur_size); \
        } \
}

#define INPUT_ERR() { \
    printf("error:  invalid input\n"); \
    exit(1); \
}

#define MEM_ERR(a, b) { \
    if ( !(a && b) ) { \
        printf("error:  memory allocation failed\n"); \
        exit(1); \
    } \
}

char *las(int);

int prev_size = MAX;
int cur_size = MAX;
char *tmp;

/* main:  receives n (as in nth element) and [optional] memory threshold (MAX) from the user 
 * and prints the output of las(n) */
int main(int argc, char **argv) {
    char *p1, *p2;
    int n;

    /* There should be exactly two inputs */
    if (argc != 2) {
        INPUT_ERR()
    }
    
    /* Output */
    if ((n = atoi(argv[1])) || !strcmp(argv[1], "0")) {
        p1 = (char *) malloc(MAX);
        p2 = (char *) malloc(MAX);

        MEM_ERR(p1, p2)
        
        printf("%s\n", las(n));
        
        free(p1);
        free(p2);
        free(tmp);
        return 0;
    }
    
    INPUT_ERR()
}


/* las: calculates the nth element of the "look and say" series.
   prev and cur are required as string memory. */
char *las(int n) {
    char c, *prev, *cur;
    int i, j;
    /* I might be using an array starting from 1... pls don't hurt me */
    int count[] = {0, 0, 0, 0};
    
    /* Base case n=0 */
    if (!n)
        return "1";
    
    /* n > 0 */
    prev = (char *) malloc(prev_size);
    cur = (char *) malloc(cur_size);
    MEM_ERR(prev, cur)
    strcpy(prev, las(n-1));

    /* iterate over the chars of the previous element in the series */
    for (i = 0, j = 0; (c = prev[i]) != '\0'; i++) { 

        MAX_ERR(20, *)

        /* The "look" part of the algorithm */
        switch (c - '0') {
            case 1:
                count[1]++;
                SAY(2)
                SAY(3)
                break;
            
            case 2:
                count[2]++;
                SAY(1)
                SAY(3)
                break;
            
            case 3:
                count[3]++;
                SAY(1)
                SAY(2)
                break;
        }
    }
    
    /* Say what hasn't been said yet */
    SAY(1)
    SAY(2)
    SAY(3)
    
    MAX_ERR(10, +)
    cur[j++] = '\0';

    strcpy(tmp, cur);

    free(prev);
    free(cur);

    return tmp;
}
