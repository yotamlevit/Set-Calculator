/*
  Created by Yotam Levit on 25/04/2024.
*/

#include <stdio.h>
#include <strings.h>

#include "set.h"
#include "Errors.h"
#include "CommandDispatcher.h"
#include "CommandParser.h"
#include "HashMap.h"
#include "SetMap.h"

#define WELCOME_MSG "Hi, Welcome to MMN22 by Yotam Levit\n---------------------------------\n\n"
#define EXIT_MSG "\nThank you for using MMN22\nBye...\n"
#define MAXLEN 1200 /* Define maximum length for commands and inputs */
#define EXIT_COMMAND "stop"

#define REMOVE_NEW_LINE(str) *strchr(str, '\n') = '\0'


void getUserCommand(char* buffer){
    printf("Enter Command: ");
    fgets(buffer, MAXLEN, stdin);
    REMOVE_NEW_LINE(buffer);
}


int checkPreProcessing(HashMapPtr commandMap, HashMapPtr setMap)
{
    if(!commandMap)
        return troubleInitSet;

    if(!setMap)
        return troubleInitSet;

    return TRUE;
}


void freeProgramStructures(UserCommandPtr userCommand, HashMapPtr commandMap, HashMapPtr setMap)
{
    freeUserCommand(userCommand);
    hashMapFree(commandMap);
    hashMapFree(setMap);
}

int main() {
    UserCommand userCommand;
    char command[MAXLEN];
    HashMapPtr commandMap = initCommandMap();
    HashMapPtr setMap = initSetMap();
    int processingResult = checkPreProcessing(commandMap, setMap);


    initUserCommand(&userCommand);


    if(processingResult != TRUE)
    {
        printError(processingResult);
        return 0;
    }

    /* Print a welcome message */
    printf(WELCOME_MSG);

    getUserCommand(command);

    while(strcmp(command, EXIT_COMMAND) != 0) {

        processingResult = parseUserCommand(&userCommand, command, setMap);

        if (processingResult == TRUE) {
            processingResult = runCommand(commandMap, &userCommand);
        }

        if (processingResult != TRUE)
            printError(processingResult);

        getUserCommand(command);
    }

    printf(EXIT_MSG);

    freeProgramStructures(&userCommand, commandMap, setMap);

    return 1;
}