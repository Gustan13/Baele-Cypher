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
        for (int j = 0; j < i->numCodes; j++)
            fprintf(toWrite, "%d ", i->codes[j]);
        fprintf(toWrite, "\n");
    }

    return 1;
}

int cypherMessage(FILE* message, alpha_t* alpha) {
    int* message_d;
    int size = 0;

    do {
        char c = fgetc(message);

        size++;
        message_d = realloc(message_d, sizeof(int) * size);

        if (c == 32) {
            message_d[size - 1] = -1;
            continue; 
        }

        letter_t* t = findLetter(alpha, c);
        if (t != NULL) {
            message_d[size - 1] = t->codes[rand() % t->numCodes]; 
        }
    }
    while (!feof(message));
    
    for (int i = 0; i < size - 1; i++)
        printf("%d ", message_d[i]);

    free(message_d);
    message_d = NULL;

    return 1;
}