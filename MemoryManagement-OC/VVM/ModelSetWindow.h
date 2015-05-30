//
//  ModelSetWindow.h
//  VVM
//
//  Created by Chen Yizhuo on 15/5/28.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Process.h"

@interface ModelSetWindow : NSObject

@property (strong, nonatomic) Process *process;

@property (assign, nonatomic) int wrongCount;

@property (assign, nonatomic) BOOL hasfinished;

- (id)initWithProcess:(Process *)process;
/**
 *  工作窗口后移至某一值，将移出窗口并且不用的页从内存删除
 */
- (void)moveTo:(int)end;
/**
 *  内存空间不够时将该进程暂停
 */
- (void)stop;
/**
 *  工作集合窗口开始工作，后移一位，表示模拟页调用，返回当前该进程占用内存页面数
 */
- (int)run;

@end
