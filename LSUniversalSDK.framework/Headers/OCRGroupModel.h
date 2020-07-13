//
//  OCRGroupModel.h
//  LSUniversalSDK
//
//  Created by Ben Maad on 03/03/2020.
//  Copyright © 2020 SightCall. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RegionOfInterest.h"

@interface OCRGroupModel : NSObject

@property (nonatomic) NSString *name;
@property (nonatomic) BOOL primary;
@property (nonatomic) NSArray<RegionOfInterest *> *fields;
@property (nonatomic) CGRect regionOfInterest;

- (instancetype)initWithDescription:(NSDictionary *)d;

@end
