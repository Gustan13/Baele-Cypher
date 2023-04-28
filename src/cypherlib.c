#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypherlib.h"

// RECEBE UM PONTEIRO DE ARQUIVO
// RETORNA O TAMANHO DO ARQUIVO
long findSizeOfFile(FILE* file) {
    long size;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);

    rewind(file);

    return size;
}

// RECEBE UM ARQUIVO E UMA LISTA
// LÊ O ARQUIVO E CRIA A LISTA LINKADA DE ACORDO COM A CIFRA DE BEALE
// RETORNA SUCCESS CASO FUNCIONAR E FAILURE CASO CONTRÁRIO
int createCypherFromBook(FILE* book, list_t* list) {
    char *c = malloc(sizeof(char) * 100);
    letter_t* aux;

    int i = 0;

    while (fscanf(book, " %s", c) == 1) {
        if (hasLetter(list, c[0]) == 1) {
            aux = createLetter(c[0]);
            insertLetter(list, aux);
        }
        addCode(list, c[0], i);
        i++;
    }

    free(c);
    c = NULL;

    return 0;
}

// FIX
// RECEBE UM ARQUIVO E UMA LISTA
// LÊ O ARQUIVO E CRIA A LISTA LINKADA SEGUINDO A ESTRUTURA DA CIFRA
// RETORNA SUCCESS CASO FUNCIONAR E FAILURE CASO CONTRÁRIO
int createCypherFromKeyFile(FILE* keys, list_t* list) {
    long size = findSizeOfFile(keys);
    char *line = malloc(sizeof(char) * size);

    while (fgets(line, size, keys) != NULL) {
        char* token = strtok(line, ":");
        char c = token[0];

        letter_t* letter = createLetter(c);
        insertLetter(list, letter);

        while (token != NULL) {
            token = strtok(NULL, " ");

            //printf("%s ", token);

            if (token != NULL) {
                addCode(list, c, atoi(token));
            }
        }
        //puts("\n");
    }

    return 0;
}

// RECEBE ARQUIVO E LISTA
// IMPRIME A LISTA AO ARQUIVO
// RETORNA SUCCESS CASO FUNCIONAR E FAILURE CASO CONTRÁRIO
int printCypherToFile(FILE* toWrite, list_t* list) {
    for (letter_t* i = list->first; i != NULL; i = i->prox) {
        fprintf(toWrite, "%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++) {
            fprintf(toWrite, "%d ", i->codes[j]);
        }
        fprintf(toWrite, "\n");
    }

    return 1;
}

// RECEBE ARQUIVO DE MENSAGEM CODIFICADA, ARQUIVO DE ESCRITA E UMA LISTA
// DECODIFICA A MENSAGEM DE ACORDO COM A LISTA E ESCREVE NO ARQUIVO DE ESCRITA
// RETORNA SUCCESS CASO FUNCIONAR E FAILURE CASO CONTRÁRIO
int decypherMessage(FILE* message, FILE* returnFile, list_t* list) {
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
        aux = findLetterFromNum(list, num);

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