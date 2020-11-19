//
//  LiveARModel.h
//  LSUniversalSDK
//
//  Created by Ben Maad on 09/06/2020.
//  Copyright © 2020 SightCall. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LSUniversalSDK/LiveARAttributeModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface LiveARModel : NSObject

@property (nonatomic) NSString *idField;
@property (nonatomic) NSString *type;
@property (nonatomic) LiveARAttributeModel *attributresField;

- (instancetype)initWithDictionary:(NSDictionary*)dictionary;

@end

NS_ASSUME_NONNULL_END
