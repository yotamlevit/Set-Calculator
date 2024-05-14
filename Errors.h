/*
  Created by Yotam Levit on 26/04/2024.
*/

#ifndef C_ALGORITHEMS_ERRORS_H
#define C_ALGORITHEMS_ERRORS_H


#define MAX_ERROR_LEN 1000

typedef enum {
    undefinedSetNameError,
    undefinedCommandNameError,
    valueError,
    missingEndOfListError,
    typeError,
    missingParamError,
    NumberOfErrors
} ErrorCode;

typedef struct {
    int error_id; /*The ID of the error.*/
    char error_msg[MAX_ERROR_LEN]; /*The error message associated with the error.*/
} Error, * ErrorPtr;


ErrorPtr getError(ErrorCode errorCode);

#endif /*C_ALGORITHEMS_ERRORS_H*/
