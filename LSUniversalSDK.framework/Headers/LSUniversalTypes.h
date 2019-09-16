//
//  LSUniversalType.h
//  LSUniversalSDK
//

#import <LSUniversalSDK/LSUniversalSDK.h>

NS_ASSUME_NONNULL_BEGIN

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
extern NSString *const kParametersSuffix;
extern NSString *const kParametersDisplayName;
extern NSString *const kParametersSentText;
extern NSString *const kParametersMPID;
extern NSString *const kParametersMPHash;
extern NSString *const kParametersTimeout;

typedef NS_ENUM(NSInteger, LSConnectionStatus_t) {
    LSConnectionStatus_idle,
    /**
     * The LSUniversalSDK is fetching all informations needed before connecting
     */
    LSConnectionStatus_fetching,
    /**
     *  The LSUniversalSDK is connecting.
     */
    LSConnectionStatus_connecting,
    /**
     *  The LSUniversalSDK is connected. Depending on the authentication process, a call is being created.
     */
    LSConnectionStatus_active,
    /**
     *  A call was started.
     */
    LSConnectionStatus_calling,
    /**
     *  A call is active.
     */
    LSConnectionStatus_callActive,
    /**
     *  The LSUniversalSDK is disconnecting.
     */
    LSConnectionStatus_disconnecting,
    /*
     *  The connection was lost.
     */
    LSConnectionStatus_networkLoss
};

/**
 *  When a connection error occurs, you are notified of it through connectionError:
 */
typedef NS_ENUM(NSInteger, LSConnectionError_t) {
	/**
	 * The error was a network one
	 */
	LSConnectionError_networkError,
	/**
	 *  The credentials given in the dictionary (or string) were incorrect.
	 */
	LSConnectionError_badCredentials,
	/**
	 *  An unknown error occured.
	 */
	LSConnectionError_unknown
} ;

/**
 *  The call ended, the LSUniversalSDK is disconnecting.
 */
typedef NS_ENUM(NSInteger, LSCallEnd_t) {
    /**
	 *  The call ended prematuraly
	 */
	LSCallEnd_unexpected,
	/**
	 *  The call was ended by the remote client
	 */
	LSCallEnd_remote,
	/**
	 *  the call was ended on your end.
	 */
	LSCallEnd_local,
    /**
     *
     */
    LSCallEnd_eulaRefused
} ;

/**
 * This structure describes the condition of the call end
 */
typedef struct {
    /**
     * Reason the call ended
     */
	LSCallEnd_t callEnd;
    /**
     * Duration of the call
     */
	NSTimeInterval callLength;
} LSCallReport_s;


/**
 * ACD Queue status.
 */
typedef struct {
	/**
	 * Position in the queue.
	 */
	NSInteger position;
	/**
	 * Total length of the queue.
	 */
	NSInteger length;
} LSACDProgress_s;


/**
 * ACD Status.
 */
typedef NS_ENUM(NSInteger, LSACDStatus_t) {
	/**
	 */
	LSACDStatus_invalid = -1,
	/**
	 * Waiting for an agent to pick up.
	 */
	LSACDStatus_ongoing,
	/**
	 * The service is closed.
	 */
	LSACDStatus_serviceClosed,
	/**
	 * The service is unavailable.
	 */
	LSACDStatus_serviceUnavailable,
	/**
	 * There is no agent available.
	 */
	LSACDStatus_agentUnavailable
} ;


/**
 * The ACD status structure. `status` and `progress` are independant: there can be an ETA without any information about the queue, and you can be in a queue without any information about an ETA.
 */
typedef struct {
	/**
	 * Current status of your ACD request.
	 */
	LSACDStatus_t status;
	/**
	 * Current info about your position in the queue.
	 */
	LSACDProgress_s progress;
	/**
	 * ETA for an agent to accept your call.
	 */
	NSInteger waitingTime;
} LSACDQueue_s;


NS_ASSUME_NONNULL_END
