//
//  LiveOCRAttributes.h
//  LSUniversalSDK
//
//  Created by Ben Maad on 18/06/2020.
//  Copyright © 2020 SightCall. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RegionOfInterest.h"
#import "OCRGroupModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface LiveOCRAttributes : NSObject

@property (nonatomic) int agentCount;
@property (nonatomic) NSString *createdAt;
@property (nonatomic) int groupsCount;
@property (nonatomic) NSString *name;
@property (nonatomic) NSString *objectName;
@property (nonatomic) CGFloat pictureRatio;
@property (nonatomic) NSString *updatedAt;
@property (nonatomic) int fieldsCount;
@property (nonatomic) NSMutableArray<RegionOfInterest *> *fields;
@property (nonatomic) CGRect regionOfInterest;
@property (nonatomic) NSArray<OCRGroupModel *> *groups;

- (instancetype)initWithDescription:(NSDictionary *)d;

@end

NS_ASSUME_NONNULL_END
