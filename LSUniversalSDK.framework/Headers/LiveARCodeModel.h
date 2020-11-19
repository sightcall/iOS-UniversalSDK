//
//  LiveARCodeModel.h
//  LSUniversalSDK
//
//  Created by Ben Maad on 09/06/2020.
//  Copyright © 2020 SightCall. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LSUniversalSDK/LiveARModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface LiveARCodeModel : NSObject

@property (nonatomic) NSArray<LiveARModel *> *liveARModel;

- (instancetype)initWithDictionary:(NSDictionary*)dictionary;

@end

NS_ASSUME_NONNULL_END
