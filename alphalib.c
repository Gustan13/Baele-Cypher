#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "alphalib.h"

#define SUCCESS 0
#define FAILURE 1

//  RETORNA UMA ESTRUTURA ALPHA_T ALOCADA
alpha_t* createAlpha(void) {
    alpha_t *alpha = malloc(sizeof(alpha_t));
    
    alpha->first = NULL;
    alpha->last = NULL;
    alpha->numNodes = 0;

    return alpha;
}

//  RECEBE UM PONTEIRO DE ALPHABETO
//  RETORNA UM PONTEIRO DE ALPHABETO COMPLETAMENTE VAZIO
alpha_t* destroyAlpha(alpha_t* head) {
    letter_t* current = head->first;
    letter_t* temp;
    while (current != NULL) {
        temp = current;
        current = current->prox;
        free(temp->codes);
        temp->codes = NULL;
        free(temp);
        temp = NULL;
    }
    free(head);
    return NULL;
}

//  RECEBE CHAR
//  RETORNA PONTEIRO PARA UM LETTER_T CUJO CHARACTER É O CHAR RECEBIDO
letter_t* createLetter(char letter) {
    letter_t* letterNode = malloc(sizeof(letter_t));

    letterNode->character = letter;
    letterNode->numCodes = 0;
    letterNode->prev = NULL;
    letterNode->prox = NULL;

    return letterNode;
}

letter_t* findLetter(alpha_t* alpha, char letter) {
    for (letter_t* i = alpha->first; i != NULL; i = i->prox) {
        if (i->character == letter)
            return i;
    }
    return NULL;
}

int insertLetter(alpha_t* alpha, letter_t* letterNode) {
    letter_t* aux;

    if (findLetter(alpha, letterNode->character) != NULL)
        return FAILURE;

    if (alpha->first == NULL) {
        alpha->first = letterNode;
        alpha->last = letterNode;
        return SUCCESS;
    }

    if (letterNode->character < alpha->first->character) {
        aux = alpha->first;
        alpha->first = letterNode;
        letterNode->prox = aux;
        aux->prev = letterNode;
        return SUCCESS;
    }

    if (letterNode->character > alpha->last->character) {
        aux = alpha->last;
        alpha->last->prox = letterNode;
        alpha->last = letterNode;
        letterNode->prev = aux;
        return SUCCESS;
    }

    for (letter_t* i = alpha->first->prox; i != NULL; i = i->prox) {
        if (letterNode->character < i->character) {
            aux = i->prev;
            i->prev = letterNode;
            letterNode->prox = i;
            aux->prox = letterNode;
            letterNode->prev = aux;
            break;
        }
    }

    return SUCCESS;
}

int hasLetter(alpha_t* alpha, char letter) {
    if (findLetter(alpha, letter) == NULL)
        return FAILURE;
    return SUCCESS;
}

int addCode(alpha_t* alpha, char letter, int num) {
    letter_t* ptr = findLetter(alpha, letter);

    ptr->numCodes++;
    ptr->codes = realloc(ptr->codes, sizeof(int) * ptr->numCodes);
    ptr->codes[ptr->numCodes - 1] = num;

    return SUCCESS;
}

int printAlpha(alpha_t* alpha) {
    for (letter_t* i = alpha->first; i != NULL; i = i->prox) {
        printf("%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++) {
            printf("%d ", i->codes[j]);
        }
        printf("\n");
    }

    return 1;
}