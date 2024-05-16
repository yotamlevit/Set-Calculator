/*
  Created by Yotam Levit on 25/04/2024.
*/

#ifndef C_ALGORITHEMS_SET_H
#define C_ALGORITHEMS_SET_H

#define BYTE_SIZE 8
#define END_OF_LIST (-1)
#define MAX_NUMBER 128
#define ARRAY_DATA_SIZE 16

#define SINGLE_DIGIT_NUMBERS 10
#define DOUBLE_DIGIT_NUMBERS MAX_NUMBER - SINGLE_DIGIT_NUMBERS - (MAX_NUMBER - 100) //90
#define TRIPLE_DIGIT_NUMBER MAX_NUMBER - 99

typedef struct set
{
    unsigned char setData[ARRAY_DATA_SIZE];
} Set, * SetPtr;


/* Function Headers */
void* initSet(SetPtr set);
char* printSet(SetPtr set);
void* readSet(SetPtr set, int* numbers);
void* unionSet(SetPtr setA, SetPtr setB, SetPtr outputSet);
void* intersectSet(SetPtr setA, SetPtr setB, SetPtr outputSet);
void* subSet(SetPtr originalSet, SetPtr subSet, SetPtr outputSet);
void* symDiffSet(SetPtr setA, SetPtr setB, SetPtr outputSet);



void addNumber(Set* set, int num);

#endif /* C_ALGORITHEMS_SET_H */
