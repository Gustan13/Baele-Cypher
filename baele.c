#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "alphalib.h"

int main (int argc, char *argv[])
{
    alpha_t* alpha = createAlpha();
    letter_t* letter = createLetter(65);
    
    letter->character = tolower(letter->character);

    puts(&findLetter(alpha, 'a')->character);

    return 0;
}