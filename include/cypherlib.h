#include "linkedlib.h"

long findSizeOfFile(FILE* file);

int createCypherFromBook(FILE* book, list_t* list);
int createCypherFromKeyFile(FILE* keys, list_t* list);

int printCypherToFile(FILE* toWrite, list_t* list);

int cypherMessage(FILE* message, FILE* returnFile, list_t* list);
int decypherMessage(FILE* message, FILE* returnFile,  list_t* list);