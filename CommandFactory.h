//
// Created by Yotam Levit on 14/05/2024.
//

#ifndef MMN22_COMMANDFACTORY_H
#define MMN22_COMMANDFACTORY_H


#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "CommandParser.h"
#include "HashMap.h"

typedef int (*FunctionPointer)(SetPtr setA, ...); //void* functionParams
typedef int (*DecoratorPointer)(FunctionPointer, UserCommandPtr);


typedef struct {
    FunctionPointer commandFunction;  // Function pointer,
    DecoratorPointer functionDecorator; // A wrapper function that is used as decorator
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



#endif //MMN22_COMMANDFACTORY_H
