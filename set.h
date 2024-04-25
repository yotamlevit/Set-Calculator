/*
  Created by Yotam Levit on 25/04/2024.
*/

#ifndef C_ALGORITHEMS_SET_H
#define C_ALGORITHEMS_SET_H


typedef struct set
{
    char setData[16];
} Set;


/* Function Headers */
void initSet(Set* set);
void printSet(Set* set);
void readSet(Set* set, int* numbers);
Set* unionSet(Set* originalSet, Set* mergeSet);
Set* intersectSet(Set* originalSet, Set* intersectSet);
Set* subSet(Set* originalSet, Set* subSet);
Set* symDiffSet(Set* originalSet, Set* subSet);



void addNumber(Set* set, int num);

#endif /* C_ALGORITHEMS_SET_H */
