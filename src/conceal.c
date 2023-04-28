#include <stdio.h>
#include <stdlib.h>

#include "conceal.h"
#include "linkedlib.h"

// RECEBE ARQUIVO DE MENSAGEM, ARQUIVO DE ESCRITA E UMA LISTA
// CODIFICA A MENSAGEM DE ACORDO COM A LISTA E ESCREVE NO ARQUIVO DE ESCRITA
// RETORNA SUCCESS CASO FUNCIONAR E FAILURE CASO CONTRÁRIO
int cypherMessage(FILE* message, FILE* returnFile, list_t* list) {
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

        letter_t* t = findLetter(list, c);
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