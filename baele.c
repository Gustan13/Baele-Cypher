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

    FILE* file = fopen("textos/exemplo.txt", "r");
    if (file == NULL) {
        perror("File could not be loaded");
        return 1;
    }

    FILE* cypher = fopen("textos/cifra.txt", "w+");
    if (cypher == NULL) {
        perror("File could not be loaded");
        return 1;
    }

    FILE* message = fopen("textos/message.txt", "r");
    if (message == NULL) {
        perror("File could not be loaded");
        return 1;
    }

    createCypher(file, alpha);

    printCypher(cypher, alpha);

    cypherMessage(message, alpha);

    alpha = destroyAlpha(alpha);

    fclose(file);
    fclose(file);
    fclose(file);

    return 0;
}