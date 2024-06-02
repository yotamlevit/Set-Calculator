/*
  Created by Yotam Levit on 25/04/2024.
*/

#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "Errors.h"

#define CAST_ASCII_NUMBER(number)  (number + '0')
#define MAX_VALUE_IN_LINE 16
#define NUM_PRETTIFY_OUTPUT_CHAR 2
#define NUM_CHAR_ENCLOSURE 3
#define MAX_SET_STRING_LEN SINGLE_DIGIT_NUMBERS + DOUBLE_DIGIT_NUMBERS * 2 + TRIPLE_DIGIT_NUMBER * 3 \
                            + MAX_NUMBER * NUM_PRETTIFY_OUTPUT_CHAR + (MAX_NUMBER/MAX_VALUE_IN_LINE) + NUM_CHAR_ENCLOSURE
#define NEW_LINE '\n'
#define EOL '\0'


/**
 * Resets the set to an empty state.
 *
 * @param set The set to reset.
 */
void resetSet(SetPtr set)
{
    unsigned char mask = {0};
    int i;

    for (i = 0; i < ARRAY_DATA_SIZE; ++i) {
        set->setData[i] = mask;
    }
}


/**
 * Initializes a new set and returns a pointer to it.
 *
 * @return A pointer to the initialized set, or NULL on failure.
 */
SetPtr initSet()
{
    SetPtr set = (SetPtr)malloc(sizeof(Set));

    if(!set)
        return NULL;

    resetSet(set);

    return set;
}


/**
 * This function os a recursive function that Adds a number to the set string.
 *
 * @param pStr The pointer to the set string.
 * @param number The number to add.
 * @return The updated pointer to the set string.
 */
char* addSetNumberStr(char* pStr, int number)
{
    if(number < 10)
    {
        *pStr++ = CAST_ASCII_NUMBER(number);
        return pStr;
    }

    pStr = addSetNumberStr(pStr, number / 10);
    *pStr++ = CAST_ASCII_NUMBER(number % 10);

    return pStr;

}


/**
 * Prints the set to a string.
 *
 * @param set The set to print.
 * @param setStr The pointer to the set string.
 * @return TRUE on success.
 */
int printSet(SetPtr set, char** setStr)
{
    int byteIndex, bitIndex, countLineElements = 0;
    unsigned char* currByte;
    *setStr = (char* )malloc(sizeof(char) * MAX_SET_STRING_LEN);
    char* currChar = *setStr;

    *currChar++ = '(';

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++) {
        currByte = set->setData + byteIndex;

        for (bitIndex = 0; bitIndex < BYTE_SIZE; bitIndex++) {
            if(*currByte & (1 << bitIndex)){

                countLineElements++;
                if(countLineElements % MAX_VALUE_IN_LINE == 0)
                    *(currChar-1) = NEW_LINE;

                currChar = addSetNumberStr(currChar, byteIndex * BYTE_SIZE + bitIndex);
                *currChar++ = ' ';
                *currChar++ = ',';
            }
        }
    }

    if(*(currChar-1) == ',')
        currChar -=2;

    *currChar++ = ')';
    *currChar++ = EOL;

    return TRUE;
}


/**
 * Reads a list of numbers into the set.
 * THe function adds the numbers to the set using shifting and bitwise operations.
 *
 * @param set The set to read into.
 * @param numbers The list of numbers to read.
 * @return TRUE on success.
 */
int readSet(SetPtr set, int* numbers)
{
    int byteIndex, bitIndex;

    resetSet(set);

    while (*numbers != END_OF_LIST)
    {
        byteIndex = *numbers / BYTE_SIZE;
        bitIndex = *numbers - byteIndex * BYTE_SIZE;

        set->setData[byteIndex] |= (1 << bitIndex);

        numbers++;
    }

    return TRUE;
}


/**
 * Performs the union of two sets and stores the result in the output set.
 * The union is being done using or bitwise operation between the two sets.
 *
 * @param setA The first set.
 * @param setB The second set.
 * @param outputSet The set to store the result or the union.
 * @return TRUE on success.
 */
int unionSet(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    int byteIndex;

    if(outputSet != setA && outputSet != setB)
        resetSet(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] | setB->setData[byteIndex];

    return TRUE;
}


/**
 * Performs the intersection of two sets and stores the result in the output set.
 * The intersection is being done using AND bitwise operation between the two sets.
 *
 * @param setA The first set.
 * @param setB The second set.
 * @param outputSet The set to store the intersection result.
 * @return TRUE on success.
 */
int intersectSet(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    int byteIndex;
    char tempByte;

    if(outputSet != setA && outputSet != setB)
        resetSet(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] & setB->setData[byteIndex];

    return TRUE;
}


/**
 * Performs the subtraction of one set from another and stores the result in the output set.
 * The subtraction is being done using AND bitwise operation between the original set and the sub set.
 *
 * @param originalSet The original set.
 * @param subSet The set to subtract.
 * @param outputSet The set to store the subtraction result.
 * @return TRUE on success.
 */
int subSet(SetPtr originalSet, SetPtr subSet, SetPtr outputSet)
{
    int byteIndex;

    if(outputSet != originalSet && outputSet != subSet)
        resetSet(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = originalSet->setData[byteIndex] & ~subSet->setData[byteIndex];

    return TRUE;
}


/**
 * Performs the symmetric difference of two sets and stores the result in the output set.
 *
 * @param setA The first set.
 * @param setB The second set.
 * @param outputSet The set to store the difference result.
 * @return TRUE on success.
 */
int symDiffSet(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    Set unionSetResult, intersectSetResult;

    if(outputSet != setA && outputSet != setB)
        resetSet(outputSet);

    unionSet(setA, setB, &unionSetResult);
    intersectSet(setA, setB, &intersectSetResult);

    subSet(&unionSetResult, &intersectSetResult, outputSet);

    return TRUE;
}

