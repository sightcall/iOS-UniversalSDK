#iOS SDK

<!-- MarkdownTOC levels="1,2,3" autolink="true" -->

- [Installation](#installation)
    - [Dependencies](#dependencies)
    - [Common link errors](#common-link-errors)
- [Usage](#usage)
    - [Instantiation](#instantiation)
    - [Delegation](#delegation)
    - [Consent UI](#consent-ui)
    - [Call UI](#call-ui)
    - [ACD information](#acd-information)
    - [Survey](#survey)
    - [Callflows](#callflows)
    - [Agent](#agent)
    - [Save picture](#save-picture)
- [Advanced](#advanced)
    - [Logging](#logging)
    - [Abort](#abort)
    - [URL Scheme Trigger](#url-scheme-trigger)
    - [Customization](#customization)

<!-- /MarkdownTOC -->

## Installation

### Dependencies

To add this SDK to your project, clone the framework from Github using a tag:

```
git clone https://github.com/sightcall/iOS-UniversalSDK.git -t <YOUR TAG>
```

Then add `LSUniversalSDK.framework` in your Xcode project (See [Apple Documentation](https://developer.apple.com/library/ios/recipes/xcode_help-project_editor/Articles/AddingaLibrarytoaTarget.html)).

### Common link errors

#### Bitcode

The Framework is not compiled with bitcode. That means you may see an error like:
```
ld: 'LSUniversalSDK.framework/LSUniversalSDK' does not contain bitcode. You must rebuild it with bitcode enabled (Xcode setting ENABLE_BITCODE), obtain an updated library from the vendor, or disable bitcode for this target.
```

In order to fix that, you must disable Bitcode generation in your app. See your project Build Settings (in the `Build Options`, the `Enable Bitcode` should be `No`).


#### Architecture

The Framework is not compiled for `x86`/`x86_64` architectures. That means you may see errors like:

```
ld: warning: ignoring file LSUniversalSDK.framework/LSUniversalSDK, missing required architecture i386 in file LSUniversalSDK.framework/LSUniversalSDK (2 slices)
```

In order to fix that, you must compile for a device target. Either build for `Generic iOS Device` or connect a device and compile for it.

This means the USDK can't run on a `simulator`.

## Usage

### Instantiation

To start a connection, create a `LSUniversal` variable and retain it. Then call `startWithString:` with your start URL in string form (see `-[NSURL absoluteString]` for more info).


For example, let's say your application received a URL through your UIApplication delegate's `application:openURL:sourceApplication:annotation:` method:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    //yourSDKPointer is a pointer to the LSUniversal instance, that was instantiated somewhere
    //to start the connection, you would simply call:
    [yourSDKPointer startWithString: [url absoluteString]];
}
```

### Delegation

#### Connection and Calls

The SDK offers a delegate with three callbacks. Those callbacks informs the application that the connection status changed, that a call ended and that an error occured.

To register a delegate, simply set the LSUniversal variable [mySDKPointer delegate] after intializing it:

```objc
id<LSUniversalDelegate> yourDelegatePointer = [[YourDelegateType alloc] init];
mySDKPointer.delegate = yourDelegatePointer;
```

The delegate is notified through those 3 methods:


```objc
[yourDelegatePointer connectionEvent: ] //Connection Status update event
[yourDelegatePointer connectionError: ] //Connection Errors
[yourDelegatePointer callReport: ] //Calls end report

```

For example, your delegate can be declared as such:

```objc
@interface YouDelegateType: NSObject <LSUniversalDelegate>

@end


@implementation YourDelegateType
- (void)connectionEvent:(lsConnectionStatus_t)status
{
    switch (status) {
        case lsConnectionStatus_idle: break;
        case lsConnectionStatus_connecting: break;
        case lsConnectionStatus_active: break;
        case lsConnectionStatus_calling: break;
        case lsConnectionStatus_callActive: break;
        case lsConnectionStatus_disconnecting: break;
    }
}

- (void)connectionError:(lsConnectionError_t)error
{

}

- (void)callReport:(lsCallReport_s)callEnd
{

}
@end

```

In addition to those mandatory callbacks, optional callbacks are offered to display informations about the platform used, your queue position if you are connected to an ACD system and if a survey is to be displayed after a call.

Please note that the callbacks may not be on the main thread.

### Consent UI

Before call start and if the usecase is configured to display a consent request, the SDK will trigger `displayConsentWithDescription:` on its delegate.

This method's parameters contains all information about the consent view that should be displayed and a block to trigger with a boolean.

For example, it could be implemented as such:

```objc
- (void)displayConsentWithDescription:(id<LSConsentDescription>)consent
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle: [consent title]
                                                                             message: [consent message]
                                                                      preferredStyle: UIAlertControllerStyleAlert];
    UIAlertAction *cancel = [UIAlertAction actionWithTitle: [consent cancelLabel] style: UIAlertActionStyleDestructive handler: ^(UIAlertAction * _Nonnull action) {
        //trigger the consent block with `NO`
        if (consent.consent) {
            consent.consent(NO);
        }
    }];
    UIAlertAction *agree = [UIAlertAction actionWithTitle: [consent agreeLabel] style:UIAlertActionStyleDefault handler: ^(UIAlertAction * _Nonnull action) {
        //trigger the consent block with `YES`
        if (consent.consent) {
            consent.consent(YES);
        }
    }];
    UIAlertAction *showEULA = [UIAlertAction actionWithTitle: [consent eulaLabel] style:UIAlertActionStyleDefault handler: ^(UIAlertAction * _Nonnull action) {
        //Opens the URL in a web browser 
        NSURL *url = [NSURL URLWithString: [consent eulaURL]];
        if ([[UIApplication sharedApplication] canOpenURL: url]) {
            [[UIApplication sharedApplication] openURL: url];
        }
    }];
    
    [alertController addAction: agree];
    [alertController addAction: showEULA];
    [alertController addAction: cancel];
    
    // Display the controller in your current view hierarchy

}
```


### Call UI

A ViewController is available at `mySDKPointer.callViewController`. This VC is the controller of the call UI. An exemple to display it would be something like:

```objc
- (void)connectionEvent:(lsConnectionStatus_t)status
{
    switch (status) {
        case lsConnectionStatus_idle: break;
        case lsConnectionStatus_connecting: break;
        case lsConnectionStatus_active: break;
        case lsConnectionStatus_calling: break;
        case lsConnectionStatus_callActive: 
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                [yourPresentationController presentViewController:mySDKPointer.callViewController animated:YES completion:nil];
            });
        }   break;
        case lsConnectionStatus_disconnecting: break;
    }
}

```

On call end, simply dismiss the ViewController.

#### Customization

The call controls buttons appearances can be customized through the `LSCustomizationDelegate`. This delegate is entirely optional. Each method allows you to customize the related button.

Let's say you want to customize the hangup button:

```objc
//declare the customization object
@interface MyCustomizationDelegate: NSObject <LSCustomizationDelegate>
@end

@implementation MyCustomizationDelegate
@end

//somewhere in your code, after the initialization of mySDKPointer
id <LSCustomizationDelegate>myCustomizationDelegate = [[MyCustomizationDelegate alloc] init];
mySDKPointer.customizationDelegate = myCustomizationDelegate;
```

At this point, the SDK will try to inform you every time a button is resized that you can customize it. You will only receive this message if you implement the related button callback.

To customize the hangup button, implement the `customizeHangup:` method in myCustomizationDelegate

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

When the call control menu appears on screen, the hangup button will appear customized.


**Note:** the callbacks will only be called if the related buttons should appear.


### ACD information

ACD informations are sent through two optional delegation methods.


```
- (void)acdStatusUpdate:(LSACDQueue_s)update;
- (void)acdAcceptedEvent:(NSString *)agentUID;
```

`update` contains informations pertaining to the ACD current status. If the `update.status` of the request is `ongoing`, the update will inform you about the position in the queue or an ETA. Otherwise, the request is cancelled or invalid and the `update.status` informs you of the reason (service closed, agent unavailable, etc.)

Note that `acdAcceptedEvent:` **may not** be called before the SDK `status` moves to `callActive`.

### Survey
If you have configured a survey for the call end, your LSUniversalDelegate will be notified on call end through the `callSurvey:` method. This optional method is called with a `LSSurveyInfo` object. 

This parameter will tell you if you need to display a popup (if `infos.displayPopup` is equal to YES) and the text in this popup (`infos.popupLabel` and `infos.popupButton`), and give you the URL to the survey (`infos.url`).

```objc
- (void)callSurvey:(LSSurveyInfos *)infos
{
    if (!infos.displayPopup) {
        //open infos.url in a webbrowser
    } else {
        //ask the user if she wants to participate in a survey
    }
}
```

### Callflows
The standard callflow is as such:

![Standard iOS Callflow](./connection_callflow.png "iOS Callflow")

<!--

https://www.websequencediagrams.com/
title Connection callflow
participant BROWSER
participant APP
participant SDK

BROWSER->APP: URL scheme trigger
    APP->SDK: Universal.start(scheme)
    SDK->SDK: parse

alt Invalid URL scheme
    SDK->APP: UniversalConfigurationErrorEvent
else Valid URL scheme
    SDK->APP: connectionEvent: lsConnectionStatus_connecting
    SDK->SDK: connect
    SDK->APP: connectionEvent: lsConnectionStatus_active
    SDK->APP: connectionEvent:lsConnectionStatus_calling
    SDK->SDK: call
    SDK->APP: connectionEvent:lsConnectionStatus_callActive
    Note over APP,SDK:
        The call is now active
        Display the callViewController here
    end note
    SDK->SDK: hangup
    SDK->APP: callReport:
    SDK->APP: connectionEvent:lsConnectionStatus_disconnecting
    SDK->SDK: disconnect
    SDK->APP: connectionEvent:lsConnectionStatus_idle
end
!-->

### Agent

This functionality uses Apple's Push Notifications.

#### Registration
To start the registration, call:


```objc
[yourSDKPointer.agentHandler registerWithPin:<#the registration pin code#> 
                                    andToken:<#the registration token#>
                                    onSignIn:^(BOOL success, NSInteger statusCode, RegistrationError_t status){
  if (success) {
    NSLog(@"Registration successful!");
  }
}];

```

Both `pinCode` and `token` are received from our backend.

Additionaly, you must set an Apple Push Notification token. 

```objc
[yourSDKPointer.agentHandler setNotificationToken:<#yourAPNSToken#>];
```

As long as it is not set, registration will not be taking place. You can set it before calling the registration method. If you called the registration method before setting the notification token, the process will be suspended until such time a notification token is set.

This Push Notification token is used to identify your iDevice when push notifications are sent. This token is linked to your agent's account. You can only set one APN token per account.


The `onSignIn:` block is fired whether the registration was successful or not. 

Upon registration, `yourSDKPointer.agentHandler.available` is YES, and you should have access to a list of usecase.

You can unregister the Universal SDK using :
```
[yourSDKPointer.agentHandler clearCredentials];
```

This method will clear all information from the Universal SDK.


#### List of Usecases

Once registered, the Universal SDK generates a list of usecases that you will use to invite guests and other agents. Those usecases are configured in the Administration Portal.

This list is stored at:

```objc
[yourSDKPointer.agentHandler usecases];
```

The list is automatically fetched upon startup if agent credentials are available. It is also fetched upon registration success.

That list can become stale, and can be refreshed using:

```objc
[yourSDKPointer.agentHandler fetchUsecases:^((BOOL success, NSArray<NSObject<LSMAUsecase> *> *usecaselist) {
  if (success) {
    NSLog(@"Usecase list refreshed!");
  }
}];
```

The usecase list should at maximum contain only one instance of each LSMAUsecase protocol-compliant class: 
`LSMAACDUsecase`, `LSMAAgentUsecase`, `LSMAGuestUsecase`.


#### Invite Guests

##### Sending invitation

To send an invitation to a Guest (aka a non-registered user), call:

```objc
[yourSDKPointer.agentHandler sendNotificationForUsecase:<#LSMAGuestUsecase#> 
                                                toEmail:<#Guest Email#> 
                                         andDisplayName:<#Guest displayname#> 
                                              andNotify:<#A block to execute#>];

[yourSDKPointer.agentHandler sendNotificationForUsecase:<#LSMAGuestUsecase#> 
                                                toPhone:<#Guest phone number#> 
                                         andDisplayName:<#Guest displayname#> 
                                              andNotify:<#A block to execute#>];
```

These methods will send an email (or a SMS) to the guest. Once the notification is sent, the notification block will be executed.


A third alternative is to use the 
```objc
[yourSDKPointer.agentHandler createInvitationForUsecase:<#LSMAGuestUsecase#> 
                                            usingSuffix:<#A unspecified String#>
                                              andNotify:<#A block to execute#>];
```

This method will return the URL that would have been sent by calling either `sendNotificationForUsecase:toPhone:AndNotify:` or `sendNotificationForUsecase:toEmail:AndNotify:`.

An invitation created that way must be cancelled when no longer needed using

```objc
[yourSDKPointer.agentHandler cancelInvitationOfSuffix:<#The suffix used to create the invite#>];
```

Invitations sent by using `sendNotificationForUsecase:toEmail:AndNotify:` or `sendNotificationForUsecase:toPhone:AndNotify:` are automatically cancelled on call end.


##### Answering invitation

On iOS, the Agent that sent the invitation receives a Push Notification after the Guest starts the Universal SDK with the received URL.

You should check if the Universal SDK can handle the method before providing the method to the SDK (in case your App uses Push Notification for something else):

Check that this notification can be handled by the Universal SDK before
```objc
//In your code, a class conforms to the PushKit protocol and receive a notification
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(NSString *)type
{
  if ([youSDKPointer canHandleNotification:payload.dictionaryPayload]) {
    [youSDKPointer handleNotification:payload.dictionaryPayload];
  }
}
```


#### Invite Agents


##### Sending invitation

Inviting another Agent is done by calling

```objc
[yourSDKPointer.agentHandler sendNotificationForUsecase:<#LSMAAgentUsecase#> 
                                                toAgent:<#Agent UID#> 
                                              andNotify:<#A block to execute#>];
```

##### Answering invitation

On iOS, the called Agent receives a Push Notification by using the dedicated PushKit delegate method.

In that method, you should check if the Universal SDK can handle the method before providing the method to the SDK (in case your App uses Push Notification for something else):

```objc
//In your code, a class conforms to the PushKit protocol and receive a notification
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(NSString *)type
{
    //yourSDKPointer is your reference to the LSUniversal instance.
    if ([yourSDKPointer canHandleNotification:payload.dictionaryPayload]) {
      [yourSDKPointer handleNotification:payload.dictionaryPayload];
    } else {
      NSLog(@"This is not a LSUniversalSDK notification.");
    }
}
```

#### Activity

The Agent keeps a log of the Activity. Activities are invitations being sent (or URL being created), call started and image uploaded. This log can be found in the `activityHandler` property of your LSUniversal object.


#### Register a delegate

You can assign a delegate to this object to receive notifications when an invite is added to the pool

```objc
    //yourSDKPointer is your reference to the LSUniversal instance.
    //somewhere in your code, you register an `id<LSALContextDelegate>` variable to the activityHandler
    if (yourSDKPointer.activityHandler) {
      [yourSDKPointer.activityHandler setDelegate:yourActivityDelegate];
    } else {
      NSLog(@"No activity handler on this variable: %@", yourSDKPointer);
    }
```

This delegate is notified when the `entries` array is modified through firing of the `entriesUpdate` method.


### Save picture

While connected as agent, a `Save picture` button exists in the Remote bar. This button triggers an image capture of the current main visual in the App.

Where the pictures are saved depends on the usecase's `Agent Controls` `Save picture configuration` section.

The `Media` section can take one of the two values: `cloud` and `local`. They will respectively upload them to SightCall's back-end after the call ends, or save the pictures locally.

In both case, the `LSPictureProtocol` delegate is used to update the App.

#### Register a delegate

Set the value of `pictureDelegate` in your LSUniversal variable to be notified either of a picture being saved (only in `local`) or of the picture's upload (only in `cloud`): 

```objc
    //in your App code
    //yourSDKPointer is your reference to the LSUniversal instance.
    //yourPictureDelegate is an `id <LSPictureProtocol>` type variable retained in your code App.
    [yourSDKPointer setPictureDelegate: yourPictureDelegate];
```



#### `local` mode

The picture can either be stored in the App storage or in the Library.

###### App storage

The Local mode allows the App to be notified when a picture is taken by the agent. This notification takes the form of a callback in the `LSPictureProtocol` delegate.

```objc
//In yourPictureDelegate's code
- (void)savedPicture:(UIImage *)image andMetadata:(LSPictureMetadata *)metadata
{
    NSLog(@"A picture has been taken: %@", image);
}

```


The `metadata` variable contains data about the picture, such as GPS location (if requested before), the timestamp of the picture in the call, the origin of the picture (if any), etc.

###### Library storage

To have the picture saved to the device's Library, set the `agentHandler`'s `saveLocally` to `YES`. The image will be stored in a collection named after the `agentHandler`'s `albumName` after the `savedPicture:andMetadata:` callback is called (see above.)

```objc
    //somewhere in you App code, before the call ends.
    //yourSDKPointer is your reference to the LSUniversal instance.
    [yourSDKPointer.agentHandler setSaveLocally:YES];
    [yourSDKPointer.agentHandler setAlbumName:@"Your Album Name"];

```


#### `cloud` mode

The cloud mode has the picture uploaded after the call ends. The App is notified of the picture being uploaded, as well as a thumbnail and index of that picture.

```objc
//In yourPictureDelegate's code
- (void)uploadingPicture:(NSInteger)pictureID of:(NSInteger)maxID andThumbnail:(UIImage *)image
{
    NSLog(@"Uploading picture %d of %d", (int)pictureID, (int)maxID);
}
```


## Advanced

### Logging

The SDK send logs to any object implementing `LSUniversalLogDelegate` and registered as `LSUniversal.logDelegate`.

The following presents a way to receive and print logs on the debugger console. 

Be aware that: 
* uncontrolled use of `NSLog();` may lead to performance degradation;
* `NSLog();` send logs to the device console (Xcode -> Window -> Devices and Simulator).


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





### Abort

To abort an ongoing connection attempt, call `[mySDKPointer abort]`.

`connectionError:` and a `connectionEvent:` callbacks will then be called.

### URL Scheme Trigger

To start your application using an URL scheme, declare the scheme in the Xcode project of your app. See [Apple Documentation](https://developer.apple.com/library/ios/documentation/iPhone/Conceptual/iPhoneOSProgrammingGuide/Inter-AppCommunication/Inter-AppCommunication.html#//apple_ref/doc/uid/TP40007072-CH6-SW10)


### Customization

Several fields can be translated using the `Strings.localizable` file of your project (See [Apple Documentation](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/InternationalizingYourUserInterface/InternationalizingYourUserInterface.html#//apple_ref/doc/uid/10000171i-CH3-SW4)):

See [Languages.md](./Languages.md) for the key/value entries and descriptions.
