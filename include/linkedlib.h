#ifndef __linkedlib__
#define __linkedlib__

#define MAX_CODES 100

typedef struct letter {
    char character;
    int *codes;
    int numCodes;

    struct letter *prox;
    struct letter *prev;
} letter_t;

typedef struct lista {
    letter_t *first;
    letter_t *last;
    int numNodes;
} list_t;

list_t* createList(void);

list_t* destroyList(list_t* head);

letter_t* createLetter(char letter);

letter_t* findLetter(list_t* list, char letter);

char findLetterFromNum(list_t* list, int num);

int insertLetter(list_t* list, letter_t* letterNode);

int hasLetter(list_t* list, char letter);

int addCode(list_t* list, char letter, int num);

int printList(list_t* list);

int binarySearch(int* codes, int numCodes, int num);

#endif