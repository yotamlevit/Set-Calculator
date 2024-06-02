/*
  Created by Yotam Levit on 26/04/2024.
*/

#include "SetMap.h"


/**
 * Initializes the set map with predefined sets.
 *
 * @return A pointer to the initialized set map, or NULL on failure.
 */
HashMapPtr initSetMap() {
    int i;
    char *setNames[NUM_OF_SETS] = {"SETA", "SETB", "SETC", "SETD", "SETE",
                                   "SETF"};
    SetPtr set;

    HashMapPtr map = createHashMap(NUM_OF_SETS, NULL, NULL);

    if (!map)
        return NULL;

    for (i = 0; i < NUM_OF_SETS; i++) {
        set = initSet();

        if(!set)
            return NULL;

        hashMapInsert(map, setNames[i], set);
    }

    return map;
}
