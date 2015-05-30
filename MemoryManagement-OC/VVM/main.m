//
//  main.m
//  VVM
//
//  Created by Chen Yizhuo on 15/5/28.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Process.h"
#import "ModelSetWindow.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        //第一个进程
        Process *p1 = [[Process alloc] initWithProcessID:1 processPageCount:40000];
        //第二个进程
        Process *p2 = [[Process alloc] initWithProcessID:2 processPageCount:40000];
        //第三个进程
        Process *p3 = [[Process alloc] initWithProcessID:3 processPageCount:38000];
        Process *p4 = [[Process alloc] initWithProcessID:3 processPageCount:39000];
        Process *p5 = [[Process alloc] initWithProcessID:3 processPageCount:41000];
        
        //p1进程对应的窗口
        ModelSetWindow *window1 = [[ModelSetWindow alloc] initWithProcess:p1];
        //p2进程对应的窗口
        ModelSetWindow *window2 = [[ModelSetWindow alloc] initWithProcess:p2];
        //p3对应窗口
        ModelSetWindow *window3 = [[ModelSetWindow alloc] initWithProcess:p3];
        ModelSetWindow *window4 = [[ModelSetWindow alloc] initWithProcess:p4];
        ModelSetWindow *window5 = [[ModelSetWindow alloc] initWithProcess:p5];
        
        NSArray *windows = @[window1, window2, window3, window4, window5];
        
        while (1) {
            BOOL hasFinish = YES;
            for (ModelSetWindow *window in windows) {
                if (window.hasfinished == NO) {
                    hasFinish = NO;
                    break;
                }
                hasFinish = YES;
            }
            if (hasFinish == NO) {
                int count = 0;
//                NSSet *allPages = [NSSet set];
                for (ModelSetWindow *w in windows) {
                    count += [w run];
//                    [w run];
//                    allPages = [allPages setByAddingObjectsFromSet:w.process.set];
                }
//                NSLog(@"%d", count);
                
                if (count > kMemoryPageCount) {
                    ModelSetWindow *selectedWindow = nil;
                    //选一个正在运行的进程
                    do {
                        int random = arc4random() % windows.count;
                        selectedWindow = windows[random];
                    } while (selectedWindow.process.isRunning != YES);
                    
                    [selectedWindow stop];
                    NSLog(@"本次超出内存容量，暂停进程%d", selectedWindow.process.processID);
                } else if (kMemoryPageCount - count > 500) {
                    //找一个暂停的进程继续运行
                    for (ModelSetWindow *w in windows) {
                        if (w.process.isRunning == NO) {
                            NSLog(@"内存空闲，将进程%d执行", w.process.processID);
                            w.process.isRunning = YES;
                            break;
                        }
                    }
                }
                
            } else {
                break;
            }
        }
        
        NSLog(@"执行完毕");
    }
    return 0;
}
