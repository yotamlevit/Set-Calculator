/*
  Created by Yotam Levit on 25/04/2024.
*/

#include <stdio.h>
#include <strings.h>

#include "set.h"
#include "Errors.h"
#include "CommandFactory.h"

#define WELCOME_MSG "Hi, Welcome to MMN22 by Yotam Levit\n---------------------------------\n\n"
#define EXIT_MSG "\nThank you for using MMN22\nBye...\n"
#define MAXLEN 1200 /* Define maximum length for commands and inputs */
#define EXIT_COMMAND "stop"

#define REMOVE_NEW_LINE(str) *strchr(str, '\n') = '\0'

typedef enum {
    SETA,
    SETB,
    SETC,
    SETD,
    SETE,
    SETF,
    NumberOfSets
} Sets;

void initAllSets(SetPtr sets)
{
    int i;

    for (i = 0; i < NumberOfSets; ++i) {
        initSet(sets+i);
    }
}


void func(){
    printf("asdasd");
}



int main() {
    //Set SETA, SETB, SETC, SETD, SETE, SETF;

    Set allSets[NumberOfSets];

    initAllSets(allSets);

    char command[MAXLEN];
    FunctionPointer commandFunction;
    int r;


    /* Define a 2Dim array of commands name */
    char commands[][MAXLEN] = {
            "read_set",
            "print_set",
            "union_set",
            "intersect_set"
            "sub_set",
            "symdiff_set",
            "stop"
    };

    /* Print a welcome message */
    printf(WELCOME_MSG);

    int arr[128] = {1,2, 3, 4,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 126, -1}; //{1,2,3,4,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 126, -1};
    int arr2[128] = {1,2,3, 110,125, -1};
    readSet(&allSets[SETA], arr);
    readSet(&allSets[SETB], arr2);


    do {
        printf("Enter Command: ");
        fgets(command, MAXLEN, stdin);
        REMOVE_NEW_LINE(command);

        commandFunction = getCommand(command);

        printf("\n%s\n", (char * )commandFunction(&allSets[SETA]));

        // Parse Command
    }while(strcmp(command, EXIT_COMMAND));


    printf(EXIT_MSG);






    printf("%s\n\n", getError(undefinedCommandNameError)->error_msg);


    /*
    printf("\n%s\n", printSet(&allSets[SETA]));
    printf("\n%s\n", printSet(&allSets[SETB]));

    unionSet(&allSets[SETA], &allSets[SETB], &allSets[SETC]);
    printf("\n%s\n", printSet(&allSets[SETC]));

    intersectSet(&allSets[SETA], &allSets[SETB], &allSets[SETC]);
    printf("\n%s\n", printSet(&allSets[SETC]));

    subSet(&allSets[SETA], &allSets[SETB], &allSets[SETC]);
    printf("\n%s\n", printSet(&allSets[SETC]));

    symDiffSet(&allSets[SETA], &allSets[SETB], &allSets[SETC]);
    printf("\n%s\n", printSet(&allSets[SETC]));*/

    return 0;
}