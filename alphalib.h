#define MAX_CODES 100

typedef struct letter {
    char character;
    int *code;
    int numCodes;

    struct letter *prox;
    struct letter *prev;
} letter_t;

typedef struct alpha {
    letter_t *first;
    letter_t *last;
    int numNodes;
} alpha_t;

alpha_t* createAlpha(void);

letter_t* createLetter(char letter);

letter_t* findLetter(char letter);

int hasLetter(alpha_t* alpha, char letter);

int addCode(alpha_t* alpha, char letter, int num);