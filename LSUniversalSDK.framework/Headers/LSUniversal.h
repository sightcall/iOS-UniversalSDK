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
extern NSString *const kParametersMode;
extern NSString *const kParametersHash;
extern NSString *const kParametersAppID;
extern NSString *const kParametersACDProduct;
extern NSString *const kParametersACDLanguage;
extern NSString *const kParametersACDLocation;

extern NSString *const kParametersACDInfo;
extern NSString *const kParametersCalleeID;
extern NSString *const kParametersButtons;
extern NSString *const kParametersSharedURL;
extern NSString *const kParametersVideoOut;
extern NSString *const kParametersUsingVideoOut;
extern NSString *const kParametersVideoFull;
extern NSString *const kParametersVideoSmall;
extern NSString *const kParametersVideoPtrOut;
extern NSString *const kParametersAudioMute;
extern NSString *const kParametersPinCode;
extern NSString *const kParametersInternalToken;
extern NSString *const kParametersTokenLivesight;
extern NSString *const kParametersExternalToken;
extern NSString *const kParametersVideoProfile;
extern NSString *const kParametersUID;
extern NSString *const kParametersDisplayName;
extern NSString *const kParametersSentText;
extern NSString *const kParametersMPID;
extern NSString *const kParametersMPSuffix;
extern NSString *const kParametersMPHash;
extern NSString *const kParametersTimeout;

@protocol LSMobile2MobileNotification <NSObject>

/**
 *  TRUE if the module has credentials. FALSE otherwise.
 *  Having credentials is not a guarantee of having any usecases.
 */
@property(nonatomic, readonly, getter=isRegistered) BOOL registered;

/**
 *  If this is different from nil, notifications can be sent. This array can be empty. The UsecaseID can be found in each entry of
 *  this array.
 */
@property(nonatomic, readonly) NSArray *usecases;

/**
 *	 The application notification token. It must be set for the registration to work.
 */
@property(nonatomic) NSString *notificationToken;

/**
 *  Sign-in. Mandatory to fetch the usecases.
 *
 *  @param block The HTTP status returned by the request, or 0 if the request wasn't sent.
 */
- (void)signInAndNotify:(void (^)(NSInteger))block;

/**
 *  Fetches the usecase for the logged in user.
 *
 *  @param block This block sets the usecases.
 */
- (void)fetchUsecasesAndNotify:(void (^)(NSInteger, NSArray *))block;

/**
 *  Sends a notification to a guest. This notification will be sent as an SMS. Notification will only works if the
 *
 *  @param usecaseID   The usecase ID.
 *  @param phoneNumber The Guest Phone number. Either in international format (ex +33601234567) or national format & country code.
 *  @param cc          Country code of the number, if not in international format.
 *  @param block  The notification block
 */
- (void)sendNotificationForUsecase:(NSInteger)usecaseID toPhone:(NSString *)phoneNumber andContryCode:(NSString *)cc andNotify:(void (^)(NSInteger))block;

/**
 *  Sends a notification to a guest. This notification will be sent as an e-mail
 *
 *  @param usecaseID The usecase ID.
 *  @param email     The email to send the notification to.
 *  @param block  The notification block
 */
- (void)sendNotificationForUsecase:(NSInteger)usecaseID toEmail:(NSString *)email andNotify:(void (^)(NSInteger))block;

@end


/**
 *  Describes the state of the current connection.
 */
typedef NS_ENUM(NSInteger, lsConnectionStatus_t) {
	/**
	 *  The LSUniversalSDK is not doing anything. This is the state it should go to after disconnecting.
	 */
	lsConnectionStatus_idle,
	/**
	 *  The LSUniversalSDK is connected as agent.
	 */
	lsConnectionStatus_agentConnected,
	/**
	 *  The LSUniversalSDK is refreshing the agent data before a call or because of a registration.
	 */
	lsConnectionStatus_agentConnecting,
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
	/*
	 *  The connection was lost.
	 */
	lsConnectionStatus_networkLoss,	
};

/**
 *  When a connection error occurs, you are notified of it through connectionError:
 */
