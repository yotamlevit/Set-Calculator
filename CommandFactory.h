//
// Created by Yotam Levit on 14/05/2024.
//

#ifndef MMN22_COMMANDFACTORY_H
#define MMN22_COMMANDFACTORY_H


#include <stdio.h>
#include <string.h>

typedef void* (*FunctionPointer)();

typedef struct {
    const char* command;  // String ID for the function
    FunctionPointer commandFunction;  // Function pointer
} CommandMap, * CommandMapPtr;


typedef struct {
    CommandMapPtr commandMap;  // Pointer to a map of command and the related function
    int numberOfCommands;  // The number of available commands
} CommandRegistry, * CommandRegistryPtr;



CommandRegistryPtr getCommandRegistry();
FunctionPointer getCommand(char* inputCommand);



#endif //MMN22_COMMANDFACTORY_H
