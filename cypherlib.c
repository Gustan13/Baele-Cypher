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

int printCypher(FILE* toWrite, alpha_t* alpha) {
    for (letter_t* i = alpha->first; i != NULL; i = i->prox) {
        fprintf(toWrite, "%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++) {
            if (j != i->numCodes -1) 
                fprintf(toWrite, "%d ", i->codes[j]);
            else
                fprintf(toWrite, "\n");
        }
    }

    return 1;
}