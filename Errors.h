/*
  Created by Yotam Levit on 26/04/2024.
*/

#ifndef C_ALGORITHEMS_ERRORS_H
#define C_ALGORITHEMS_ERRORS_H


#define MAX_ERROR_LEN 1000

typedef enum {FALSE = 0, TRUE} boolean;

typedef enum {
    undefinedSetNameError = 2,
    undefinedCommandNameError,
    valueError,
    missingEndOfListError,
    typeError,
    missingParamError,
    missingCommand,
    troubleParsingCommandArguments,
    troubleParsingCommandSETS,
    tooManySets,
    extraTextAfterCommand,
    troubleInitCommands,
    troubleInitSet,
    illegalComma,
    consecutiveCommas,
    missingComma,
    NumberOfErrors
} ErrorCode;

typedef struct {
    int error_id; /*The ID of the error.*/
    char error_msg[MAX_ERROR_LEN]; /*The error message associated with the error.*/
} Error, * ErrorPtr;


ErrorPtr getError(ErrorCode errorCode);
void printError(ErrorCode errorCode);

#endif /*C_ALGORITHEMS_ERRORS_H*/
