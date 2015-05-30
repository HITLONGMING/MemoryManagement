//
//  Set.c
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#include "Set.h"
#include <stdlib.h>

void set_init(Set *set) {
    for (int i = 0; i < MAX_LENGTH; i++) {
        set->data[i] = 0;
    }
    set->length = 0;
}

void set_add(Set *set, ELEM_TYPE elem) {
    if (set_containsObject(set, elem)) {
        return;
    }
    set->data[set->length++] = elem;
}

BOOL set_containsObject(Set *set, ELEM_TYPE elem) {
    for (int i = 0; i < set->length; i++) {
        if (set->data[i] == elem) {
            return YES;
        }
    }
    return NO;
}