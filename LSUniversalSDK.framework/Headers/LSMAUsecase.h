//
//  LSMobile2MobileUsecase.h
//  LSUniversalSDK
//
//  Created by Charles Thierry on 23/03/17.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol LSMAUsecase <NSObject>

@property (nonatomic, readonly, nullable) NSString *name;

@end

@interface LSMAACDUsecase : NSObject <LSMAUsecase>

- (nullable instancetype)init NS_UNAVAILABLE;

@end

@interface LSMAGuestUsecase: NSObject <LSMAUsecase>

- (nullable instancetype)init NS_UNAVAILABLE;

@end

@interface LSMAAgentUsecase: NSObject<LSMAUsecase>

- (nullable instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
