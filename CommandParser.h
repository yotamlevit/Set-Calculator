//
// Created by Yotam Levit on 16/05/2024.
//

#ifndef MMN22_USERCOMMANDDTO_H
#define MMN22_USERCOMMANDDTO_H

#include "set.h"
#include "Errors.h"
#include "HashMap.h"

typedef struct UserCommand
{
    char* command;
    SetPtr * sets;
    int setsCount;
    char** arguments;
    int argCount;

} UserCommand, * UserCommandPtr;


int parseUserCommand(UserCommandPtr commandDTO, char* command, HashMapPtr setMap);


void freeUserCommand(UserCommandPtr cmd);

#endif //MMN22_USERCOMMANDDTO_H
