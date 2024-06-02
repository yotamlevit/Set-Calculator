/*
* Created by Yotam Levit on 16/05/2024.
*/

#ifndef MMN22_COMMANDDISPATCHER_H
#define MMN22_COMMANDDISPATCHER_H


#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "CommandParser.h"
#include "HashMap.h"

typedef int (*ThreeSetFunctionsPointer)(SetPtr set1, SetPtr set2, SetPtr set3);
typedef int (*StrOutputSetFunctionPointer)(SetPtr set1, char** output);
typedef int (*SetAndNumbersFunctionPointer)(SetPtr set1, int* numbers);


typedef union {
    ThreeSetFunctionsPointer threeSetFunctions;
    StrOutputSetFunctionPointer strOutputSetFunction;
    SetAndNumbersFunctionPointer setAndNumbersFunction;
} FunctionPointer;

typedef int (*Dispatcher)(FunctionPointer, UserCommandPtr);


typedef struct {
    FunctionPointer commandFunction;  /* Function pointer */
    Dispatcher functionDispatcher; /* Dispatcher function that is used as decorator */
} CommandMapValue, * CommandMapValuePtr;


HashMapPtr initCommandMap();
int runCommand(HashMapPtr commandMap, UserCommandPtr command);



#endif /* MMN22_COMMANDDISPATCHER_H */