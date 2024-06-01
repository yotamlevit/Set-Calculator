//
// Created by Yotam Levit on 16/05/2024.
//

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>

#include "CommandParser.h"

#define IS_ARGUMENT_SET(argument) strstr(argument, "SET") != NULL || strstr(argument, "set") != NULL
#define IS_CH_WHITE_SPACE(ch) *str == *SPACE || *str == TAB
#define DELIMITER ","
#define EOS '\0'
#define NEGATIVE_SIGN '-'
#define TAB '\t'
#define SPACE " "
#define BASE_10 10


void initUserCommand(UserCommandPtr commandDTO)
{
    commandDTO->arguments = NULL;
    commandDTO->argCount = 0;
    commandDTO->command = NULL;
    commandDTO->setsCount = 0;
}

void resetUserCommand(UserCommandPtr commandDTO)
{
    int i;
    free(commandDTO->command);
    commandDTO->setsCount = 0;
    if (commandDTO->arguments) {
        free(commandDTO->arguments);
        commandDTO->arguments = NULL;
        commandDTO->argCount = 0;
    }

}

void removeWhiteSpaces(char *str) {
    char* temp = str;
    do {
        while (*temp == *SPACE || *temp == TAB) {
            ++temp;
        }
    } while (*str++ = *temp++);
}


int isStrNumber(const char* str)
{
    if (*str == NEGATIVE_SIGN) {
        str++; // Skip the leading '-' sign if present
    }

    if (*str == EOS) {
        return FALSE; // If the string is empty after skipping '-', return FALSE
    }

    while (*str) {
        if (!isdigit(*str)) {
            return FALSE; // Found a non-digit character
        }
        str++;
    }
    return TRUE;
}


int extractCommand(UserCommandPtr userCommand, char* command)
{
    char* token;
    if(command == NULL || strlen(command) == 0)
        return missingCommand;

    token = strtok(command, SPACE);
    userCommand->command = strdup(token);

    if (strchr(userCommand->command, *DELIMITER) != NULL)
        return illegalComma;

    return TRUE;
}


int validateDelimiters(char* str, char delimiter)
{
    char* chBeforeWhiteSpace = str;

    while(IS_CH_WHITE_SPACE(*str))
    {
        str++;
        printf("Asdasd");
    }

    if (*str++ == delimiter)
        return illegalComma;

    while (*str != EOS)
    {
        if (!(IS_CH_WHITE_SPACE(*str)))
        {
            if (*chBeforeWhiteSpace == delimiter && *str == delimiter)
                return consecutiveCommas;
            if (*chBeforeWhiteSpace != delimiter && *str != delimiter && (IS_CH_WHITE_SPACE(*(chBeforeWhiteSpace=1)) ||
                    IS_CH_WHITE_SPACE(*(str-1))))
                return missingComma;
            chBeforeWhiteSpace = str;
        }
        str++;
    }

    if (str[-1] == delimiter)
        return extraTextAfterCommand;

    return TRUE;
}

int validateCommandArg(char* inputCommand, char* executeCommand, char delimiter)
{
    char* commandArgs = inputCommand + strlen(executeCommand) +1;
    int validationResult = validateDelimiters(commandArgs, delimiter);
    removeWhiteSpaces(commandArgs);
    return validationResult;
}


int processSetArg(char* token, UserCommandPtr userCommand, HashMapPtr setMap)
{
    SetPtr set;
    int processResult = TRUE;

    set = hashMapFind(setMap, token);
    if(set)
        userCommand->sets[userCommand->setsCount++] = set;
    else
        processResult = undefinedSetNameError;

    return processResult;
}

int processNumeralArg(char* token, UserCommandPtr userCommand)
{
    int processResult = TRUE;
    char* endptr;
    long int inputNum;

    userCommand->arguments = (int*)realloc(userCommand->arguments, ++userCommand->argCount * sizeof(int));

    if (!userCommand->arguments)
        processResult = troubleParsingCommandArguments;

    if (!isStrNumber(token))
        processResult = typeError;

    inputNum = strtol(token, endptr, BASE_10);

    if (errno == ERANGE)
        return valueError;

    userCommand->arguments[userCommand->argCount - 1] = (int)inputNum;

    return processResult;
}


int processCommandArgs(char* token, UserCommandPtr userCommand, HashMapPtr setMap)
{
    int processResult;
    if (IS_ARGUMENT_SET(token))
        processResult = processSetArg(token, userCommand, setMap);
    else
        processResult = processNumeralArg(token, userCommand);

    return processResult;
}

int parseUserCommand(UserCommandPtr userCommand, char* command, HashMapPtr setMap)
{
    char* token;
    int processResult;

    resetUserCommand(userCommand);

    processResult = extractCommand(userCommand, command);

    if (processResult == TRUE)
        processResult = validateCommandArg(command, userCommand->command, *DELIMITER);

    while ((token = strtok(NULL, DELIMITER)) != NULL && processResult == TRUE)
    {
        processResult = processCommandArgs(token, userCommand, setMap);
    }

    return processResult;
}


void freeUserCommand(UserCommandPtr cmd) {
    if (cmd) {
        free(cmd->command);
        free(cmd->arguments);
        free(cmd);
    }
}