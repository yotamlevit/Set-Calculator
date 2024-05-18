//
// Created by Yotam Levit on 16/05/2024.
//

#include <strings.h>
#include <stdlib.h>

#include "CommandParser.h"


int parseUserCommand(UserCommandPtr commandDTO, char* command)
{
    char* token;

    if(command == NULL || strlen(command) == 0)
        //printError(missingCommand);
        return missingCommand;

    token = strtok(command, " ");
    commandDTO->command = strdup(token);

    //commandDTO->arguments = malloc(space * sizeof(char*));
    commandDTO->argCount = 0;

    while ((token = strtok(NULL, ", ")) != NULL)
    {
        commandDTO->arguments = realloc(commandDTO->arguments, ++commandDTO->argCount * sizeof(char*));

        if (!commandDTO->arguments)
            return troubleParsingCommandArguments;

        commandDTO->arguments[commandDTO->argCount] = strdup(token);
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