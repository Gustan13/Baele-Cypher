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