#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypherlib.h"

long findSizeOfFile(FILE* file) {
    long size;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);

    rewind(file);

    return size;
}

int createCypherFromBook(FILE* book, alpha_t* alpha) {
    char *c = malloc(sizeof(char) * 45);
    letter_t* aux;

    int i = 0;

    while (fscanf(book, " %s", c) == 1) {
        if (hasLetter(alpha, c[0]) == 1) {
            aux = createLetter(c[0]);
            insertLetter(alpha, aux);
        }
        addCode(alpha, c[0], i);
        i++;
    }

    free(c);
    c = NULL;

    return 0;
}

// FIX
int createCypherFromKeyFile(FILE* keys, alpha_t* alpha) {
    long size = findSizeOfFile(keys);
    char *line = malloc(sizeof(char) * size);

    while (fgets(line, size, keys) != NULL) {
        char* token = strtok(line, ":");
        char c = token[0];

        letter_t* letter = createLetter(c);
        insertLetter(alpha, letter);

        while (token != NULL) {
            token = strtok(NULL, " ");

            printf("%s ", token);

            if (token != NULL) {
                addCode(alpha, c, atoi(token));
            }
        }
        puts("\n");
    }

    return 0;
}

int printCypherToFile(FILE* toWrite, alpha_t* alpha) {
    for (letter_t* i = alpha->first; i != NULL; i = i->prox) {
        fprintf(toWrite, "%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++)
            fprintf(toWrite, "%d ", i->codes[j]);
        fprintf(toWrite, "\n");
    }

    return 1;
}

int cypherMessage(FILE* message, FILE* returnFile, alpha_t* alpha) {
    int* message_d = malloc(sizeof(int));
    int size = 0;

    do {
        char c = fgetc(message);

        if (c == 32) {
            size++;
            message_d = realloc(message_d, sizeof(int) * size);
            message_d[size - 1] = -1;
            continue; 
        }

        letter_t* t = findLetter(alpha, c);
        if (t != NULL) {
            size++;
            message_d = realloc(message_d, sizeof(int) * size);
            message_d[size - 1] = t->codes[rand() % t->numCodes]; 
        }
    }
    while (!feof(message));
    
    for (int i = 0; i < size; i++)
        fprintf(returnFile, "%d ", message_d[i]);

    free(message_d);
    message_d = NULL;

    return 1;
}

int decypherMessage_type_b(FILE* message, FILE* returnFile, alpha_t* alpha) {
    char* mensagem_d = malloc(sizeof(char));
    int size = 0;

    do {
        char* c = malloc(sizeof(char) * 46);
        char aux = '0';
        int num = 0;

        size++;
        mensagem_d = realloc(mensagem_d, sizeof(char) * size);

        fscanf(message, "%s", c);

        num = atoi(c);
        aux = findLetterFromNum(alpha, num);

        if (c[0] != '-') {
            mensagem_d[size - 1] = aux;
        } else {
            mensagem_d[size - 1] = 32;
        }

        free(c);
        c = NULL;

    } while (!feof(message));

    for (int i = 0; i < size - 1; i++)
        fprintf(returnFile, "%c", mensagem_d[i]);

    free(mensagem_d);
    mensagem_d = NULL;

    return 1;
}