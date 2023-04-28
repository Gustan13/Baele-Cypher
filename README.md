# Beale-Cypher Introduction

A program that cyphers and decyphers messages according to the Beale Cypher method. This program was written in:

[![My Skills](https://skillicons.dev/icons?i=c)](https://skillicons.dev)

To compile the program, open the terminal in the same folder as the source code and run `make`. You can also run `make test` to test the functionality of all three possible commands in the program.

The files must have the .txt extention in order for the program to properly function. Also, the files must be in the same directory as the program.

usage:

> ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves
>
> ./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada
>
> ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada

*Made by Gustavo Isoo Binder*

# Libraries

All libraries created for this project.

## conceal.h

Contains a function to Cypher messages.

```
int cypherMessage(FILE *message, FILE *returnFile, list_t *list);
```


## deconceal.h

Contains a function to Decypher messages.

```
int decypherMessage(FILE* message, FILE* returnFile,  list_t* list);
```


## cypherlib.h

This library allows the program to properly manage the cyphering files.

```
long findSizeOfFile(FILE* file);
int createCypherFromBook(FILE* book, list_t* list);
int createCypherFromKeyFile(FILE* keys, list_t* list);
int printCypherToFile(FILE* toWrite, list_t* list);
```

## linkedlib.h

This library contains functions and structs to apply linked list data structures.

```
list_t* createList(void);
list_t* destroyList(list_t* head);

letter_t* createLetter(char letter);
letter_t* findLetter(list_t* list, char letter);

char findLetterFromNum(list_t* list, int num);

int insertLetter(list_t* list, letter_t* letterNode);
int hasLetter(list_t* list, char letter);
int addCode(list_t* list, char letter, int num);
int printList(list_t* list);
```
