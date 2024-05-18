//
// Created by Yotam Levit on 14/05/2024.
//

#include "CommandFactory.h"
#include "set.h"
#include "Errors.h"


CommandRegistryPtr getCommandRegistry()
{
    static CommandMap commandMap[] = {
            {"read_set",      readSet},
            {"print_set",     (FunctionPointer) printSet},
            {"union_set",     unionSet},
            {"intersect_set", intersectSet},
            {"sub_set",       subSet},
            {"symdiff_set",   symDiffSet}
    };

    static CommandRegistry commandRegistry = {commandMap, sizeof(commandMap) / sizeof(CommandMap)};

    return &commandRegistry;
}


int getCommand(FunctionPointer commandFunction, char* command)
{
    CommandRegistryPtr commandRegistry = getCommandRegistry();
    CommandMapPtr commandMap = commandRegistry->commandMap;

    for (int i = 0; i < commandRegistry->numberOfCommands; i++) {
        if (strcmp(commandMap[i].command, command) == 0) {  // Compare string IDs
            commandFunction = commandMap[i].commandFunction;
            return TRUE;
        }
    }
    commandFunction = NULL;
    return undefinedCommandNameError;
}

