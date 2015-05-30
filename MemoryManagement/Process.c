//
//  Process.c
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#include "Process.h"
#include <stdlib.h>
#include <time.h>

void process_initWithIDAndPageCount(Process *process, int processID, int pageCount) {
    process->processID = processID;
    process->processPageCount = pageCount;
    process->set = (Set *)malloc(sizeof(Set));
    set_init(process->set);
    process->isRunning = YES;
    process->sequence_count = 0;
    //随机产生序列
    srand((unsigned)time(NULL));
    process_getSequence(process);
}

void process_getSequence(Process *process) {
    for (int i = 0; i < process->processPageCount; i++) {
        process->sequence[i] = rand() % kProcessPageCount + 1;
        process->sequence_count++;
    }
}

void process_addPage(Process *process, int pageNumber) {
    set_add(process->set, pageNumber);
}