//
//  LSDisplayNameDescription.h
//  LSUniversalSDK
//
//  Created by Ben Maad on 29/10/2020.
//  Copyright © 2020 SightCall. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol LSDisplayNameDescriptionProtocol <NSObject>

/**
 *  Title of the display Name popup
 */
@property (readonly, nonatomic, nullable) NSString *title;

/**
 *  display name subtitle message
 */
@property (readonly, nonatomic, nullable) NSString *subtitle;

/**
 *  Title of the `Agree` button
 */
@property (readonly, nonatomic, nullable) NSString *agreeButtonTitle;

/**
 *  Title of the `Skip` button
 */
@property (readonly, nonatomic, nullable) NSString *skipButtonTitle;

/**
 *  default display Name text
 */
@property (readonly, nonatomic, nullable) NSString *displayNameText;


/**
*  is option display name mode
*/
@property (readonly, nonatomic) BOOL isOptional;

/**
 *  Block to trigger when the user set or skip with display name.
 */
@property (readonly, nonatomic, nullable) void (^displayName)(BOOL, NSString* _Nullable);

@end
