//
//  main.c
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ModelSetWindow.h"

#define kProcessCount   4

int main(int argc, const char * argv[]) {
    
    //准备生成随机数
    srand((unsigned)time(NULL));
    
    //第一个进程
    Process p1;
    process_initWithIDAndPageCount(&p1, 1, 40000);
    //第二个进程
    Process p2;
    process_initWithIDAndPageCount(&p2, 2, 39000);
    //第三个进程
    Process p3;
    process_initWithIDAndPageCount(&p3, 3, 38000);
    //第四个进程
    Process p4;
    process_initWithIDAndPageCount(&p4, 4, 40000);
    
    //四个进程对应的窗口
    ModelSetWindow window1;
    window_initWithProcess(&window1, &p1);
    ModelSetWindow window2;
    window_initWithProcess(&window2, &p2);
    ModelSetWindow window3;
    window_initWithProcess(&window3, &p3);
    ModelSetWindow window4;
    window_initWithProcess(&window4, &p4);
    
    ModelSetWindow windows[kProcessCount] = {window1, window2, window3, window4};
    
    while (1) {
        //查看是否全部进程都结束了
        BOOL hasFinish = YES;
        for (int i = 0; i < kProcessCount; i++) {
            ModelSetWindow *w = &windows[i];
            if (w->hasfinished == NO) {
                hasFinish = NO;
                break;
            }
            hasFinish = YES;
        }
        
        if (hasFinish == NO) {
            int count = 0;

            for (int i = 0; i < kProcessCount; i++) {
                ModelSetWindow *w = &windows[i];
                count += window_run(w);
            }
//            printf("%d\n", count);
            
            if (count > kMemoryPageCount) {
                ModelSetWindow *selectedWindow;
                //选一个正在运行的进程
                do {
                    int random = rand() % kProcessCount;
                    selectedWindow = &windows[random];
                } while (selectedWindow->process->isRunning != YES || selectedWindow->hasfinished == YES);
                
                window_stop(selectedWindow);
                printf("本次超出内存容量，暂停进程%d\n", selectedWindow->process->processID);
            } else if (kMemoryPageCount - count > 500) {
                //找一个暂停的进程继续运行
                for (int i = 0; i < kProcessCount; i++) {
                    ModelSetWindow *w = &windows[i];
                    if (w->process->isRunning == NO) {
                        printf("内存空闲，将进程%d执行\n", w->process->processID);
                        w->process->isRunning = YES;
                        break;
                    }
                }
            }
            
        } else {
            break;
        }
    }
    
    printf("执行完毕\n");
    
    return 0;
}
