//
//  Process.m
//  VVM
//
//  Created by Chen Yizhuo on 15/5/28.
//  Copyright (c) 2015年 Chen Yizhuo. All rights reserved.
//

#import "Process.h"

@implementation Process

- (instancetype)initWithProcessID:(int)processID processPageCount:(int)count
{
    self = [super init];
    if (self) {
        self.processID = processID;
        self.processPageCount = count;
        [self genSequence];
        self.isRunning = YES;
    }
    return self;
}

- (void)genSequence {
    self.sequence = [NSMutableArray arrayWithCapacity:kMemoryPageCount];
    for (int i = 0; i < self.processPageCount; i++) {
        [self.sequence addObject:[NSNumber numberWithInt:(arc4random() % kProcessPageCount + 1)]];
    }
//    NSLog(@"process id = %d, sequence =", self.processID);
//    for (int i = 0; i < self.sequence.count; i++) {
//        printf("%d", [self.sequence[i] intValue]);
//    }
//    printf("\n");
}

- (void)addPage:(NSNumber *)pageNumber {
    if (self.set == nil) {
        self.set = [NSMutableSet set];
    }
    
    [self.set addObject:pageNumber];
    
}

@end
