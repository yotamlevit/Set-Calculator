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


/**
 * Prompts the user to enter a command and stores it in the provided buffer.
 *
 * @param buffer The buffer to store the user command.
 */
void getUserCommand(char* buffer){
    printf("Enter Command: ");
    fgets(buffer, MAXLEN, stdin);
    REMOVE_NEW_LINE(buffer);
}


/**
 * Checks the initialization of command and set maps.
 *
 * @param userCommand The user command buffer to check.
 * @param commandMap The command map to check.
 * @param setMap The set map to check.
 * @return Error code indicating the result of the check.
 */
int checkPreProcessing(UserCommandPtr userCommand, HashMapPtr commandMap, HashMapPtr setMap)
{
    if(!commandMap)
        return troubleInitCommands;

    if(!setMap)
        return troubleInitSet;

    if(!userCommand)
        return troubleInitUserBuffer;

    return TRUE;
}


/**
 * Frees the memory allocated for program structures.
 *
 * @param userCommand The UserCommand structure to free.
 * @param commandMap The command map to free.
 * @param setMap The set map to free.
 */
void freeProgramStructures(UserCommandPtr userCommand, HashMapPtr commandMap, HashMapPtr setMap)
{
    freeUserCommand(userCommand);
    hashMapFree(commandMap);
    hashMapFree(setMap);
}


/**
 * The main function of the program.
 * The function is responsible for initializing the program and running the main loop.
 *
 * @return Exit status of the program.
 */
int main() {
    char command[MAXLEN];
    UserCommandPtr userCommand;
    HashMapPtr commandMap = initCommandMap();
    HashMapPtr setMap = initSetMap();

    userCommand = initUserCommand();
    int processingResult = checkPreProcessing(userCommand, commandMap, setMap);

    if(processingResult != TRUE)
    {
        printError(processingResult);
        return 0;
    }

    /* Print a welcome message */
    printf(WELCOME_MSG);

    getUserCommand(command);

    while(strcmp(command, EXIT_COMMAND) != 0) {

        printf("Received Command: %s\n", command);
        printf("asdasdasdasdasdasdasd");
        processingResult = parseUserCommand(userCommand, &command, setMap);

        if (processingResult == TRUE) {
            processingResult = runCommand(commandMap, userCommand);
        }

        if (processingResult != TRUE)
            printError(processingResult);

        getUserCommand(command);
    }

    printf(EXIT_MSG);

    freeProgramStructures(userCommand, commandMap, setMap);

    return 1;
}