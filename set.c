/*
  Created by Yotam Levit on 25/04/2024.
*/

#include "stdio.h"

#include "set.h"



void printSet(Set* s) {
    for (int i = 0; i < 16; i++) {
        printf("%02x ", (unsigned char)s->setData[i]);
    }
    printf("\n");
}