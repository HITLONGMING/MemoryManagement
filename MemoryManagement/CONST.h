//
//  CONST.h
//  MemoryManagement
//
//  Created by Chen Yizhuo on 15/5/30.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#ifndef MemoryManagement_CONST_h
#define MemoryManagement_CONST_h

//bool 类型
typedef int BOOL;
#define YES 1
#define NO  0

//数组最大长度
#define MAX_LENGTH  1500

//本次试验中以int表示一个页
typedef int ELEM_TYPE;

//获取较大值
#define	MAX(a,b) (((a)>(b))?(a):(b))

/**
 *  内存页面总数
 */
#define kMemoryPageCount    1000
/**
 *  进程页面种类数
 */
#define kProcessPageCount   500
/**
 *  工作集窗口大小
 */
#define kModelSetWindowSize 900

#endif
