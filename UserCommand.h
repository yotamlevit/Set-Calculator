//
// Created by Yotam Levit on 16/05/2024.
//

#ifndef MMN22_USERCOMMANDDTO_H
#define MMN22_USERCOMMANDDTO_H

#include "strings.h"

#include "set.h"

typedef struct UserCommand
{
    char* command;
    SetPtr * sets;
    int setsCount;
    char* args;
    int argCount;

} UserCommand, * UserCommandPtr;


void parseUserCommand(UserCommandPtr commandDTO, char* command)
{

}

#endif //MMN22_USERCOMMANDDTO_H
