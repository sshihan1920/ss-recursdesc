#ifndef Tree_H_
#define Tree_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define FAILED NULL

typedef struct Node *Tree;
typedef struct inputString* inputString;
struct Node {
    //char label;
    char* label;
    Tree leftmostChild, rightSibling;
};
struct inputString {
    char* input;
    int index;
    Tree root;
};

extern Tree parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */
char *curr;

extern char look_ahead(inputString s);
extern bool match(inputString s, char m);
extern inputString newInputString(char* s);
extern void incrementIndex(inputString s);

extern Tree makeNode0(char* x);
extern Tree makeNode1(char* x, Tree t);
extern Tree makeNode2(char* x, Tree t1, Tree t2);
extern Tree makeNode3(char* x, Tree t1, Tree t2, Tree t3);
extern Tree makeNode4(char* x, Tree t1, Tree t2, Tree t3, Tree t4);
extern int isalpha(int c);
extern void prettyPrint(int indents, Tree t);

extern Tree E(inputString s);
extern Tree S(inputString s);
extern Tree C(inputString s);
extern Tree A(inputString s);
extern Tree X(inputString s);
extern Tree ET(inputString s);
extern Tree ST(inputString s);
extern Tree CT(inputString s);

#endif /* Tree_H_ */
