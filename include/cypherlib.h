#ifndef __cypherlib__
#define __cypherlib__

#include "linkedlib.h"

long findSizeOfFile(FILE* file);

int createCypherFromBook(FILE* book, list_t* list);
int createCypherFromKeyFile(FILE* keys, list_t* list);

int printCypherToFile(FILE* toWrite, list_t* list);

#endif