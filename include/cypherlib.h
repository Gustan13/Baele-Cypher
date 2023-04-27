#include "alphalib.h"

long findSizeOfFile(FILE* file);

int createCypherFromBook(FILE* book, alpha_t* alpha);
int createCypherFromKeyFile(FILE* keys, alpha_t* alpha);

int printCypherToFile(FILE* toWrite, alpha_t* alpha);

int cypherMessage(FILE* message, FILE* returnFile, alpha_t* alpha);
int decypherMessage(FILE* message, FILE* returnFile,  alpha_t* alpha);