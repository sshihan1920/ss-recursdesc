#include "tdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

LinkedList stack;

cTree makeTree0(char* x, bool term) {
    cTree root;
    root = (cTree) malloc(sizeof(struct cTree));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    root->isTerm = term;
    return root;
}


cTree getLeftMostNonTerm(cTree node) {
    if(node->leftmostChild != NULL){
        cTree n1 = getLeftMostNonTerm(node -> leftmostChild);
        if(n1 != NULL) return n1;
    } else if(*(node->label) != 'e' && node -> isTerm == false){
        return node;
    }
    if(node->rightSibling != NULL){
        cTree n2 = getLeftMostNonTerm(node->rightSibling);
        if(n2!=NULL) return n2;
    }
    return NULL;
}

/* Grammar

⟨E⟩ → ⟨C⟩ ⟨ET⟩
⟨ET⟩ → | ⟨E⟩ | ϵ
⟨C⟩ → ⟨S⟩ ⟨CT⟩
⟨CT⟩ → . ⟨C⟩ | ϵ
⟨S⟩ → ⟨A⟩ ⟨ST⟩
⟨ST⟩ → * ⟨ST⟩ | ϵ
⟨A⟩ → (⟨E⟩) | ⟨X⟩
⟨X⟩ → a | b | · · · | z

 */
