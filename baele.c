#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "alphalib.h"

#define ASCII_TABLE 

int main (int argc, char *argv[])
{
    alpha_t* alpha = createAlpha();

    for (int i = 32; i < 127; i++) {
        letter_t* letter = createLetter(i);
        insertLetter(alpha, letter);
        puts(&findLetter(alpha, i)->character);
    }    

    addCode(alpha, 65, 13);

    printf("%d", findLetter(alpha, 65)->codes[0]);

    return 0;
}