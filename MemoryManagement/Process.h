//
//  Process.h
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#ifndef __MemoryManagement__Process__
#define __MemoryManagement__Process__

#include <stdio.h>
#include "Set.h"
#include "CONST.h"

/**进程*/
typedef struct Process {
    /**进程id*/
    int processID;
    /**进程页面数*/
    int processPageCount;
    /**进程工作集合*/
    Set *set;
    /**是否正在执行*/
    BOOL isRunning;
    /**内存访问顺序*/
    ELEM_TYPE sequence[MAX_LENGTH];
    /**内存访问顺序的大小*/
    int sequence_count;
} Process;

void process_initWithIDAndPageCount(Process *process, int processID, int count);

/**将该进程用到的新的页调入内存*/
void process_addPage(Process *process, int pageNumber);

/**从文件读取生成页面访问序列*/
void process_getSequence(Process *process);

#endif /* defined(__MemoryManagement__Process__) */
