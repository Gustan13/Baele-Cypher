#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cypherlib.h"
#include "conceal.h"
#include "deconceal.h"
#include "linkedlib.h"

#define ASCII_TABLE 127
#define ASCII_RAND_OFFSET 94
#define ASCII_SPACE 32

int main (int argc, char *argv[])
{
    int next_option;

    int hasCodeFlag = 0; // -e
    int hasDecodeFlag = 0; // -d
    int hasBook = 0; // -b
    int hasCypher = 0; // c
    int hasOrigMessage = 0; // -m
    int hasCodeMessage = 0; // -i
    int hasWriteFile = 0; // -o & mensagem decodificada

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
    };

    list_t* list = createList();

    if (hasCodeFlag && hasBook && hasCypher && hasOrigMessage && hasWriteFile) {
        book = fopen(bookName, "r");
        cypher = fopen(cypherName, "w");
        originalMessage = fopen(originalMessName, "r");
        writeFile = fopen(writeFileName, "w");

        createCypherFromBook(book, list);
        printCypherToFile(cypher, list);
        cypherMessage(originalMessage, writeFile, list);

        fclose(cypher);
        fclose(originalMessage);
        fclose(writeFile);
        fclose(book);
    } else if (hasDecodeFlag && hasCodeMessage && hasCypher && hasWriteFile) {
        cypher = fopen(cypherName, "r");
        originalMessage = fopen(codedMessName, "r");
        writeFile = fopen(writeFileName, "w");

        createCypherFromKeyFile(cypher, list);
        decypherMessage(originalMessage, writeFile, list);

        fclose(cypher);
        fclose(originalMessage);
        fclose(writeFile);
    } else if (hasDecodeFlag && hasCodeMessage && hasBook && hasWriteFile) {
        book = fopen(bookName, "r");
        originalMessage = fopen(codedMessName, "r");
        writeFile = fopen(writeFileName, "w");

        createCypherFromBook(book, list);
        decypherMessage(originalMessage, writeFile, list);

        fclose(book);
        fclose(originalMessage);
        fclose(writeFile);
    } else {
        perror("Something went wrong.");
        return 1;
    }

    list = destroyList(list);

    return 0;
}