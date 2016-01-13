//
//  Model.h
//  RTCC Generic
//
//  Created by Charles Thierry on 19/09/14.
//  Copyright (c) 2014 Charles Thierry. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LSUniversalSDK/LSUniversalSDK.h>


/** @name Connection parameters ID keys.*/
extern NSString * const kParametersMode;
extern NSString * const kParametersHash;
extern NSString * const kParametersAppID;
extern NSString * const kParametersACDMask;
extern NSString * const kParametersACDValue;
extern NSString * const kParametersACDInfo;
extern NSString * const kParametersCalleeID;
extern NSString * const kParametersButtons;
extern NSString * const kParametersSharedURL;
extern NSString * const kParametersVideoOut;
extern NSString * const kParametersVideoFull;
extern NSString * const kParametersVideoSmall;
extern NSString * const kParametersVideoPtrOut;
extern NSString * const kParametersAudioMute;
extern NSString * const kParametersPinCode;
extern NSString * const kParametersInternalToken;
extern NSString * const kParametersTokenLivesight;
extern NSString * const kParametersExternalToken;
extern NSString * const kParametersVideoProfile;
extern NSString * const kParametersUID;
extern NSString * const kParametersDisplayName;
extern NSString * const kParametersSentText;
extern NSString * const kParametersMPID;
extern NSString * const kParametersMPSuffix;
extern NSString * const kParametersMPHash;
extern NSString * const kParametersTimeout;


/**
 *  Describes the state of the current connection.
 */
typedef NS_ENUM(NSInteger, lsConnectionStatus_t){
	/**
	 *  The LSUniversalSDK is not doing anything. This is the state it should go to after disconnecting.
	 */
	lsConnectionStatus_idle,
	/**
	 *  The LSUniversalSDK is connecting.
	 */
	lsConnectionStatus_connecting,
	/**
	 *  The LSUniversalSDK is connected. Depending on the authentication process, a call is being created.
	 */
	lsConnectionStatus_active,
	/**
	 *  A call was started.
	 */
	lsConnectionStatus_calling,
	/**
	 *	A call is active.
	 */
	lsConnectionStatus_callActive,
	/**
	 *	 The LSUniversalSDK is disconnecting.
	 */
	lsConnectionStatus_disconnecting,
};

/**
 *  When a connection error occurs, you are notified of it through connectionError:
 */
typedef NS_ENUM(NSInteger, lsConnectionError_t){
	/**
	 * The error was a network one
	 */
	lsConnectionError_networkError,
	/**
	 *  The credentials given in the dictionary (or string) were incorrect.
	 */
	lsConnectionError_badCredentials,
	/**
	 *  An unknown error occured.
	 */
	lsConnectionError_unknown,
};

/**
 *  The call ended, the LSUniversalSDK is disconnecting.
 */
typedef NS_ENUM(NSInteger, lsCallEnd_t){
	/**
	 *  The call ended prematuraly
	 */
	lsCallEnd_unexpected,
	/**
	 *  The call was ended by the remote client
	 */
	lsCallEnd_remote,
	/**
	 *  the call was ended on your end.
	 */
	lsCallEnd_local,
};

typedef struct {
	lsCallEnd_t callEnd;
	NSTimeInterval callLength;
} lsCallReport_s;


typedef NS_ENUM(NSInteger, cameraUsedOnStart_t) {
	camera_front,
	camera_rear,
	camera_none,
};

@interface LSSurveyInfos: NSObject
@property (nonatomic, readonly)NSString *url;

@property (nonatomic, readonly)BOOL displayPopup;
@property (nonatomic, readonly)NSString *popupLabel;
@property (nonatomic, readonly)NSString *buttonLabel;

@end

typedef struct {
	NSInteger position;
	NSInteger length;
}LSACDProgress_s;

@protocol LSUniversalLogDelegate <NSObject>

- (void)logLevel:(NSInteger)level logModule:(NSInteger)module fromMethod:(NSString *)from message:(NSString *)message, ... NS_REQUIRES_NIL_TERMINATION;

