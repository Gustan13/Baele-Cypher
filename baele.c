#include <stdio.h>
#include <stdlib.h>

#include "alphalib.h"

#define ASCII_TABLE 127
#define ASCII_RAND_OFFSET 94
#define ASCII_SPACE 32

int main (int argc, char *argv[])
{
    alpha_t* alpha = createAlpha();

    for (int i = 0; i < 5; i++) {
        letter_t* letter = createLetter((rand() % 94) + 32);
        insertLetter(alpha, letter);
    }

    for (letter_t* i = alpha->first; i != NULL; i = i->prox)
        puts(&i->character);

    return 0;
}