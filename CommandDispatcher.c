/*
* Created by Yotam Levit on 16/05/2024.
*/

#include <stdlib.h>
#include <strings.h>

#include "CommandDispatcher.h"
#include "set.h"
#include "Errors.h"
#include "CommandParser.h"

#define NUM_OF_COMMANDS 6
#define EMPTY_SET_MSG "The set is empty"
#define EMPTY_SET_VALUE "()"


/**
 * Dispatches a function that operates on three sets.
 *
 * @param func The function to be dispatched.
 * @param userCommand The user command containing the sets and arguments.
 * @return Error code indicating the result of the operation.
 */
int threeSetDispatcher(FunctionPointer func, UserCommandPtr userCommand)
{
    if (userCommand->setsCount != 3)
        return userCommand->setsCount < 3 ? missingParamError : tooManySets;

    if (userCommand->argCount)
        return extraTextAfterCommand;

    return func.threeSetFunctions(userCommand->sets[0], userCommand->sets[1], userCommand->sets[2]);
}


/**
 * Dispatches a function that outputs a string representation of a set.
 *
 * @param func The function to be dispatched.
 * @param userCommand The user command containing the sets and arguments.
 * @return Error code indicating the result of the operation.
 */
int strOutputSetDispatcher(FunctionPointer func, UserCommandPtr userCommand)
{
    int result;
    char *output = NULL;

    if (userCommand->setsCount != 1)
        return userCommand->setsCount < 1 ? missingParamError : extraTextAfterCommand;

    if (userCommand->argCount > 0)
        return extraTextAfterCommand;

    result = func.strOutputSetFunction(userCommand->sets[0], &output);

    if(strcmp(output, EMPTY_SET_VALUE) == 0)
        printf("\n%s\n\n", EMPTY_SET_MSG);
    else
        printf("\n%s\n\n", output);

    free(output);

    return result;
}


/**
 * Validates the input numbers for set operations.
 *
 * @param numbers The array of numbers to be validated.
 * @param listLength The length of the numbers array.
 * @return Error code indicating the result of the validation.
 */
int validateNumberInput(const int* numbers, int listLength)
{
    int i;

    if(numbers[listLength-1] != END_OF_LIST)
        return missingEndOfListError;

    for (i = 0; i < listLength-1; ++i) {
        if(numbers[i] >= MAX_NUMBER || numbers[i] < MIN_NUMBER)
            return valueError;
    }

    return TRUE;
}


/**
 * Dispatches a function that operates on a set and a list of numbers.
 *
 * @param func The function to be dispatched.
 * @param userCommand The user command containing the sets and arguments.
 * @return Error code indicating the result of the operation.
 */
int setAndNumbersDispatcher(FunctionPointer func, UserCommandPtr userCommand)
{
    int result;
    ErrorCode validationResult;

    if(userCommand->setsCount != 1)
        return userCommand->setsCount < 1 ? missingParamError : tooManySets;

    if (userCommand->argCount == 0)
        return missingParamError;

    validationResult = validateNumberInput(userCommand->arguments, userCommand->argCount);

    if(validationResult != TRUE)
        return validationResult;

    result = func.setAndNumbersFunction(userCommand->sets[0], userCommand->arguments);

    return result;
}


/**
 * Initializes the command map with predefined commands and their respective functions.
 *
 * @return The initialized command map.
 */
HashMapPtr initCommandMap() {
    int i;
    char *commandNames[NUM_OF_COMMANDS] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set",
                                           "symdiff_set"};

    CommandMapValue *commandsFunctions[NUM_OF_COMMANDS];
    for (i = 0; i < NUM_OF_COMMANDS; ++i) {
        commandsFunctions[i] = malloc(sizeof(CommandMapValue));
    }
    *commandsFunctions[0] = (CommandMapValue){{.setAndNumbersFunction = readSet}, setAndNumbersDispatcher};
    *commandsFunctions[1] = (CommandMapValue){{.strOutputSetFunction = printSet}, strOutputSetDispatcher};
    *commandsFunctions[2] = (CommandMapValue){{.threeSetFunctions = unionSet}, threeSetDispatcher};
    *commandsFunctions[3] = (CommandMapValue){{.threeSetFunctions = intersectSet}, threeSetDispatcher};
    *commandsFunctions[4] = (CommandMapValue){{.threeSetFunctions = subSet}, threeSetDispatcher};
    *commandsFunctions[5] = (CommandMapValue){{.threeSetFunctions = symDiffSet}, threeSetDispatcher};

    HashMapPtr map = createHashMap(NUM_OF_COMMANDS, NULL, NULL);

    if (!map)
        return NULL;

    for (i = 0; i < NUM_OF_COMMANDS; i++) {
        hashMapInsert(map, commandNames[i], commandsFunctions[i]);
    }

    return map;
}


/**
 * Executes the user command using the command map.
 *
 * @param commandMap The command map containing the command functions.
 * @param command The user command to be executed.
 * @return Error code indicating the result of the command execution.
 */
int runCommand(HashMapPtr commandMap, UserCommandPtr command)
{
    CommandMapValuePtr commandFunction = (CommandMapValuePtr)hashMapFind(commandMap, command->command);

    if (!commandFunction)
        return undefinedCommandNameError;

    return commandFunction->functionDispatcher(commandFunction->commandFunction, command);
}

