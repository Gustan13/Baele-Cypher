#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphalib.h"
#include "cypherlib.h"

#define ASCII_TABLE 127
#define ASCII_RAND_OFFSET 94
#define ASCII_SPACE 32

int main (int argc, char *argv[])
{
    alpha_t* alpha = createAlpha();
    FILE* file = fopen("exemplo.txt", "r");

    createCypher(file, alpha);

    for (letter_t* i = alpha->first; i != NULL; i = i->prox) {
        printf("%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++) {
            printf("%d ", i->codes[j]);
        }
        printf("\n");
    }

    alpha = destroyAlpha(alpha);

    return 0;
}