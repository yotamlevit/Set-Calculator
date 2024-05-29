//
// Created by Yotam Levit on 14/05/2024.
//

#ifndef MMN22_COMMANDDISPACHER_H
#define MMN22_COMMANDDISPACHER_H


#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "CommandParser.h"
#include "HashMap.h"

//typedef int (*FunctionPointer)(void*); //void* functionParams
typedef int (*ThreeSetFunctionsPointer)(SetPtr set1, SetPtr set2, SetPtr set3); //void* functionParams
typedef int (*StrOutputSetFunctionPointer)(SetPtr set1, char** output); //void* functionParams
typedef int (*SetAndNumbersFunctionPointer)(SetPtr set1, int* numbers); //void* functionParams


/*
typedef struct {
    SetPtr set1;
    SetPtr set2;
    SetPtr set3;
} threeSetFunctionsParam;

typedef struct {
    SetPtr set1;
    char** output;
} strOutputSetFunctionsParam;

typedef struct {
    SetPtr set1;
    int* numbers;
} setAndNumbersFunctionParam;
*/


typedef union {
    ThreeSetFunctionsPointer threeSetFunctions;
    StrOutputSetFunctionPointer strOutputSetFunction;
    SetAndNumbersFunctionPointer setAndNumbersFunction;
} FunctionPointer;

typedef int (*Dispatcher)(FunctionPointer, UserCommandPtr);


typedef struct {
    FunctionPointer commandFunction;  // Function pointer,
    Dispatcher functionDispatcher; // Dispatcher function that is used as decorator
} CommandMapValue, * CommandMapValuePtr;

/*
typedef struct {
    const char* command;  // String ID for the function
    FunctionPointer commandFunction;  // Function pointer,
    DecoratorPointer functionDecorator; // A wrapper function that is used as decorator
} CommandMap, * CommandMapPtr;


typedef struct {
    CommandMapPtr commandMap;  // Pointer to a map of command and the related function
    int numberOfCommands;  // The number of available commands
} CommandRegistry, * CommandRegistryPtr;
*/


HashMapPtr initCommandMap();
int runCommand(HashMapPtr commandMap, UserCommandPtr command);



#endif //MMN22_COMMANDDISPACHER_H
