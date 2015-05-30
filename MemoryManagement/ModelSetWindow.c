//
//  ModelSetWindow.c
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#include "ModelSetWindow.h"
#include <stdlib.h>

void window_initWithProcess(ModelSetWindow *window, Process *process) {
    window->process = process;
    window->hasfinished = NO;
    window->hasLoggedResult = NO;
    window->currentStep = 0;
    window->wrongCount = 0;
}

/**
 *  获取下一个页
 */
ELEM_TYPE window_getNextPage(ModelSetWindow *window, int end) {
    if (end >= window->process->sequence_count) {
        return 0;
    }
    
    return window->process->sequence[end];
}

/**
 *  工作窗口后移至某一值，将移出窗口并且不用的页从内存删除
 */
void window_moveTo(ModelSetWindow *window, int end) {
    if (window->process->set == NULL) {
        window->process->set = (Set *)malloc(sizeof(Set));
        set_init(window->process->set);
    }
    //有可能当前窗口还没完全移入
    int start = MAX(0, end - kModelSetWindowSize + 1);
    //把用到的加入内存
    for (int i = start; i <= end; i++) {
        process_addPage(window->process, window->process->sequence[i]);
    }
}

/**
 *  内存空间不够时将该进程暂停
 */
void window_stop(ModelSetWindow *window) {
    window->process->isRunning = NO;
}

/**
 *  工作集合窗口开始工作，后移一位，表示模拟页调用，返回当前该进程占用内存页面数
 */
int window_run(ModelSetWindow *window) {
    //如果新掉进来的页在原来中找不到，则说明此次出现页错误
    if (window->process->set != NULL && set_containsObject(window->process->set, window_getNextPage(window, window->currentStep)) == NO) {
        window->wrongCount++;
//        printf("进程%d发生页错误，wrongCount = %d\n", window->process->processID, window->wrongCount);
    }
    
    //把全部的清除，表示把“不用的删除”，因为接下来会重新对窗口添加一遍
    free(window->process->set);
    window->process->set = NULL;
    
    //如果当前进程被暂停
    if (window->process->isRunning == NO) {
        return 0;
    }
    //如果当前进程执行完毕
    if (window->currentStep >= window->process->sequence_count) {
        window->hasfinished = YES;
        if (window->hasLoggedResult == NO) {
            printf("进程%d执行完毕，页错误次数%d，页错误率%f\n", window->process->processID, window->wrongCount, (float)window->wrongCount / window->process->processPageCount);
            window->hasLoggedResult = YES;
        }
        return 0;
    }
    
    window_moveTo(window, window->currentStep);
    window->currentStep++;
//    printf("currentStep = %d, window count = %d\n", window->currentStep, (int)window->process->set->length);
    return (int)window->process->set->length;
}
