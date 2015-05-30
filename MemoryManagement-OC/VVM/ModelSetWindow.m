//
//  ModelSetWindow.m
//  VVM
//
//  Created by Chen Yizhuo on 15/5/28.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#import "ModelSetWindow.h"

const int kWindowLength = kModelSetWindowSize;

@interface ModelSetWindow ()

@property (assign, nonatomic) BOOL hasLoggedResult;
@property (assign, nonatomic) int currentStep;

@end

@implementation ModelSetWindow

- (instancetype)initWithProcess:(Process *)process
{
    self = [super init];
    if (self) {
        self.process = process;
        self.hasfinished = NO;
        self.hasLoggedResult = NO;
        self.currentStep = 0;
    }
    return self;
}

- (NSNumber *)nextPage:(int)end {
    if (end + 1 >= self.process.sequence.count) {
        return 0;
    }
    return self.process.sequence[end + 1];
}

- (void)moveTo:(int)end {
    int start = MAX(0, end - kWindowLength + 1);
    //把用到的加入内存
    for (int i = start; i <= end; i++) {
        [self.process addPage:self.process.sequence[i]];
    }
}

- (void)stop {
    self.process.isRunning = NO;
}

- (int)run {
    //如果新掉进来的页在原来中找不到，则说明此次出现页错误
    if (self.process.set != nil && [self.process.set containsObject:[self nextPage:self.currentStep]] == NO) {
        self.wrongCount++;
//        NSLog(@"进程%d发生页错误，wrongCount = %d", self.process.processID, self.wrongCount);
    }
    
    //把全部的清楚，表示把“不用的删除”，因为接下来会重新对窗口添加一遍
    self.process.set = nil;
    
    //如果当前进程被暂停
    if (self.process.isRunning == NO) {
        return 0;
    }
    //如果当前进程执行完毕
    if (self.currentStep >= self.process.sequence.count) {
        self.hasfinished = YES;
        if (self.hasLoggedResult == NO) {
            NSLog(@"进程%d执行完毕，页错误次数%d，页错误率%f", self.process.processID, self.wrongCount, (float)self.wrongCount / self.process.processPageCount);
            self.hasLoggedResult = YES;
        }
        return 0;
    }
    [self moveTo:self.currentStep];
    self.currentStep++;
//    NSLog(@"currentStep = %d, window count = %d", self.currentStep, (int)self.process.set.count);
    return (int)self.process.set.count;
}

@end