@end

/**
 *  The protocol the LSUniversalDelegate is to follow. Make no assumption regarding the thread that is used to trigger those messages.
 */
@protocol LSUniversalDelegate <NSObject>

/**
 *  A connection event occured. You were not connected, the SDK goes to idle.
 *
 *  @param status The new connection state.
 */
- (void)connectionEvent:(lsConnectionStatus_t)status;

/**
 *  An error occured. The SDK is most likely now disconnecting.
 *
 *  @param error The error that occured.
 */
- (void)connectionError:(lsConnectionError_t)error;

/**
 *  The call ended. You should probably dismiss the Call ViewController here.
 *
 *  @param callEnd The reason the call ended.
 */
- (void)callReport:(lsCallReport_s)callEnd;

@optional
- (void)acdProgressEvent:(LSACDProgress_s)queue;
- (void)acdAcceptedEvent:(NSString *)agentUID;
- (void)connectionParameters:(NSDictionary *)parameters;
- (void)cameraUsedOnStart:(cameraUsedOnStart_t)isFront;
- (void)callSurvey:(LSSurveyInfos *)infos;
@end

/**
 The LSUniversal object is your point of entry to the connection and call control. The Callflow is simplified to the max:
 
 - Start the connection using parameters;
 - When the connection goes active, the call is created;
 - When the call ends, you are disconnected.
 
 Starting can be done through two methods startWithDictionary: or startWithString: . The latter makes use of the former.

 The call internals are controlled through the UI (turning off the camera, muting the mic. etc). As said before, the call is started upon connection.

 You are notified of the connection state through the delegate property. You can check the status of the connection anytime by calling currentConnectionStatus.
 
 You can call abort during connection or during a call. It will either directly disconnect the LSUniversalSDK or hangup the call, which will in turn disconnect the LSUniversalSDK. On your end, calls can be ended either trough this abort method or the hangup button in the call view UI. You are notified of call ends by the [LSUniversalDelegate callReport:].
 */
@interface LSUniversal : NSObject

/**
 *  A UIViewController that is used by the SDK to display the video in and out, as well as the buttons used for controlling the call. Display it when the currentConnectionStatus goes to active. Remove it on call end.
 *  @sa [LSUniversalDelegate connectionEvent:]
 *  @sa [LSUniversalDelegate callReport:]
 */
@property (nonatomic, readonly) UIViewController *callViewController;

/**
 *  The delegate that is notified of connection events and call ends.
 */
@property (nonatomic) id<LSUniversalDelegate> delegate;

/**
 *  If the delegate conforms to LSUniversalLogDelegate, this property is set automatically
 */
@property (nonatomic) id<LSUniversalLogDelegate> logDelegate;

/**
 *  The current connection status. When the connection goes from connecting to active, the call is created.
 */
@property (nonatomic, readonly) lsConnectionStatus_t status;

/**
 *  Connects the LSUniversalSDK to SightCall's cloud. The dictionary is a <String *: String *> dictionary, with the key being URL Scheme parameters and the values their value.
 *
 *  @param dictionary The key/value used to connect
 *
 *  @return True if the dictionary allows for connection. If false, something is missing from the dictionary.
 *  @sa startWithString:
 *  @sa abort
 */
- (BOOL)startWithDictionary:(NSDictionary *)dictionary;

/**
 *  Connects the LSUniversalSDK to SightCall's cloud. From this string is made a dictionary used in startWithDictionary:
 *
 *  @param param The string used to create the dictionary. It can be an URL string such as the one used in the Universal App (i.e. "sightcall://?mode=value&..."), or simply "mode=value&...". `?`, `=` and `&` are used as separators.
 *
 *  @return True if the string allows for connection. If false, something is missing from the library
 *  @sa startWithDictionary:
 *  @sa abort
 */
- (BOOL)startWithString:(NSString *)param;

/**
 *  Disconnects the LSUniversalSDK from the cloud. Hangup the call if any.
 *  @sa startWithString:
 *  @sa startWithDictionary:
 */
- (void)abort;

@end
