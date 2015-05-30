//
//  Process.h
//  VVM
//
//  Created by Chen Yizhuo on 15/5/28.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CONST.h"

@interface Process : NSObject

/**
 *  进程id
 */
@property (assign, nonatomic) int processID;
/**
 *  进程页面数
 */
@property (assign, nonatomic) int processPageCount;
/**
 *  进程工作集合
 */
@property (strong, nonatomic) NSMutableSet *set;
/**
 *  是否正在执行
 */
@property (assign, nonatomic) BOOL isRunning;
/**
 *  内存访问顺序
 */
@property (strong, nonatomic) NSMutableArray *sequence;

- (id)initWithProcessID:(int)processID processPageCount:(int)count;
/**
 *  将该进程用到的新的页调入内存
 */
- (void)addPage:(NSNumber *)pageNumber;

@end
