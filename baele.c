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

    FILE* message = fopen("textos/message.txt", "w");
    if (message == NULL) {
        perror("File could not be loaded");
        return 1;
    }

    FILE* dMessage = fopen("textos/dMessage.txt", "r");
    if (dMessage == NULL) {
        perror("File could not be loaded");
        return 1;
    }

    createCypherFromBook(file, alpha);

    printCypherToFile(cypher, alpha);

    //cypherMessage(dMessage, message, alpha);

    decypherMessage_type_b(dMessage, message, alpha);

    alpha = destroyAlpha(alpha);

    fclose(file);
    fclose(cypher);
    fclose(message);
    fclose(dMessage);

    return 0;
}