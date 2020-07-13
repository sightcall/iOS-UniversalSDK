//
//  LiveARAttributeModel.h
//  LSUniversalSDK
//
//  Created by Ben Maad on 09/06/2020.
//  Copyright © 2020 SightCall. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LiveARAttributeModel : NSObject

@property (nonatomic) NSString *name;
@property (nonatomic) NSDictionary *configuration;
@property (nonatomic) int sessionTimeOut;
@property (nonatomic) int objectsCount;
@property (nonatomic) NSString *updatedAt;

- (instancetype)initWithDictionary:(NSDictionary*)dictionary;

@end

NS_ASSUME_NONNULL_END
