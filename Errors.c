//
// Created by Yotam Levit on 26/04/2024.
//

#include <stdio.h>

#include "Errors.h"

ErrorPtr getErrors()
{
    static Error Errors[NumberOfErrors] = {
            {undefinedSetNameError, "Undefined set name"},
            {undefinedCommandNameError, "Undefined command name"},
            {valueError, "Invalid set member – value out of range"},
            {missingEndOfListError, "List of set members is not terminated correctly"},
            {typeError, "Invalid set member – not an integer"},
            {missingParamError, "Missing parameter"},
            {troubleParsingCommandArguments, "There was a problem parsing command arguments"},
            {troubleParsingCommandSETS, "There was a problem parsing command sets"},
            {tooManySets, "Too many sets in command"},
            {extraTextAfterCommand, "Extraneous text after end of command"},
            {troubleInitCommands, "There was a problem initializing a command"},
            {troubleInitSet, "There was a problem initializing a set"}
    };

    return Errors;
}


ErrorPtr getError(ErrorCode errorCode)
{
    ErrorPtr errors = getErrors();
    return &errors[errorCode-2];
}

void printError(ErrorCode errorCode)
{
    printf("%s\n", getError(errorCode)->error_msg);
}
