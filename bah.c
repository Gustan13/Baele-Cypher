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
    int next_option;

    int hasCodeFlag = -1; // -e
    int hasDecodeFlag = -1; // -d
    int hasBook = -1; // -b
    int hasCypher = -1; // c
    int hasOrigMessage = -1; // -m
    int hasCodeMessage = -1; // -i
    int hasWriteFile = -1; // -o & mensagem decodificada

    char* bookName;
    char* cypherName;
    char* originalMessName;
    char* codedMessName;
    char* writeFileName;

    FILE* writeFile;
    FILE* book;
    FILE* cypher;
    FILE* originalMessage;

    if (argc < 5) {
        perror("Not enough arguments. Usage:\n");
        return 1;
    }

    while ((next_option = getopt(argc, argv, "edo:b:c:m:i:")) != -1) {
        switch (next_option)
        {
        case 'e':
            hasCodeFlag = 1;
            break;
        
        case 'd':
            hasDecodeFlag = 1;
            break; 

        case 'o':
            hasWriteFile = 1;
            writeFileName = optarg;
            break;

        case 'b':
            hasBook = 1;
            bookName = optarg;
            break;

        case 'c':
            hasCypher = 1;
            cypherName = optarg;
            break;

        case 'm':
            hasOrigMessage = 1;
            originalMessName = optarg;
            break;

        case 'i':
            hasCodeMessage = 1;
            codedMessName = optarg;
            break;

        default:
            perror("Something went wrong\n");
            return 1;
        }
    }

    alpha_t* alpha = createAlpha();

    // if (hasCodeFlag && hasBook && hasCypher && hasOrigMessage && hasWriteFile) {
    //     book = fopen(bookName, "r");
    //     cypher = fopen(cypherName, "w+");
    //     originalMessage = fopen(originalMessName, "r");
    //     writeFile = fopen(writeFileName, "w+");

    //     createCypherFromBook(book, alpha);
    //     printCypherToFile(cypher, alpha);
    //     cypherMessage(originalMessage, writeFile, alpha);

    //     fclose(writeFile);
    //     fclose(cypher);
    //     fclose(originalMessage);
    //     fclose(book);

    //     puts("Message Encoded");

    // } else if (hasDecodeFlag && hasCodeMessage && hasCypher && hasWriteFile) {
    //     cypher = fopen(cypherName, "r");
    //     originalMessage = fopen(codedMessName, "r");
    //     writeFile = fopen(writeFileName, "w+");

    //     createCypherFromKeyFile(cypher, alpha);
    //     decypherMessage(originalMessage, writeFile, alpha);

    //     fclose(writeFile);
    //     fclose(cypher);
    //     fclose(originalMessage);

    //     puts("Message Decoded");

    // } else if (hasDecodeFlag && hasCodeMessage && hasBook && hasWriteFile) {
    //     book = fopen(bookName, "r");
    //     originalMessage = fopen(codedMessName, "r");
    //     writeFile = fopen(writeFileName, "w+");

    //     createCypherFromBook(book, alpha);
    //     decypherMessage(originalMessage, writeFile, alpha);

    //     fclose(writeFile);
    //     fclose(book);
    //     fclose(originalMessage);

    //     puts("Message Decoded");
    // }

    book = fopen(bookName, "r");
    puts(cypherName);
    cypher = fopen(cypherName, "w");
    originalMessage = fopen(originalMessName, "r");
    writeFile = fopen(writeFileName, "w+");

    createCypherFromBook(book, alpha);
    printCypherToFile(cypher, alpha);
    cypherMessage(originalMessage, writeFile, alpha);

    fclose(writeFile);
    fclose(cypher);
    fclose(originalMessage);
    fclose(book);

    puts("Message Encoded");

    alpha = destroyAlpha(alpha);

    return 0;
}