

# iOS SDK

<!-- MarkdownTOC levels="2,3,4" autolink="true" -->
- [Introduction](#introduction)
    - [SightCall SDK](#sightcall-sdk)
    - [Dependencies](#dependencies)
- [Installation](#installation)
    - [Installation with CocoaPods](#installation-with-cocoapods)
    - [Update from older versions](#update-from-older-versions)
    - [Direct Framework import](#direct-import)
- [Usage](#usage)
    - [Permissions](#permissions)
    - [Entitlements](#entitlements)
    - [Instantiation](#instantiation)
    - [Consent UI](#consent-ui)
    - [Survey](#survey)
    - [Logging](#logging)
    - [Localization](#localization)
- [Advanced](#advanced)
    - [Customization](#customization)
    - [ACD information](#acd-information)
    - [Callflows](#callflows)
    - [Agent](#agent)
        - [Onboarding](#onboarding)
        - [Registration](#registration)
        - [Notifications](#notifications)
        - [Unregister](#unregister)
        - [Identity](#identity)
        - [Usecases](#usecases)
        - [Inviting a Guest](#inviting-a-guest)
        - [Invitation history](#invitation-history)
        - [Save picture](#save-picture)

<!-- /MarkdownTOC -->

## Introduction

### SightCall SDK

This SDK is dedicated to Sightcall customers. It can be integrated in an existing app flow and brings a seamless access to the Sightcall experience. 
It is packaged in an XCFramework easily integrated with CocoaPods. It is compiled with bitcode support and can be used with a Swift code base.
It supports nine languages: Bulgarian, German, English (default language), Spanish, French, Italian, Japanese and Portugese.


### Dependencies

This Framework ships with its own dependencies:

|        Name         | Version | 
| :-----------------  | :-----  |
| AFNetworking        |  3.2.1  |
| MMWormhole          |  2.0.0  |
| libPhoneNumber      |  0.9.13 |
| FormatterKit        |  1.9.0  |
| MaterialComponents        |  119.5.0  |

## Installation

### Installation with CocoaPods

[CocoaPods](https://cocoapods.org/) is the easiest way to get started (if you're new to CocoaPods, check out their [getting started documentation](https://guides.cocoapods.org/using/getting-started.html).)

To integrate the Sightcall sdk into your Xcode project using CocoaPods, specify it in your `Podfile`:

```shell
    pod 'LSUniversalSDK', :git => 'https://github.com/sightcall/iOS-UniversalSDK.git'
```

### Update from older versions

If the sdk has been directly imported in your application, from our Github repository, we highly recommend that you use CocoaPods:

- Remove LSUniversalSDK framework
- Then follow the step described in [Installation with CocoaPods](#installation-with-cocoapods)

>Note: The API contract remains unchanged. 

### Direct Framework import

Direct import steps are described in [Direct Import](#direct-import)


## Usage

### Permissions

The Framework requires some permissions to be used and must be set in the App's Info.plist.

* **NSLocationWhenInUseUsageDescription**

This permission is used in response to an Agent's request.  The sdk will display a pop-up to prompt the user about sharing their location, in addition to the System's "regular" pop-up.

* **NSCameraUsageDescription**

This permission is required for starting the video capture. If never asked, the system pop-up will appear on call start.

* **NSMicrophoneUsageDescription**

This permission is required for starting the audio capture. If never asked, the system pop-up will appear on call start.

* **NSPhotoLibraryUsageDescription**

This permission is required for sharing images from the gallery.

### Entitlements

#### Universal link

In order to setup universal link, some domains should be added to the **Associated Domains** section (in Signing and  Capabilities of your target). 
Common domains are usually: 

* **applinks:guest.sightcall.com**
* **applinks:guest-ppr.sightcall.com**

> Note: Depending on your use case, you may need specific domains. Don't forget to ask your SightCall contact for them.

#### Deeplink

When user comes from the guest webpage, a deeplink can be displayed to open your application. So, at least, one scheme should be added to the **URL Types** section (in Info section of your target). 
Common scheme is: **sightcall**

> Note: Depending on your use case, you may need specific schemes. Don't forget to ask your SightCall contact for them.

#### Background Modes

If you need to be able to continue the call on background, you should setup the associated section (in Signing and  Capabilities of your target, then **Background Modes**):

* **Audio, AirPlay, and Picture in Picture**
* **Voice over IP**
* **Remote notifications**


### Instantiation

First, import `LSUniversalSDK` and create a `LSUniversal` variable:

```swift
func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
    guard let _ = (scene as? UIWindowScene) else { return }
    self.lsUniversal = LSUniversal()
    /**
    **/
}
```

 Then call `start:` providing the start URL. This, usually, takes place in SceneDelegate:

```swift
func scene(_ scene: UIScene, continue userActivity: NSUserActivity) {
    guard let url = userActivity.webpageURL else { return }
    lsUniversal?.start(with: url.absoluteString)
}
```

The SDK offers a delegate with three callbacks. Those inform the application that the connection status changed, that a call ended and that an error occurred. It can be set on `self.lsUniversal.delegate`.

This is also where the `self.lsUniversal.callViewController` of the sdk should be added on your stack if the call is currently active. It will display the UI of the call. When the latter is finished, just dismiss the viewController:

```swift
extension SceneDelegate: LSUniversalDelegate {
    func connectionEvent(_ status: lsConnectionStatus_t) {
        DispatchQueue.main.async {
            switch status {
            case .callActive:
            /**
                Add self.lsUniversal.callViewController to your view hierarchy
            **/
            case .disconnecting:
            /**
                Remove self.lsUniversal.callViewController from your view hierarchy
            **/
            default:
                break
            }
        }
    }

    func connectionError(_ error: lsConnectionError_t) {
        DispatchQueue.main.async {
            switch error {
            default:
                break
            }
        }
    }

    func callReport(_ callEnd: LSCallReport) {
    }


```

>Note: The callbacks may not operate on the main thread.

Please see the [Callflow section](#callflows) below for an overview of the callbacks triggered.

### Display Name

Sometime, the guest is prompted for entering his/her name. The delegate method is `showDisplayNameAlert`:

```swift
    func showDisplayNameAlert(_ alertController: UIAlertController?) {
        guard let alertController = alertController else { return }
        /**
            Present the alertController, here
        **/
    }
```
### Consent UI

Depending on your usecase configuration, consent may be requested from the user. This will be triggered by the sdk on  `displayConsentWithDescription:` delegate method.

This method's parameters contains all information about the consent view that should be displayed and a block to trigger with a boolean:

```swift
    func displayConsent(with description: LSConsentDescription?) {
        let controller = UIAlertController(title: description?.title, message: description?.message, preferredStyle: .alert)
        controller.addAction(UIAlertAction(title: description?.cancelLabel, style: .cancel, handler: { _ in
            description?.consent?(false)
        }))
        controller.addAction(UIAlertAction(title: description?.eulaURL, style: .default, handler: { _ in
            guard let urlString = description?.eulaURL,
                let url = URL(string: urlString)
            else { return }
            /**
                Show the content of the url page
            **/
        }))
        controller.addAction(UIAlertAction(title: description?.agreeLabel, style: .default, handler: { _ in
            description?.consent?(true)
        }))
        /**
            Display the controller in your current view hierarchy
        **/
    }

```

### ACD Information

ACD information are provided through two optional delegation methods of the `LSUniversalDelegate`.

```
func acdStatusUpdate(_ update: LSACDQueue)
func acdAcceptedEvent(_ agentUID: String?)
```

`acdStatusUpdate` is called with information pertaining to the ACD current status. If the `update.status` of the request is `ongoing`, the update will inform you about the position in the queue or an ETA. Otherwise, the request is cancelled or invalid and the `update.status` informs you of the reason (service closed, agent unavailable, etc.)  

`acdAcceptedEvent` is called when an agent accepts the call.  

Note that `acdAcceptedEvent` **may not** be called before the SDK `status` moves to `callActive`.


## Advanced

### Logging

The SDK send logs to any object implementing `LSUniversalLogDelegate` and registered as `LSUniversal.logDelegate`.

The following presents a way to receive and print logs on the debugger console. 

Be aware that: 
* uncontrolled use of `NSLog();` may lead to performance degradation;
* `NSLog();` send logs to the device console (available in Xcode -> Window -> Devices and Simulator and Console.App).


```objc
// An instance of this class will be used as log delegate. 
// You must instantiate your LSUniversal pointer before instantiating this object.

@interface YourLogDelegate: NSObject <LSUniversalLogDelegate>

- (instancetype)initWithUSDK:(LSUniversal *)yourSDKPointer;

@end

@implementation YourLogDelegate

- (instancetype)initWithUSDK:(LSUniversal *)yourSDKPointer
{
    self = [super init];
    yourSDKPointer.logDelegate = self;
    return self;
}

//this delegate method is called when a log line is emitted by the SDK
- (void)logLevel:(NSInteger)level logModule:(NSInteger)module fromMethod:(NSString *)originalSel message:(NSString *)message, ...;
{
    va_list pe;
    va_start(pe, message);
    NSString *sMessage = [[NSString alloc] initWithFormat:message arguments:pe];
    va_end(pe);
    NSLog(@"%@ %@", originalSel, sMessage);
}


@end

```

### Localization

The localized elements are only UI elements displayed during a call. In order for the SDK to display those entries, the App must be localized in those languages.

To change those strings (i.e. change the base language) or support a new language, your app should override their key/value pair in its `Localizable.strings` file.

A list of the overridable elements can be found in the base Localizable.strings file found in this folder.

### Customization

The call controls buttons appearances can be customized through the `localBarCustomizationDelegate` and `remoteBarCustomizationDelegate` properties. Those `LSUniversal` properties let you customize either the Local Bar or the Remote Bar by using the `LSLocalCustomizationDelegate` or `LSRemoteCustomizationDelegate` protocols. 

Each methods of these protocols is optional, allowing for the customization of each buttons individually.

Let's say you want to customize the hangup button:

```objc
//declare the customization object
@interface MyCustomizationDelegate: NSObject <LSLocalCustomizationDelegate>
@end

@implementation MyCustomizationDelegate
@end

//somewhere in your code, after the initialization of mySDKPointer
id <LSCustomizationDelegate>myCustomizationDelegate = [[MyCustomizationDelegate alloc] init];
mySDKPointer.localBarCustomizationDelegate = myCustomizationDelegate;
```

At this point, the SDK will inform you every time a button is resized that you can customize it. You will only receive this message if you implement the related button callback.

For example, to customize the hangup button, one would implement the `customizeHangup:` method of myCustomizationDelegate

```objc
//Somewhere in MyCustomizationDelegate.m

- (void)customizeHangup:(UIButton *)b
{
    b.backgroundColor = [UIColor colorWithRed:0. green:1. blue:0. alpha:0.3];
    [b setImage:[UIImage imageNamed:@"hangup_image"] forState:UIControlStateNormal]; 
    //hangup_image is an image available in your project
}

```

Each button has an image for state. See the USDK documentation to see the meaning of each button state.


**Note:** the callbacks will only be called if the related buttons appear.


### Callflows
The standard callflow is as such:

![Standard iOS Callflow](./connection_callflow.png "iOS Callflow")

<!--

https://www.websequencediagrams.com/
title Call Connection callflow
participant BROWSER
participant APP
participant SDK

BROWSER->APP: URL received through Deeplinking
    APP->SDK: Universal.startWithString:URL
    SDK->SDK: parse

alt Invalid URL scheme
    SDK->APP: connectionError:
else Valid URL scheme
    SDK->APP: connectionEvent: lsConnectionStatus_connecting
    SDK->SDK: connect
    SDK->APP: connectionEvent: lsConnectionStatus_active
    opt ACD Call
        SDK->APP: acdProgressEvent:
        SDK->APP: acdStatusUpdate:
        SDK->APP: acdAcceptedEvent:
    end
    SDK->APP: connectionEvent:lsConnectionStatus_calling
    SDK->SDK: call
    SDK->APP: connectionEvent:lsConnectionStatus_callActive
    Note over APP,SDK:
        The call is now active
        Display the callViewController here
    end note
    SDK->SDK: hangup
    SDK->APP: callReport:
    opt Call survey
        SDK->APP: callSurvey:
    end
    SDK->APP: connectionEvent:lsConnectionStatus_disconnecting
    SDK->SDK: disconnect
    SDK->APP: connectionEvent:lsConnectionStatus_idle
end



!-->

### Survey

If the usecase is configured to display a survey on call end, your `LSUniversalDelegate` will be notified through the `callSurvey:` method. This optional method is called with an object responding to `LSSurveyInfo`.

This parameter will tell you if you need to display a popup (if `infos.displayPopup` is equal to YES) and the text in this popup (`infos.popupLabel` and `infos.popupButton`), and give you the URL to the survey (`infos.url`).

```objc
- (void)callSurvey:(LSSurveyInfos *)infos
{
    if (!infos.displayPopup) {
        //open infos.url in a webbrowser
    } else {
        //ask the user if he wants to participate in a survey
    }
}
```


### Agent

The agent is handled by the Universal SDK `agentHandler` property.

As our backend uses notifications (UserNotifications) to start agent-to-guest calls, you must register an APN key/secret to generate Authentication Tokens in the Administration portal.

#### Onboarding

A registered agent can ask for a new registration link to be sent using `sendRegistrationCodeTo:usingMedia:andExecute:`.  

This will send a registration link via SMS or Email.


#### Registration

To start the registration, call either one of the `registerWith...:andReference:onSignIn:` methods.

e.g. : 

```objc
// the registration URL is from an Universal Link
[yourSDKPointer.agentHandler registerWithURL:<#The registration URL#> 
                                    andReference:<#The reference to be used when sending notification#>
                                    onSignIn:^(LSMARegistrationStatus_t statusCode, RegistrationError_t status){
  if (statusCode == LSMARegistrationStatus_registered) {
    NSLog(@"Registration successful!");
  }
}];
```


In case the app is started with a custom scheme (e.g. the Universal Link starts the webbrowser instead of the App), registration is done by calling `startWithString:` . Note that the reference must be set before calling the `startWithString:` method.

```objc
yourSDKPointer.agentHandler.notificationReference = <#The reference to be used when sending notification#>;
[yourSDKPointer startWithString:url];

```


The register code is provided in the email or SMS sent upon creating the agent or resending a registration link.  

The reference is used by our back-end to send the notifications to the correct App, and must be the same as the one set in the Administration portal. It may be set before registering.

The device/App notification token must be set in the agent before attempting registration (see https://developer.apple.com/documentation/usernotifications/registering_your_app_with_apns)

```objc
[yourSDKPointer.agentHandler setNotificationToken:<#yourAPNSToken#>];
```

Note that in some case, registering may be done by custom-schemed URLs (in case the Universal Link fails.) In this case, please register with the 


```objc
// yourRegistrationURL is yourCustomScheme://mode=register&token=<registrationToken>
yourSDKPointer.agentHandler.notificationReference = <#The reference to be used when sending notification#>;
[yourSDKPointer.startWithString:<#yourRegistrationURL#>];

```

Agents can test if their device is correctly registered by using the agentHandler's `sendTestNotification:` method. An Apple Notification will be received by the App some time after.

This notification is handled by the SDK's `canHandleNotification:`/`handleNotification:` methods (as explained [below](#notifications).) 

The test notification will trigger the SDK delegate's `testNotificationReceivedTitle:andBody:` method, allowing to display a local notification as the App sees fit.  

Agent credentials are kept within the App. Upon instantiation, a valid agent triggers the `connectionEvent:` callback with a `lsConnectionStatus_agentConnected` parameter. 


#### Notifications

Apple Notifications are used to notify an agent of a few things:
- A guest is ready to be called;
- A test notification was sent (using `sendTestNotification:` or the Administration portal);
- The agent's registration was revoked (e.g. the agent's account was registered on another device or the Revoke button was pressed in the Administration portal.)

To check if the notification is supported by the Universal SDK, call `LSUniversal canHandleNotification:` with the userInfo NSDictionary provided by `application:didReceiveRemoteNotification:...`.
If the method returns `YES`, call `LSUniversal handleNotification:` with the same NSDictionary.

e.g.

```objc
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    if (yourSDKPointer.agentHandler != nil &&
        yourSDKPointer.agentHandler.identity == nil) {
        [yourSDKPointer.agentHandler fetchIdentity:^(BOOL success) {
            if (!success) {
                return;
            }
            // call notification
            [self handleNotification:userInfo fetchCompletionHandler:completionHandler];
        }];
    } else {
        [self handleNotification:userInfo fetchCompletionHandler:completionHandler];
    }
}

-(void) handleNotification:(NSDictionary *) userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    NSString *notif = [NSString stringWithFormat:@"%@", userInfo ];
    if ([yourSDKPointer.universal canHandleNotification:userInfo])
    {
        
        [yourSDKPointer.universal handleNotification:userInfo];
    }
    if (completionHandler)
    {
        completionHandler(UIBackgroundFetchResultNoData);
    }
}

```
And when user doesn't click in push notification incoming call, we need to handle the notification when application did become active :

```objc
- (void)applicationDidBecomeActive:(UIApplication *)application {
    if (@available(iOS 10.0, *))
    {
        UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
        [center getDeliveredNotificationsWithCompletionHandler:^(NSArray<UNNotification *> * notifications) {
            for (UNNotification* notification in notifications) {
                if ([notification.request.content.categoryIdentifier isEqualToString:@"INCOMING_CALL"]) {
                    [self handleNotification:notification.request.content.userInfo fetchCompletionHandler:nil];
                }
            }
            [center removeAllDeliveredNotifications];
        }];
    }
}

```


#### Unregister

You can unregister the Universal SDK using :
```
[yourSDKPointer.agentHandler clearCredentials];
```

This method will clear all agent information from the Universal SDK.

If an already registered agent succesfully registers on another device, the first device receives an Apple Notification to unregister.


#### Identity

The Agent can access some information about their identity (such as its display name, login, date of registration) through the `agentHandler.identity` property.


#### Usecases

Once registered, the Universal SDK generates a list of usecases that you can use to invite guests or call other agents. Those usecases are configured in the Administration Portal.

This list is stored at:

```objc
[yourSDKPointer.agentHandler.identity pincodeUsecases];
```

Those usecases are used to generate & send pincodes to guests.


The list is refreshed when the call to `fetchIdentity:` triggers its parameter block :


```objc
[yourSDKPointer.agentHandler fetchIdentity:^((BOOL success) {
  if (success) {
    NSLog(@"Usecase list refreshed!");
  }
}];
```


#### Inviting a Guest

##### Usecases

The agent is provided usecases (configured in the Administration portal) to generate pincodes.

Usecases offer a range of information (such as supported media and default media) to be used for UI composition.

##### Sending an invitation

To send an invitation to a Guest (aka a non-registered user), call:

```objc
[yourSDKPointer.agentHandler sendInvitationForUsecase:<#usecase object#> 
                                              toPhone:<#Guest phone number with country code#>
                                        withReference:<#Usecase reference#>
                                            andNotify:<#A block to execute#>];

[yourSDKPointer.agentHandler sendInvitationForUsecase:<#usecase object#> 
                                              toEmail:<#Guest email address#>
                                        withReference:<#Usecase reference#>
                                            andNotify:<#A block to execute#>];

```

These methods will send an email or a SMS. Once the request is sent, the `andNotify:` block will be executed.


A third alternative is to use : 

```objc
[yourSDKPointer.agentHandler createInvitationForUsecase:<#LSMAGuestUsecase#> 
                                            withReference:<#Usecase reference#>
                                              andNotify:<#A block to execute#>];
```

This method will return the URL that would have been sent by calling either `sendNotificationForUsecase:to...:` method.

Only one pincode is valid at a time. Requesting a new pincode without cancelling the previous one leads to undefined behaviour. You can cancel a pincode before sending another one by using `cancelPincodeAndExecute:`.

An invitation can be resent only one time by using `resendPincodeAndExecute:`.

##### Starting a call

Once the Guest accepts the call (by calling `startWithString:` with the URL provided), the Agent receives an APNS notification.

That notification is handled through the SDK's `canHandleNotification:` / `handleNotification:` (see [above](#notifications).)

If the notification is handled, the SDK delegate's `guestAcceptedCall:` is fired. Its block parameter is used to start the call or cancel the call (respectively by calling the block with `YES` or `NO`.)


#### Invitation history

A list of the last 5 invitations is kept in memory. 

It is available in the `agentHandler.invitationHistory`.


#### Save picture

Depending on the usecase configuration, picture saved by the agent will either be saved remotely or locally.

Remotely saved pictures are sent to the back after the call ends accordingly to the usecase configuration.

Locally saved pictures are stored either in the Photos.App or in the App's `~/Documents` (or any of its subfolder). In the later case, pictures can appear in the Files.App by configuring the App `info.plist`. See Apple's `UIFileSharingEnabled` and `LSSupportsOpeningDocumentsInPlace` info.plist keys. 

Please see the Administration portal to set the folder path.


If you don't want the pictures to be saved by the SDK in either way, please set the pictureDelegate's `ignoreUsecaseConfiguration` to `YES`. In this case, only the picture's `savedPicture:andMetadata:` delegate is called.



## Direct Import 

This method is not recommended. Please, use it only if you can't use CocoaPods.

To add this Framework to your project, clone it from Github using a tag:

```shell
$ git clone https://github.com/sightcall/iOS-UniversalSDK.git -t <YOUR TAG>
```

Then add `LSUniversalSDK.framework` in your Xcode project (Drag and drop the Framework in your Project Navigator or See [Apple Documentation](https://help.apple.com/xcode/mac/8.0/#/dev51a648b07)).

> **Xcode 12.3 issue**: iOS and iOS Simulator code has never been supported in the same binary 

The problem is that the USDK framework contains a build for both the simulator (x86_64) and the actual devices (ARM).

The only correct way to resolve this is to change project settings in Xcode : Build Settings → Validate Workspace → Yes

You aren't allowed to submit to the App Store a binary for an unsupported architecture, so the solution is to "manually" remove the unneeded architectures from the final binary, before submitting it.

Use the following run script code to remove unsupported architectures from added libraries, frameworks.

Project Name -> Build Phases -> create new run script past the below code. 

```shell
APP_PATH="${TARGET_BUILD_DIR}/${WRAPPER_NAME}"

# This script loops through the frameworks embedded in the application and
# removes unused architectures.
find "$APP_PATH" -name '*.framework' -type d | while read -r FRAMEWORK
do
    FRAMEWORK_EXECUTABLE_NAME=$(defaults read "$FRAMEWORK/Info.plist" CFBundleExecutable)
    FRAMEWORK_EXECUTABLE_PATH="$FRAMEWORK/$FRAMEWORK_EXECUTABLE_NAME"
    echo "Executable is $FRAMEWORK_EXECUTABLE_PATH"

    EXTRACTED_ARCHS=()

    for ARCH in $ARCHS
    do
        echo "Extracting $ARCH from $FRAMEWORK_EXECUTABLE_NAME"
        lipo -extract "$ARCH" "$FRAMEWORK_EXECUTABLE_PATH" -o "$FRAMEWORK_EXECUTABLE_PATH-$ARCH"
        EXTRACTED_ARCHS+=("$FRAMEWORK_EXECUTABLE_PATH-$ARCH")
    done

    echo "Merging extracted architectures: ${ARCHS}"
    lipo -o "$FRAMEWORK_EXECUTABLE_PATH-merged" -create "${EXTRACTED_ARCHS[@]}"
    rm "${EXTRACTED_ARCHS[@]}"

    echo "Replacing original executable with thinned version"
    rm "$FRAMEWORK_EXECUTABLE_PATH"
    mv "$FRAMEWORK_EXECUTABLE_PATH-merged" "$FRAMEWORK_EXECUTABLE_PATH"

done
```