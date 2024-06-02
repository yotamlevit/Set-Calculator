/*
* Created by Yotam Levit on 16/05/2024.
*/

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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


/**
 * Initializes the UserCommand structure.
 *
 * @return command The initialized UserCommand structure .
 */
UserCommandPtr initUserCommand()
{
    UserCommandPtr command = (UserCommandPtr)malloc(sizeof(UserCommand));
    if (command) {
        command->arguments = NULL;
        command->argCount = 0;
        command->command = NULL;
        command->setsCount = 0;
    }
    return command;
}


/**
 * Resets the UserCommand structure, freeing any allocated memory.
 *
 * @param commandDTO The UserCommand structure to reset.
 */
void resetUserCommand(UserCommandPtr commandDTO)
{
    if (commandDTO->command != "") {
        free(commandDTO->command);
        commandDTO->command = NULL;
    }
    commandDTO->setsCount = 0;
    if (commandDTO->arguments) {
        free(commandDTO->arguments);
        commandDTO->arguments = NULL;
        commandDTO->argCount = 0;
    }

}


/**
 * Removes all whitespace characters from a string.
 *
 * @param str The string to remove whitespace from.
 */
void removeWhiteSpaces(char *str) {
    char* temp = str;
    do {
        while (*temp == *SPACE || *temp == TAB) {
            ++temp;
        }
    } while (*str++ = *temp++);
}

/**
 * Checks if a string represents a valid number.
 *
 * @param str The string to check.
 * @return TRUE if the string is a number, otherwise FALSE.
 */
int isStrNumber(const char* str)
{
    if (*str == NEGATIVE_SIGN) {
        str++; /* Skip the leading '-' sign if present */
    }

    if (*str == EOS) {
        return FALSE; /* If the string is empty after skipping '-', return FALSE */
    }

    while (*str) {
        if (!isdigit(*str)) {
            return FALSE; /* Found a non-digit character */
        }
        str++;
    }
    return TRUE;
}


/**
 * Extracts the command from a string and stores it in the UserCommand structure.
 *
 * @param userCommand The UserCommand structure to store the extracted command.
 * @param command The string containing the command.
 * @return Error code indicating the result of the extraction.
 */
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


/**
 * Validates the delimiters in a string.
 *
 * @param str The string to validate.
 * @param delimiter The delimiter to validate against.
 * @return Error code indicating the result of the validation.
 */
int validateDelimiters(char* str, char delimiter)
{
    char* chBeforeWhiteSpace = str;

    while(IS_CH_WHITE_SPACE(*str))
        str++;

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


/**
 * Validates the command arguments in a string.
 *
 * @param inputCommand The input command string.
 * @param executeCommand The command to execute.
 * @param delimiter The delimiter to validate against.
 * @return Error code indicating the result of the validation.
 */
int validateCommandArg(char* inputCommand, char* executeCommand, char delimiter)
{
    char* commandArgs = inputCommand + strlen(executeCommand) +1;
    int validationResult = validateDelimiters(commandArgs, delimiter);
    removeWhiteSpaces(commandArgs);
    return validationResult;
}


/**
 * Processes a set argument and stores it in the UserCommand structure.
 *
 * @param token The set argument to process.
 * @param userCommand The UserCommand structure to store the processed argument.
 * @param setMap The map of available sets.
 * @return Error code indicating the result of the processing.
 */
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


/**
 * Processes a numeral argument and stores it in the UserCommand structure.
 *
 * @param token The numeral argument to process.
 * @param userCommand The UserCommand structure to store the processed argument.
 * @return Error code indicating the result of the processing.
 */
int processNumeralArg(char* token, UserCommandPtr userCommand)
{
    int processResult = TRUE;
    long int inputNum;
    userCommand->arguments = (int*)realloc(userCommand->arguments, ++userCommand->argCount * sizeof(int));

    if (!userCommand->arguments)
        processResult = troubleParsingCommandArguments;

    if (!isStrNumber(token))
        processResult = typeError;

    inputNum = atoi(token);

    if (errno == ERANGE)
        return valueError;

    userCommand->arguments[userCommand->argCount - 1] = (int)inputNum;

    return processResult;
}


/**
 * Processes the command arguments and stores them in the UserCommand structure.
 *
 * @param token The command argument to process.
 * @param userCommand The UserCommand structure to store the processed arguments.
 * @param setMap The map of available sets.
 * @return Error code indicating the result of the processing.
 */
int processCommandArgs(char* token, UserCommandPtr userCommand, HashMapPtr setMap)
{
    int processResult;
    if (IS_ARGUMENT_SET(token))
        processResult = processSetArg(token, userCommand, setMap);
    else
        processResult = processNumeralArg(token, userCommand);

    return processResult;
}


/**
 * Parses the user command and stores the result in the UserCommand structure.
 *
 * @param userCommand The UserCommand structure to store the parsed command.
 * @param command The string containing the command.
 * @param setMap The map of available sets.
 * @return Error code indicating the result of the parsing.
 */
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


/**
 * Frees the memory allocated for the UserCommand structure.
 *
 * @param cmd The UserCommand structure to free.
 */
void freeUserCommand(UserCommandPtr cmd) {
    if (cmd) {
        free(cmd->command);
        free(cmd->arguments);
        free(cmd);
    }
}