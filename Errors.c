//
// Created by Yotam Levit on 26/04/2024.
//

#include <stdio.h>

#include "Errors.h"

ErrorPtr getErrors()
{
    static Error Errors[NumberOfErrors] = {
            {undefinedSetNameError, "Undefined set name"},
            {undefinedCommandNameError, "Undefined commend name"},
            {valueError, "Invalid set member – value out of range"},
            {missingEndOfListError, "List of set members is not terminated correctly"},
            {typeError, "Invalid set member – not an integer"},
            {missingParamError, "Missing parameter"}
    };

    return Errors;
}


ErrorPtr getError(ErrorCode errorCode)
{
    ErrorPtr errors = getErrors();
    return &errors[errorCode];
}

void printError(ErrorCode errorCode)
{
    printf("%s\n", getErrors(errorCode)->error_msg);
}
