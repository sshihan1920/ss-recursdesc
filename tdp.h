#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef CSC173PROJECT02_TDP_H
#define CSC173PROJECT02_TDP_H
#endif //CSC173PROJECT02_TDP_H


typedef struct cinputString* cinputString;
typedef struct cTree* cTree;

struct Table {
    int** table;
};

struct cinputString {
    char* input;
    int index;
    cTree root;
};

struct cTree {
    char* label;
    cTree leftmostChild, rightSibling;
    bool isTerm;
};

extern cTree evaluateString(cinputString s);
extern bool isTerminal(char c);
extern char clook_ahead(cinputString s);
extern cinputString cnewInputString(char* s);
extern void cincrementIndex(cinputString s);
extern void matchTerminal(cinputString s, char c);
extern void cprettyPrint(int indents, cTree t);
