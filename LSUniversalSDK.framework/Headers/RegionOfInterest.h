//
//  RegionOfInterest.h
//  LSLiveOCR
//
//  Created by Charles Thierry on 07/01/2020.
//  Copyright © 2020 Charles Thierry. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RegionOfInterest : NSObject

@property (nonatomic) NSString *name;
@property (nonatomic) NSString *identifier;
@property (nonatomic) CGRect box;
@property (nonatomic) BOOL mandatory;
@property (nonatomic) BOOL primaryKey;
@property (nonatomic) NSString *validationPattern;
@property (nonatomic) NSString *replacementExpression;
@property (nonatomic) NSString *groupName;

- (instancetype)initWithDescription:(NSDictionary *)d andgroupName:(NSString *) groupName;
@end

NS_ASSUME_NONNULL_END
