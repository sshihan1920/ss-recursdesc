#include "Tree.h"

#ifndef CSC173PROJECT02_TREE_H
#define CSC173PROJECT02_TREE_H

#endif //CSC173PROJECT02_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Tree.h"

char* eSym = "E";
char* etSym = "ET";
char* cSym = "C";
char* ctSym = "CT";
char* sSym = "S";
char* stSym = "ST";
char* aSym = "A";
char* xSym = "X";

//Look Ahead Method
char look_ahead(inputString s) {
    //printf("%d", 0);
    return s ->input[s -> index];
}

//New Input String Method
inputString newInputString(char* s) {
    inputString string;
    string = (inputString)malloc(sizeof(struct inputString));
    string -> input = s;
    string -> index  = 0;
    return string;
}

//Increment Index Method
void incrementIndex(inputString s) {
    s -> index++;
    //s++;
}

//Match Method
bool match(inputString s, char m) {
    //printf("%d", 1);
    if (s -> input[s -> index] == m) {
        //printf("%d", 1);
        incrementIndex(s);
        return true;
    }
    else return false;
}

//Make Leaf Method
Tree makeNode0(char* x){
    Tree root;
    root = (Tree) malloc(sizeof(struct Node));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

//Make Node with One Child Method
Tree makeNode1(char* x, Tree t){
    Tree root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

//Make Node with Two Children Method
Tree makeNode2(char* x, Tree t1, Tree t2) {
    Tree root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}

//Make Node with Two Children Method
Tree makeNode3(char* x, Tree t1, Tree t2, Tree t3) {
    Tree root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

//Make Node with Four Children Method
Tree makeNode4(char* x, Tree t1, Tree t2, Tree t3, Tree t4) {
    Tree root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

//TODO Grammar Methods

//Make Expression Tree Method
Tree E(inputString s) {
	//if (match(s, '(')) printf("( found\n");
	printf("%c", look_ahead(s));
	Tree cTree = C(s);
    Tree etTree = ET(s);
    Tree newTree = makeNode2(eSym, cTree, etTree);
    return newTree;
}

//Make Expression Tail Tree Method
Tree ET(inputString s) {
    if (look_ahead(s) != '|') {
        Tree epsNode = makeNode0("_"); //Epsilon
        Tree newTree = makeNode1(etSym, epsNode);//TODO Change I to ET, Change Param to String
        return newTree;
    }
//<E> -> eps
    else {
        if (!match(s, '|')) return NULL;
        Tree eTree = E(s);
        if (eTree == NULL) return NULL;
        Tree newTree = makeNode2(etSym, makeNode0("|"), eTree);
        return newTree;
    }
//<E> -> |E
}

//Make Concantenation Tree Method
Tree C(inputString s) {
	printf("%c", look_ahead(s));
	Tree sTree = S(s);
    Tree ctTree = CT(s);
    Tree newTree = makeNode2(cSym, sTree, ctTree);
    return newTree;
}

//Make Concatenation Tail Tree Method
Tree CT(inputString s) {
    if (look_ahead(s) != '.') {
        Tree epsNode = makeNode0("_"); //Epsilon
        Tree newTree = makeNode1(ctSym, epsNode);//TODO Change J to CT
        return newTree;
    }
//<C> -> eps
    else {
        if (!match(s, '.')) return NULL;
        Tree cTree = C(s);
        if (cTree == NULL) return NULL;
        Tree newTree = makeNode2(ctSym, makeNode0("."), cTree);
        return newTree;
    }
//<C> -> .C
}

//Make Star Tree Method
Tree S(inputString s) {
	printf("%c", look_ahead(s));
	Tree aTree = A(s);
    Tree stTree = ST(s);
    Tree newTree = makeNode2(sSym, aTree, stTree);
    return newTree;
}

//Make Star Tail Tree Method
Tree ST(inputString s) {
//    printf("%c not * \n", look_ahead(s));
    if (look_ahead(s) != '*') {
        Tree epsNode = makeNode0("_"); //Epsilon
        Tree newTree = makeNode1(stSym, epsNode);//TODO Change K to ST
        return newTree;
    }
//<S> -> eps
    else {
        if (!match(s, '*')) return NULL;
        Tree sTree = ST(s);
        if (sTree == NULL) return NULL;

        Tree newTree = makeNode2(stSym, makeNode0("*"), sTree);
        return newTree;
    }
//<S> -> *ST
}

//Make Atomic Tree Method
Tree A(inputString s) {
	printf("%c", look_ahead(s));
	if (!match(s, '(')) {
        //printf("Not (\n");
    	return makeNode1(aSym, X(s));
    }
//<A> -> X
    else {
    	//if (match(s, '(')) printf("( found");
        if (!match(s, '(')) return NULL;
        Tree xTree = E(s);
        if (xTree == NULL) return NULL;
        if (!match(s, ')')) return NULL;

        //printf("Is (\n");
        Tree newTree = makeNode3(aSym, makeNode0("("), E(s), makeNode0(")"));
        //printf("Index: %d\n", s->index);
        return newTree;
    }
//<A> -> (E)
}

//Make Input Character Tree Method
Tree X(inputString s) {
    if (isalpha(look_ahead(s)) == 0) {
        return NULL;
    }
    else {
        //char c = look_ahead(s);
        char *str = malloc(sizeof(char)*2);
        //char str[2];
        //str[1] = "\n";
        str[0] = look_ahead(s);
        str[1] = '\0';
        Tree leafNode = makeNode0(str);

        Tree newTree = makeNode1(xSym, leafNode);
        incrementIndex(s);

        return newTree;
    }
}

//Formatted Parse Tree Print Method
void prettyPrint(int indents, Tree t) {
    if(t == FAILED) {
        //TODO printf("Error Invalid Expression");
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

    prettyPrint(indents + 1, t->leftmostChild);
    prettyPrint(indents, t->rightSibling);
}
