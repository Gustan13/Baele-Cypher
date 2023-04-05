#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cypherlib.h"

#define ASCII_TABLE 127
#define ASCII_RAND_OFFSET 94
#define ASCII_SPACE 32

int main (int argc, char *argv[])
{
    char next_option;
    char c_type;

    FILE* writeFile;
    FILE* book;
    FILE* cypher;
    FILE* originalMessage;

    while ((next_option = getopt(argc, argv, "edo:b::c::m::i::")) != -1) {
        switch (next_option)
        {
        case 'e':
            c_type = 'e';
            break;
        
        case 'd':
            c_type = 'd';
            break; 

        case 'o':
            writeFile = fopen(optarg, "w");
            if (writeFile == NULL) {
                perror("File not loaded");
                return 1;
            }
                
            break;

        case 'b':
            book = fopen(optarg, "r");
            break;

        case 'c':
            if (c_type == 'e')
                cypher = fopen(optarg, "w");
            else
                cypher = fopen(optarg, "r");
            break;

        case 'm':
            originalMessage = fopen(optarg, "r");
            break;

        case 'i':
            originalMessage = fopen(optarg, "r");
            break;

        default:
            perror("Something went wrong\n");
            return 1;
        }

        if (c_type != 'e' && c_type != 'd') {
            puts("Bruh");
            return 1;
        }
    }

    alpha_t* alpha = createAlpha();

    if (c_type == 'd') {
        if (book != NULL)
            createCypherFromBook(book, alpha);
        else
            createCypherFromKeyFile(cypher, alpha);

        decypherMessage_type_b(originalMessage, writeFile, alpha);

        puts("Message Decoded");
    }
    else {
        createCypherFromBook(book, alpha);
        printCypherToFile(cypher, alpha);
        cypherMessage(originalMessage, writeFile, alpha);

        puts("Message Encoded");
    }

    // createCypherFromKeyFile(cypher, alpha);

    // printAlpha(alpha);

    // cypherMessage(dMessage, message, alpha);

    // decypherMessage_type_b(dMessage, message, alpha);

    alpha = destroyAlpha(alpha);

    fclose(writeFile);
    fclose(cypher);
    fclose(originalMessage);
    fclose(book);

    return 0;
}