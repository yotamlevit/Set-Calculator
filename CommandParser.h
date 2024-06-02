/*
* Created by Yotam Levit on 16/05/2024.
*/

#ifndef MMN22_USERCOMMANDDTO_H
#define MMN22_USERCOMMANDDTO_H

#include "set.h"
#include "Errors.h"
#include "HashMap.h"

#define MAX_COMMAND_SETS

typedef struct UserCommand
{
    char* command;
    int* arguments;
    int argCount;
    int setsCount;
    SetPtr sets[MAX_COMMAND_SETS];
} UserCommand, * UserCommandPtr;


UserCommandPtr initUserCommand();
int parseUserCommand(UserCommandPtr commandDTO, char** command, HashMapPtr setMap);
void resetUserCommand(UserCommandPtr commandDTO);

void freeUserCommand(UserCommandPtr cmd);

#endif /* MMN22_USERCOMMANDDTO_H */
