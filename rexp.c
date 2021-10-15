#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "tdp.h"

#define FAILED NULL

bool keepgoing = true;
int mode = 1;

void userInterface() {
    char input[255];

    while(keepgoing == true) {

        if(mode == 1) {
            printf("\n----------------------------------------------------------------------------------------\n");
            printf("Recursive Decent Parsing\n");
            printf("Enter a regular expression, enter next for the Table Driven Parser, or quit to exit\n");
            scanf("%s", input);
            if (!strcmp(input, "quit")) {
                keepgoing = false;
            }
            else if(!strcmp(input, "next")) {
                mode = 2;
            }
            else {
                inputString i = newInputString(input);
                i -> root = E(i);
                prettyPrint(0, i -> root);
                free(i);

            }
        }
        if(mode == 2) {
            printf("\n----------------------------------------------------------------------------------------\n");
            printf("Table Driven Parsing\n");
            printf("Enter a regular expression or quit to exit\n");
            scanf("%s", input);
            if (!strcmp(input, "quit")) {
                keepgoing = false;
            }
            else {
                cinputString s = cnewInputString(input);
                evaluateString(s);
                cprettyPrint(0, s->root);
                free(s);
            }
        }
    }
}

int main() {
    userInterface();
    //char* input = "a|b.c*";
//
//    inputString i = newInputString(input);
//    cinputString s = cnewInputString(input);
//
//    Tree rooti = E(i);
//    evaluateString(s);
//
//    prettyPrint(0, rooti);
//    printf("\n\n");
//   cprettyPrint(0, s -> root);
}
