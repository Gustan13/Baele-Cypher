#include "alphalib.h"

int createCypher(FILE* file, alpha_t* alpha);
int printCypher(FILE* toWrite, alpha_t* alpha);

int cypherMessage(FILE* message, FILE* returnFile, alpha_t* alpha);
int decypherMessage_b(FILE* message, FILE* returnFile,  alpha_t* alpha);