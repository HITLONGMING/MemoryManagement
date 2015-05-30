//
//  ModelSetWindow.h
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#ifndef __MemoryManagement__ModelSetWindow__
#define __MemoryManagement__ModelSetWindow__

#include <stdio.h>
#include "Process.h"

/**工作集窗口*/
typedef struct ModelSetWindow{
    /**该窗口对应的进程*/
    Process *process;
    /**错误次数，用于计算错误率*/
    int wrongCount;
    /**对应进程是否访问结束*/
    BOOL hasfinished;
    /**当前对象是否已经把结果打印出来了*/
    BOOL hasLoggedResult;
    /**当前访问到的步数*/
    int currentStep;

}ModelSetWindow;

void window_initWithProcess(ModelSetWindow *window, Process *process);

/**
 *  获取下一个页
 */
ELEM_TYPE window_getNextPage(ModelSetWindow *window, int end);
/**
 *  工作窗口后移至某一值，将移出窗口并且不用的页从内存删除
 */
void window_moveTo(ModelSetWindow *window, int end);
/**
 *  内存空间不够时将该进程暂停
 */
void window_stop(ModelSetWindow *window);
/**
 *  工作集合窗口开始工作，后移一位，表示模拟页调用，返回当前该进程占用内存页面数
 */
int window_run(ModelSetWindow *window);

#endif /* defined(__MemoryManagement__ModelSetWindow__) */
