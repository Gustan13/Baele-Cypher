#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "alphalib.h"

alpha_t* createAlpha(void) {
    alpha_t *alpha = malloc(sizeof(alpha_t));
    
    alpha->first = NULL;
    alpha->last = NULL;
    alpha->numNodes = 0;

    return alpha;
}

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