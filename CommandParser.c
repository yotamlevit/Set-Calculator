//
// Created by Yotam Levit on 16/05/2024.
//

#include <strings.h>
#include <stdlib.h>

#include "CommandParser.h"

#define IS_ARGUMENT_SET(argument) strstr(argument, "SET") != NULL


void initUserCommand(UserCommandPtr commandDTO)
{
    commandDTO->arguments = NULL;
    commandDTO->argCount = 0;
    commandDTO->command = NULL;
    commandDTO->setsCount = 0;
}

void resetUserCommand(UserCommandPtr commandDTO)
{
    free(commandDTO->command);
    commandDTO->setsCount = 0;

    for (int i = 0; i < commandDTO->argCount; ++i) {
        free(commandDTO->arguments[i]);
    }
    commandDTO->argCount = 0;
}

int parseUserCommand(UserCommandPtr commandDTO, char* command, HashMapPtr setMap)
{
    char* token;
    SetPtr set;

    if(command == NULL || strlen(command) == 0)
        return missingCommand;

    resetUserCommand(commandDTO);

    token = strtok(command, " ");
    commandDTO->command = strdup(token);

    while ((token = strtok(NULL, ", ")) != NULL)
    {
        if (IS_ARGUMENT_SET(token))
        {
            set = hashMapFind(setMap, token);
            if(set)
                commandDTO->sets[commandDTO->setsCount++] = set;
            else
                return undefinedSetNameError;
        }
        else
        {
            commandDTO->arguments = realloc(commandDTO->arguments, ++commandDTO->argCount * sizeof(char*));

            if (!commandDTO->arguments)
                return troubleParsingCommandArguments;

            commandDTO->arguments[commandDTO->argCount-1] = strdup(token);
        }
    }

    return TRUE;
}


void freeUserCommand(UserCommandPtr cmd) {
    if (cmd) {
        free(cmd->command);
        for (int i = 0; i < cmd->argCount; i++) {
            free(cmd->arguments[i]);
        }
        free(cmd->arguments);
        free(cmd);
    }
}