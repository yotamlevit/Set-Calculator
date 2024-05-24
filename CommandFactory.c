//
// Created by Yotam Levit on 14/05/2024.
//

#include "stdlib.h"

#include "CommandFactory.h"
#include "set.h"
#include "Errors.h"
#include "CommandParser.h"

#define NUM_OF_COMMANDS 6


int threeSetFunctions(FunctionPointer func, UserCommandPtr userCommand)
{
    if (userCommand->setsCount != 3)
        return userCommand->setsCount < 3 ? missingParamError : tooManySets;

    if (userCommand->argCount)
        return extraTextAfterCommand;

    return func(userCommand->sets[0], userCommand->sets[1], userCommand->sets[2]);
}

int strOutputSetFunctions(FunctionPointer func, UserCommandPtr userCommand)
{
    int result;
    char *output = NULL;

    if (userCommand->setsCount != 1)
        return userCommand->setsCount < 1 ? missingParamError : tooManySets;

    if (userCommand->argCount > 0)
        return extraTextAfterCommand;

    result = func(userCommand->sets[0], output);

    printf("%s", output);

    return result;
}

int* convertAToIntList(char** numberList, int listLength)
{
    int i;
    //int intList[listLength];
    int* intList = (int*) malloc( listLength * sizeof(int));

    for (i = 0; i < listLength; ++i) {
        intList[i] = atoi(numberList[i]);
    }

    return intList;
}

int setAndNumbersFunction(FunctionPointer func, UserCommandPtr userCommand)
{
    int* numbers;

    if(userCommand->argCount < 1)
        return missingParamError;

    numbers = convertAToIntList(userCommand->arguments, userCommand->argCount);


    if(numbers[userCommand->argCount-1] != END_OF_LIST)
        return missingEndOfListError;

    return func(userCommand->sets[0], numbers);
}

HashMapPtr initCommandMap() {
    int i;
    char *commandNames[NUM_OF_COMMANDS] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set",
                                           "symdiff_set"};
    CommandMapValuePtr commandsFunctions[NUM_OF_COMMANDS] = {{(FunctionPointer) readSet,      (DecoratorPointer) setAndNumbersFunction},
                                                             {(FunctionPointer) printSet,     (DecoratorPointer) strOutputSetFunctions},
                                                             {(FunctionPointer) unionSet,     (DecoratorPointer) threeSetFunctions},
                                                             {(FunctionPointer) intersectSet, (DecoratorPointer) threeSetFunctions},
                                                             {(FunctionPointer) subSet,       (DecoratorPointer) threeSetFunctions},
                                                             {(FunctionPointer) symDiffSet,   (DecoratorPointer) threeSetFunctions}
    };

    HashMapPtr map = createHashMap(NUM_OF_COMMANDS, NULL, NULL);

    if (!map)
        return NULL;

    for (i = 0; i < NUM_OF_COMMANDS; i++) {
        hashMapInsert(map, commandNames[i], commandsFunctions[i]);
    }

    return map;
}


int runCommand(HashMapPtr commandMap, UserCommandPtr command)
{
    CommandMapValuePtr commandFunction = hashMapFind(commandMap, command->command);

    if (!commandFunction)
        return undefinedCommandNameError;

    commandFunction->functionDecorator(commandFunction->commandFunction, command);
    return 1;
}

