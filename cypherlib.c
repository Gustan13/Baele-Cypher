#include <stdio.h>
#include <stdlib.h>

#include "cypherlib.h"

int createCypher(FILE* file, alpha_t* alpha) {
    char *c = malloc(sizeof(char) * 45);
    letter_t* aux;

    int i = 0;

    while (fscanf(file, " %s", c) == 1) {
        if (hasLetter(alpha, c[0]) == 1) {
            aux = createLetter(c[0]);
            insertLetter(alpha, aux);
        }
        addCode(alpha, c[0], i);
        i++;
    }

    free(c);
    c = NULL;

    return 0;
}