//
// Created by Yotam Levit on 16/05/2024.
//

#include <strings.h>
#include <stdlib.h>

#include "CommandParser.h"

#define IS_ARGUMENT_SET(argument) strstr(argument, "SET") != NULL


int parseUserCommand(UserCommandPtr commandDTO, char* command, HashMapPtr setMap)
{
    char* token;

    if(command == NULL || strlen(command) == 0)
        return missingCommand;

    token = strtok(command, " ");
    commandDTO->command = strdup(token);

    commandDTO->setsCount = 0;
    commandDTO->sets = NULL;
    commandDTO->argCount = 0;
    commandDTO->arguments = NULL;

    while ((token = strtok(NULL, ", ")) != NULL)
    {
        if (IS_ARGUMENT_SET(token))
        {
            commandDTO->sets = realloc(commandDTO->sets, ++commandDTO->setsCount * sizeof(char*));

            if (!commandDTO->sets)
                return troubleParsingCommandArguments;

            commandDTO->sets[commandDTO->setsCount-1] = strdup(token);
        }
        commandDTO->arguments = realloc(commandDTO->arguments, ++commandDTO->argCount * sizeof(char*));

        if (!commandDTO->arguments)
            return troubleParsingCommandArguments;

        commandDTO->arguments[commandDTO->argCount-1] = strdup(token);
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