int refTable[8][32] = {
//terminals:    |  .  *  (  )  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z eps
 //             0  1  2  3  4  5  6  7  8  9 10 11  12 13 14...
        /*E*/ { 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        /*ET*/{ 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        /*C*/ { 0, 0, 0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
        /*CT*/{ 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        /*S*/ { 0, 0, 0, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
        /*ST*/{ 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        /*A*/ { 0, 0, 0,10, 0,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, 0},
        /*X*/ { 0, 0, 0, 0, 0,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37, 0},
};
int synRow(char* sym) {
    if (strcmp(sym, "E") == 0) { //E
        return 0;
    }
    else if (strcmp(sym, "ET") == 0) { //ET
        return 1;
    }
    else if (strcmp(sym, "C") == 0) { //C
        return 2;
    }
    else if (strcmp(sym, "CT") == 0) { //CT
        return 3;
    }
    else if (strcmp(sym, "S") == 0) { //S
        return 4;
    }
    else if (strcmp(sym, "ST") == 0) { //ST
        return 5;
    }
    else if (strcmp(sym, "A") == 0) { //A
        return 6;
    }
    else if (strcmp(sym, "X") == 0) { //X
        return 7;
    }
    else {
        return -1;
    }
}

int termColumn(char c) {
    switch (c) {
        case '|':
            return 0;
        case '.':
            return 1;
        case '*':
            return 2;
        case '(':
            return 3;
        case ')':
            return 4;
        case 'a':
            return 5;
        case 'b':
            return 6;
        case 'c':
            return 7;
        case 'd':
            return 8;
        case 'e':
            return 9;
        case 'f':
            return 10;
        case 'g':
            return 11;
        case 'h':
            return 12;
        case 'i':
            return 13;
        case 'j':
            return 14;
        case 'k':
            return 15;
        case 'l':
            return 16;
        case 'm':
            return 17;
        case 'n':
            return 18;
        case 'o':
            return 19;
        case 'p':
            return 20;
        case 'q':
            return 21;
        case 'r':
            return 22;
        case 's':
            return 23;
        case 't':
            return 24;
        case 'u':
            return 25;
        case 'v':
            return 26;
        case 'w':
            return 27;
        case 'x':
            return 28;
        case 'y':
            return 29;
        case 'z':
            return 30;
        case '\0':
            return 31;
        default:
            return -1;
    }
}
char elook_ahead(cinputString s) {
    return s ->input[s -> index];
}
void eincrementIndex(cinputString s) {
    s -> index++;
}
cinputString cnewInputString(char* s) {
    cinputString string;
    string = (cinputString)malloc(sizeof(struct cinputString));
    string -> input = s;
    string -> index  = 0;
    string -> root = makeTree0("E", false);
    return string;
}

bool isTerminal(char c) {
    switch (c) {
        case 'a':
            return true;
        case 'b':
            return true;
        case 'c':
            return true;
        case 'd':
            return true;
        case 'e':
            return true;
        case 'f':
            return true;
        case 'g':
            return true;
        case 'h':
            return true;
        case 'i':
            return true;
        case 'j':
            return true;
        case 'k':
            return true;
        case 'l':
            return true;
        case 'm':
            return true;
        case 'n':
            return true;
        case 'o':
            return true;
        case 'p':
            return true;
        case 'q':
            return true;
        case 'r':
            return true;
        case 's':
            return true;
        case 't':
            return true;
        case 'u':
            return true;
        case 'v':
            return true;
        case 'w':
            return true;
        case 'x':
            return true;
        case 'y':
            return true;
        case 'z':
            return true;
        case '|':
            return true;
        case '.':
            return true;
        case '*':
            return true;
        case '(':
            return true;
        case ')':
            return true;
        default:
            return false;
    }
}
void matchTerminal(cinputString s, char c){
    if(elook_ahead(s) == c){
        eincrementIndex(s);
        return;
    } else {
        return;
    }
}
int returnProduction(cinputString i, char* s) {
    int row = synRow(s);
    int column = termColumn(elook_ahead(i));

    if(row != -1 && column != -1) {
        return refTable[row][column];
    }
    else {
        return -1;
    }

}
void selectProduction(cinputString i, char* s) {
    int production = returnProduction(i, s);
    if(production == -1) {
        return;
    }
    cTree currNode = getLeftMostNonTerm(i -> root);
    switch (production) {
        case 0:
            currNode -> leftmostChild  = makeTree0("_", true);
            return;
        case 1:
            LinkedList_add_at_front(stack, "ET");
            LinkedList_add_at_front(stack, "C");

            currNode -> leftmostChild  = makeTree0("C", false);
            currNode -> leftmostChild -> rightSibling = makeTree0("ET", false);

            return;
        case 2:
            LinkedList_add_at_front(stack, "E");
            LinkedList_add_at_front(stack, "|");

            currNode -> leftmostChild  = makeTree0("|", true);
            currNode -> leftmostChild -> rightSibling = makeTree0("E", false);

            return;
        case 3:
            LinkedList_add_at_front(stack, "_");

            currNode -> leftmostChild  = makeTree0("_", true);

            return;
        case 4:
            LinkedList_add_at_front(stack, "CT");
            LinkedList_add_at_front(stack, "S");

            currNode -> leftmostChild  = makeTree0("S", false);
            currNode -> leftmostChild -> rightSibling = makeTree0("CT", false);

             return;
        case 5:
            LinkedList_add_at_front(stack, "C");
            LinkedList_add_at_front(stack, ".");

            currNode -> leftmostChild  = makeTree0(".", true);
            currNode -> leftmostChild -> rightSibling = makeTree0("C", false);

            return;
        case 6:
            LinkedList_add_at_front(stack, "_");

            currNode -> leftmostChild  = makeTree0("_", true);

             return;
        case 7:
            LinkedList_add_at_front(stack, "ST");
            LinkedList_add_at_front(stack, "A");

            currNode -> leftmostChild  = makeTree0("A", false);
            currNode -> leftmostChild -> rightSibling = makeTree0("ST", false);

            return;
        case 8:
            LinkedList_add_at_front(stack, "ST");
            LinkedList_add_at_front(stack, "*");

            currNode -> leftmostChild  = makeTree0("*", true);
            currNode -> leftmostChild -> rightSibling = makeTree0("ST", false);

            return;
        case 9:
            LinkedList_add_at_front(stack, "_");

            currNode -> leftmostChild  = makeTree0("_", true);

            return;
        case 10:
            printf("touched by input %c and production %s \n ", elook_ahead(i), s);
            LinkedList_add_at_front(stack, ")");
            LinkedList_add_at_front(stack, "E");
            LinkedList_add_at_front(stack, "(");

            currNode -> leftmostChild  = makeTree0("(", true);
            currNode -> leftmostChild -> rightSibling = makeTree0("E", false);
            currNode -> leftmostChild -> rightSibling -> rightSibling = makeTree0(")", true);

            return;
        case 11:
            LinkedList_add_at_front(stack, "X");

            currNode -> leftmostChild  = makeTree0("X", false);

            return;
        case 12:
            LinkedList_add_at_front(stack, "a");

            currNode -> leftmostChild  = makeTree0("a", true);

            return;
        case 13:
            LinkedList_add_at_front(stack, "b");

            currNode -> leftmostChild  = makeTree0("b", true);

            return;
        case 14:
            LinkedList_add_at_front(stack, "c");

            currNode -> leftmostChild  = makeTree0("c", true);

            return;
        case 15:
            LinkedList_add_at_front(stack, "d");

            currNode -> leftmostChild  = makeTree0("d", true);

            return;
        case 16:
            LinkedList_add_at_front(stack, "e");

            currNode -> leftmostChild  = makeTree0("e", true);

            return;
        case 17:
            LinkedList_add_at_front(stack, "f");

            currNode -> leftmostChild  = makeTree0("f", true);

            return;
        case 18:
            LinkedList_add_at_front(stack, "g");

            currNode -> leftmostChild  = makeTree0("g", true);

            return;
        case 19:
            LinkedList_add_at_front(stack, "h");

            currNode -> leftmostChild  = makeTree0("h", true);

            return;
        case 20:
            LinkedList_add_at_front(stack, "i");

            currNode -> leftmostChild  = makeTree0("i", true);

            return;
        case 21:
            LinkedList_add_at_front(stack, "j");

            currNode -> leftmostChild  = makeTree0("j", true);

            return;
        case 22:
            LinkedList_add_at_front(stack, "k");

            currNode -> leftmostChild  = makeTree0("k", true);

            return;
        case 23:
            LinkedList_add_at_front(stack, "l");

            currNode -> leftmostChild  = makeTree0("l", true);

            return;
        case 24:
            LinkedList_add_at_front(stack, "m");

            currNode -> leftmostChild  = makeTree0("m", true);

            return;
        case 25:
            LinkedList_add_at_front(stack, "n");

            currNode -> leftmostChild  = makeTree0("n", true);

            return;
        case 26:
            LinkedList_add_at_front(stack, "o");

            currNode -> leftmostChild  = makeTree0("o", true);

            return;
        case 27:
            LinkedList_add_at_front(stack, "p");

            currNode -> leftmostChild  = makeTree0("p", true);

            return;
        case 28:
            LinkedList_add_at_front(stack, "q");

            currNode -> leftmostChild  = makeTree0("q", true);

            return;
        case 29:
            LinkedList_add_at_front(stack, "r");

            currNode -> leftmostChild  = makeTree0("r", true);

            return;
        case 30:
            LinkedList_add_at_front(stack, "s");

            currNode -> leftmostChild  = makeTree0("s", true);

            return;
        case 31:
            LinkedList_add_at_front(stack, "t");

            currNode -> leftmostChild  = makeTree0("t", true);

            return;
        case 32:
            LinkedList_add_at_front(stack, "u");

            currNode -> leftmostChild  = makeTree0("u", true);

            return;
        case 33:
            LinkedList_add_at_front(stack, "v");

            currNode -> leftmostChild  = makeTree0("v", true);

            return;
        case 34:
            LinkedList_add_at_front(stack, "w");

            currNode -> leftmostChild  = makeTree0("w", true);

            return;
        case 35:
            LinkedList_add_at_front(stack, "x");

            currNode -> leftmostChild  = makeTree0("x", true);

            return;
        case 36:
            LinkedList_add_at_front(stack, "y");

            currNode -> leftmostChild  = makeTree0("y", true);

            return;
        case 37:
            LinkedList_add_at_front(stack, "z");

            currNode -> leftmostChild  = makeTree0("z", true);
            return;

        default:
            return;
    }
}
void cprettyPrint(int indents, cTree t) {
    if(t == NULL) {
        return;
    }
    else {
        for (int i = 0; i < indents; i++) {
            printf("    ");
        }
        if(strcmp(t -> label, "_") == 0) {
            printf("%s\n", "eps");
        }
        else {
            printf("%s\n", t ->label);
        }
    }

    cprettyPrint(indents + 1, t->leftmostChild);
    cprettyPrint(indents, t->rightSibling);

}

cTree evaluateString(cinputString s) {
    stack = new_LinkedList();
    LinkedList_add_at_front(stack, "E");
    while(!LinkedList_isEmpty(stack)) {
        char* y = LinkedList_pop(stack);
        if (isTerminal(*y)) {
            matchTerminal(s, *y);
        } else {
            // Y is a non-terminal
            //printf("else comparison containing input %c and popped input %s\n", elook_ahead(s) , y);
            selectProduction(s, y);
           // select production for Y using lookahead
           //
           // push RHS of production onto stack
        }
    }
    return NULL;
}


