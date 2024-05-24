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


SetPtr initSet()
{
    SetPtr set = (SetPtr)malloc(sizeof(Set));

    if(!set)
        return NULL;

    unsigned char mask = {0};
    int i;

    for (i = 0; i < ARRAY_DATA_SIZE; ++i) {
        set->setData[i] = mask;
    }

    return set;
}

char* add_set_number_str(char* pStr, int number)
{
    if(number < 10)
    {
        *pStr++ = CAST_ASCII_NUMBER(number);
        return pStr;
    }

    pStr = add_set_number_str(pStr, number / 10);
    *pStr++ = CAST_ASCII_NUMBER(number % 10);

    return pStr;

}


int printSet(SetPtr set, char* setStr)
{
    int byteIndex, bitIndex, countLineElements = 0;
    unsigned char* currByte;
    setStr = (char* )malloc(sizeof(char) * MAX_SET_STRING_LEN);
    char* currChar = setStr;

    *currChar++ = '(';

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++) {
        currByte = set->setData + byteIndex;

        for (bitIndex = 0; bitIndex < BYTE_SIZE; bitIndex++) {
            if(*currByte & (1 << bitIndex)){

                countLineElements++;
                if(countLineElements % MAX_VALUE_IN_LINE == 0)
                    *(currChar-1) = NEW_LINE;

                currChar = add_set_number_str(currChar, byteIndex * BYTE_SIZE + bitIndex);
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


int readSet(SetPtr set, int* numbers)
{
    int byteIndex, bitIndex;

    while (*numbers != END_OF_LIST)
    {
        byteIndex = *numbers / BYTE_SIZE;
        bitIndex = *numbers - byteIndex * BYTE_SIZE;

        set->setData[byteIndex] |= (1 << bitIndex);

        numbers++;
    }

    return TRUE;
}


int unionSet(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    int byteIndex;

    initSet(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] | setB->setData[byteIndex];

    return TRUE;
}


int intersectSet(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    int byteIndex;

    initSet(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] & setB->setData[byteIndex];

    return TRUE;
}


int subSet(SetPtr originalSet, SetPtr subSet, SetPtr outputSet)
{
    int byteIndex;

    initSet(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = originalSet->setData[byteIndex] & ~subSet->setData[byteIndex];

    return TRUE;
}

int symDiffSet(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    Set unionSetResult, intersectSetResult;

    initSet(outputSet);

    unionSet(setA, setB, &unionSetResult);
    intersectSet(setA, setB, &intersectSetResult);

    subSet(&unionSetResult, &intersectSetResult, outputSet);

    return TRUE;
}

