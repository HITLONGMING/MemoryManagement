//
//  Set.h
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#ifndef __MemoryManagement__Set__
#define __MemoryManagement__Set__

#include <stdio.h>
#include "CONST.h"

/**集合*/
typedef struct Set {
    ELEM_TYPE data[MAX_LENGTH];
    int length;
} Set;

void set_init(Set *set);
/**为集合添加新元素，如果新元素已经在集合中存在，则不会添加*/
void set_add(Set *set, ELEM_TYPE elem);
/**判断当前集合是否包含某元素*/
BOOL set_containsObject(Set *set, ELEM_TYPE elem);


#endif /* defined(__MemoryManagement__Set__) */
