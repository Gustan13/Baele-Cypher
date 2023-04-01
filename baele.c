#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypherlib.h"

#define ASCII_TABLE 127
#define ASCII_RAND_OFFSET 94
#define ASCII_SPACE 32

int main (int argc, char *argv[])
{
    alpha_t* alpha = createAlpha();
    FILE* file = fopen("exemplo.txt", "r");
    FILE* cypher = fopen("cifra.txt", "w");

    createCypher(file, alpha);

    printCypher(cypher, alpha);

    alpha = destroyAlpha(alpha);

    fclose(file);

    return 0;
}