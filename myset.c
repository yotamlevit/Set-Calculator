/*
  Created by Yotam Levit on 25/04/2024.
*/

#include "stdio.h"

#include "set.h"
#include "Errors.h"

#define MAXLEN 1200 /* Define maximum length for commands and inputs */

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



int main() {
    //Set SETA, SETB, SETC, SETD, SETE, SETF;

    Set allSets[NumberOfSets];

    initAllSets(allSets);

    char command[MAXLEN];

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
    printf("Hi, Welcome to MMN22 by Yotam Levit\n---------------------------------\n\nEnter Command:\n");
/*
    while (fgets(command, MAXLEN, stdin))
    {

    }*/

    printf("%s\n\n", getError(undefinedCommandNameError)->error_msg);
    int arr[128] = {1,4,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 126, -1}; //{1,2,3,4,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 126, -1};
    int arr2[128] = {1,2,3, 13, 14, 15, 16, 17, 125, -1};
    readSet(&allSets[SETA], arr);
    readSet(&allSets[SETB], arr2);
    printf("\n%s\n", toString(&allSets[SETA]));
    printf("\n%s\n", toString(&allSets[SETB]));

    unionSet(&allSets[SETA], &allSets[SETB], &allSets[SETC]);
    printf("\n%s\n", toString(&allSets[SETC]));

    intersectSet(&allSets[SETA], &allSets[SETB], &allSets[SETC]);
    printf("\n%s\n", toString(&allSets[SETC]));
    return 0;
}