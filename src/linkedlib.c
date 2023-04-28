#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "linkedlib.h"

#define SUCCESS 0
#define FAILURE 1

//  RETORNA UMA ESTRUTURA ALPHA_T ALOCADA
list_t* createList(void) {
    list_t *list = malloc(sizeof(list_t));
    
    list->first = NULL;
    list->last = NULL;
    list->numNodes = 0;

    return list;
}

//  RECEBE UM PONTEIRO DE ALPHABETO
//  RETORNA UM PONTEIRO DE ALPHABETO COMPLETAMENTE VAZIO
list_t* destroyList(list_t* head) {
    if (head == NULL)
        return NULL;

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
    letterNode->codes = malloc(sizeof(int));
    letterNode->prev = NULL;
    letterNode->prox = NULL;

    return letterNode;
}

// RECEBE UMA LISTA E UM CHAR
// ENCONTRA O NODO QUE PERTENCE O CHAR
letter_t* findLetter(list_t* list, char letter) {
    for (letter_t* i = list->first; i != NULL; i = i->prox) {
        if (i->character == letter)
            return i;
    }
    return NULL;
}

// RECEBE LISTA DE INT, TAMANHO DA LISTA E O NÚMERO A SER ENCONTRADO
// RETORNA 1 CASO ENCONTRADO O NÚMERO E 0 CASO CONTRÁRIO
int binarySearch(int* codes, int numCodes, int num) {
    int a = 0;
    int b = numCodes - 1;
    int m;

    while (a <= b) {
        m = (a + b) / 2;

        if (codes[m] == num)
            return 1;
        else if (codes[m] > num)
            b = m - 1;
        else
            a = m + 1;
    }
    
    return 0;
}

// RECEBE UMA LISTA E UM INT
// ENCONTRA O CHAR DO NODO QUE POSSUI O INT COMO CÓDIGO
char findLetterFromNum(list_t* list, int num) {
    for (letter_t* i = list->first; i != NULL; i = i->prox) {
        if (binarySearch(i->codes, i->numCodes, num))
            return i->character;
        // for (int j = 0; j < i->numCodes; j++) {
        //     if (i->codes[j] == num)
        //         return i->character;
        // }
    }
    return 32;
}

// RECEBE LISTA E UM NODO LETTER_T
// INSERE O NODO DE FORMA ORDENADA NA LISTA LINKADA
// RETORNA SUCCESS SE O PROCEDIMENTO OCORREU CORRETAMENTE E FAILURE CASO CONTRÁRIO
int insertLetter(list_t* list, letter_t* letterNode) {
    letter_t* aux;

    if (findLetter(list, letterNode->character) != NULL)
        return FAILURE;

    if (list->first == NULL) {
        list->first = letterNode;
        list->last = letterNode;
        return SUCCESS;
    }

    if (letterNode->character < list->first->character) {
        aux = list->first;
        list->first = letterNode;
        letterNode->prox = aux;
        aux->prev = letterNode;
        return SUCCESS;
    }

    if (letterNode->character > list->last->character) {
        aux = list->last;
        list->last->prox = letterNode;
        list->last = letterNode;
        letterNode->prev = aux;
        return SUCCESS;
    }

    for (letter_t* i = list->first->prox; i != NULL; i = i->prox) {
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

// RECEBE LISTA E UM CHAR
// RETORNA SUCCESS SE EXISTE UM NODO COM A LETRA CHAR NA LISTA E FAILURE CASO CONTRÁRIO
int hasLetter(list_t* list, char letter) {
    if (findLetter(list, letter) == NULL)
        return FAILURE;
    return SUCCESS;
}

// RECEBE UMA LISTA, UM CHAR E UM INT
// ADICIONA O CÓDIGO (INT) PARA O NODO CONTENDO O CHAR
// RETORNA SUCCESS SE FUNÇÃO FEITA CORRETAMENTE E FAILURE CASO CONTRÁRIO
int addCode(list_t* list, char letter, int num) {
    letter_t* ptr = findLetter(list, letter);

    ptr->numCodes++;
    ptr->codes = realloc(ptr->codes, sizeof(int) * ptr->numCodes);
    ptr->codes[ptr->numCodes - 1] = num;

    return SUCCESS;
}

// RECEBE LISTA
// IMPRIME A LISTA PARA O STDOUT
int printlist(list_t* list) {
    for (letter_t* i = list->first; i != NULL; i = i->prox) {
        printf("%c : ", i->character);
        for (int j = 0; j < i->numCodes; j++) {
            printf("%d ", i->codes[j]);
        }
        printf("\n");
    }

    return 1;
}