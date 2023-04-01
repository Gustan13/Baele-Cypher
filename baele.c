#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphalib.h"

#define ASCII_TABLE 127
#define ASCII_RAND_OFFSET 94
#define ASCII_SPACE 32

int main (int argc, char *argv[])
{
    alpha_t* alpha = createAlpha();
    FILE* file = fopen("exemplo.txt", "r");

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

    // for (int i = 0; i < 5; i++) {
    //     letter_t* letter = createLetter((rand() % 94) + 32);
    //     insertLetter(alpha, letter);
    // }

    for (letter_t* i = alpha->first; i != NULL; i = i->prox) {
        printf("%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++) {
            printf("%d ", i->codes[j]);
        }
        printf("\n");
    }

    alpha = destroyAlpha(alpha);
    free(c);

    return 0;
}