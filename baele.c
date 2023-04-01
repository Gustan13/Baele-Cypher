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

    char *c = malloc(sizeof(char) * 50);
    letter_t* aux;

    for (int i = 0; i < 18; i++) {
        fscanf(file, " %s", c);
        if (hasLetter(alpha, c[0]) < 1)
            continue;
        aux = createLetter(c[0]);
        insertLetter(alpha, aux);
    }

    // for (int i = 0; i < 5; i++) {
    //     letter_t* letter = createLetter((rand() % 94) + 32);
    //     insertLetter(alpha, letter);
    // }

    for (letter_t* i = alpha->first; i != NULL; i = i->prox)
        printf("%c ", i->character);

    return 0;
}