typedef NS_ENUM(NSInteger, lsConnectionError_t) {
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
typedef NS_ENUM(NSInteger, lsCallEnd_t) {
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

typedef NS_ENUM(NSInteger, lsCameraUsedOnStart_t) {
	lsCameraUsedOnStart_front,
	lsCameraUsedOnStart_rear,
	lsCameraUsedOnStart_none,
};

/**
 *  An object of this type describes the data needed to display the survey at call's end.
 *  If displayPopup, ask the user if she wants to participate in a survey. Otherwise, just use url to open a webbrowser
 */
@protocol LSSurveyInfos <NSObject>
/**
 *  The URL of the survey. If displayPopup, ask the user if she accepts to participate in a survey. Otherwise, just open it in
 *  a webbrowser (e.g. using UIApplication openURL: )
 */
@property(nonatomic, readonly) NSString *url;
/**
 *  If YES, the user is to be presented with an alert view to confirm wether or not they want to go to the survey.
 *  If NO, just open url
 */
@property(nonatomic, readonly) BOOL displayPopup;
/**
 *  If displayPopup, this is the popup title.
 */
@property(nonatomic, readonly) NSString *popupLabel;
/**
 *  If displayPopup, this is the popup text.
 */
@property(nonatomic, readonly) NSString *buttonLabel;

@end

typedef struct {
	NSInteger position;
	NSInteger length;
} LSACDProgress_s;

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

/**
 *  Describe the position in the queue (and the length of it) if the usecase is using ACD. Eventually, acdAcceptedEvent: is called.
 *
 *  @param queue The position and length of the queue.
 *  @sa acdAcceptedEvent:
 */
- (void)acdProgressEvent:(LSACDProgress_s)queue;

/**
 *  The user was accepted by an agent using the ACD system. The call begins soon after (i.e. connectionEvent: will soon be called with lsConnectionStatus_calling).
 *
 *  @param agentUID The UID of the agent that accepted the call.
 *  @sa acdProgressEvent:
 */
- (void)acdAcceptedEvent:(NSString *)agentUID;

- (void)connectionParameters:(NSDictionary *)parameters;
- (void)cameraUsedOnStart:(lsCameraUsedOnStart_t)isFront;

/**
 *  Should this method be called, it will be at the end of a call. It contains all informations needed to open the survey webpage defined in the administration portal.
 *
 *  @param infos The informations needed to open the survey page and optionaly open a popup to prompt the user before that.
 */
- (void)callSurvey:(id<LSSurveyInfos>)infos;

/**
 *  The mobile2mobile object can be used to send notification to other users.
 */
- (void)notificationUsecaseAvailable;
@end

/**
 *  The customization delegate allows to change a few things in the LSUniversal callViewController's view.
 *  The button customization allows for changing the buttons look and content. Their size is computed by the SDK. The content is dependant on the button's state. See each buttons callback for details.
 */
@protocol LSCustomizationDelegate <NSObject>
@optional

/**
 * @param b The LSButton describing the mute status of the app.
 */
- (void)customizeMuteToggle:(UIButton *)b;

/**
 *  Tapping this button stops/starts the video out stream capture.
 *  b.state == UIControlStateNormal - The video is being sent
 *  b.state == UIControlStateSelected - The video is not being sent
 *  @param b
 */
- (void)customizeCameraToggle:(UIButton *)b;

/**
 * Tapping this button changes the video out source.
 *  b.state == UIControlStateNormal - Using the front camera
 *  b.state == UIControlStateSelected - Using another camera
 *
 *  @param b
 */
- (void)customizeCameraSource:(UIButton *)b;

/**
 *  Tapping that button changes the audio route used to play/record the audio, if possible.
 *  b.state == UIControlStateNormal - Using the loudspeaker
 *  b.state == UIControlStateSelected - Not using the loudspeaker
 *  This button changes automatically when connecting a headset with a mic.
 *
 *  @param b
 */
- (void)customizeSpeakerRoute:(UIButton *)b;

/**
 *  This button pauses/resumes the video out stream capture.
 *  b.state == UIControlStateNormal - VideoOut is playing
 *  b.state == UIControlStateSelected - VideoOut is paused
 *
 *  @param b
 */
- (void)customizeVideoPauseToggle:(UIButton *)b;

/**
 *  Tapping that button will display the media selector popup.
 *
 *  @param b
 */
- (void)customizeShareMedia:(UIButton *)b;

/**
 *  Tapping this button starts/stops the torch, when using the back camera. It does nothing if using the front camera.
 *  b.state == UIControlStateNormal - The torch is not on
 *  b.state == UIControlStateSelected - The torch is on
 *
 *  @param b
 */
- (void)customizeTorchToggle:(UIButton *)b;

/**
 *  Tapping this button will erase any drawings (on share, video out or player)
 *  @param b
 */
- (void)customizeEraseDrawings:(UIButton *)b;
/**
 *  Tapping this button will end the ongoing call.
 *
 *  @param b
 */
- (void)customizeHangup:(UIButton *)b;
/**
 *  Tapping this button will stop an ongoing share out.
 *
 *  @param b
 */
- (void)customizeStopShare:(UIButton *)b;

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
@property(nonatomic, readonly) UIViewController *callViewController;

/**
 *  The delegate that is notified of connection events and call ends.
 */
@property(nonatomic) id<LSUniversalDelegate> delegate;

/**
 *  If the delegate conforms to LSUniversalLogDelegate, this property is set automatically
 */
@property(nonatomic) id<LSUniversalLogDelegate> logDelegate;

/**
 *  This delegate is called upon when the call menu is resized.
 */
@property(nonatomic) NSObject<LSCustomizationDelegate> *customizationDelegate;

/**
 *  The current connection status. When the connection goes from connecting to active, the call is created.
 */
@property(nonatomic, readonly) lsConnectionStatus_t status;

/**
 *  This object is responsible for sending the notifications to a remote contact (e.g. in the Agent-to-guest case). It needs the Apple Notification token to work (see APNS).
 *	 Make sure the app can send a notification before trying to send one (check the LSMobile2MobileNotification protocol for more info).
 */
@property(nonatomic, readonly) NSObject<LSMobile2MobileNotification> *mobile2mobile;
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
