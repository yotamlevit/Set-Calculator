/*
* Created by Yotam Levit on 16/05/2024.
*/

#include <stdio.h>

#include "Errors.h"


/**
 * Retrieves the array of predefined error messages.
 *
 * @return A pointer to the array of error messages.
 */
ErrorPtr getErrors()
{
    static Error Errors[NumberOfErrors] = {
            {undefinedSetNameError, "Undefined set name"},
            {undefinedCommandNameError, "Undefined command name"},
            {valueError, "Invalid set member – value out of range"},
            {missingEndOfListError, "List of set members is not terminated correctly"},
            {typeError, "Invalid set member – not an integer"},
            {missingParamError, "Missing parameter"},
            {missingCommand, "Missing command"},
            {troubleParsingCommandArguments, "There was a problem parsing command arguments"},
            {troubleParsingCommandSETS, "There was a problem parsing command sets"},
            {tooManySets, "Too many sets in command"},
            {extraTextAfterCommand, "Extraneous text after end of command"},
            {troubleInitCommands, "There was a problem initializing a command"},
            {troubleInitSet, "There was a problem initializing a set"},
            {troubleInitUserBuffer, "There was a problem initializing a user buffer"},
            {illegalComma, "Illegal comma"},
            {consecutiveCommas, "Multiple consecutive commas"},
            {missingComma, "Missing comma"}
    };

    return Errors;
}


/**
 * Retrieves the error message associated with a specific error code.
 *
 * @param errorCode The error code for which to retrieve the error message.
 * @return A pointer to the error message corresponding to the given error code.
 */
ErrorPtr getError(ErrorCode errorCode)
{
    ErrorPtr errors = getErrors();
    return &errors[errorCode-2];
}


/**
 * Prints the error message associated with a specific error code to the standard output.
 *
 * @param errorCode The error code for which to print the error message.
 */
void printError(ErrorCode errorCode)
{
    printf("%s\n", getError(errorCode)->error_msg);
}
