# Changelog

<!-- MarkdownTOC levels="1,2" autolink="true" -->

- [2.4.1](#241)
- [2.3.1](#231)
- [2.3.0](#230)
- [2.2.0](#220)
- [2.1.7](#217)
- [2.1.6](#216)
- [2.1.5](#215)
- [2.1.4](#214)
- [2.1.3](#213)
- [2.1.2](#212)
- [2.1.1](#211)
- [2.1.0](#210)
- [2.0.8](#208)
- [2.0.7](#207)
- [2.0.6](#206)
- [2.0.5](#205)
- [2.0.4](#204)
- [2.0.3](#203)
- [2.0.2](#202)
- [2.0.0](#200)
- [1.4.11](#1411)
- [1.4.10](#1410)
- [1.4.9](#149)
- [1.4.6](#146)
- [1.4.0](#140)
- [1.3.0](#130)
- [1.2.12](#1212)
- [1.2.11](#1211)
- [1.2.4](#124)
- [1.1.2](#112)
- [1.0.1](#101)
- [0.10.1](#0101)
- [0.9.12](#0912)
- [0.9.3](#093)
- [0.9.2](#092)
- [0.9.1](#091)
- [0.9.0](#090)
- [0.8.1](#081)
- [0.8.0](#080)

<!-- /MarkdownTOC -->

## 2.4.1
> 2021/01/19
> __mucl 00331739__

### Change
- Update OpenSSL version in mobile SDKs
- Manual Display name for Guest and Attendee
- Implement role switching Guest-Attendee
- Agent Poll for Mobile Agent
- Implement multiparty chat
- Add capabilities handling
- Support mute/unmute in conference

### Fix
- Add notes after share from agent
- Enable attendee ssl
- Fix Bypass consent with display name
- Add JPEG support for multiparty snapshot with WebRTC participants
- Attendee bar does not show up when clicking on the video window
- Annotations are not properly displayed on a paused video share
- Dismissing the media picker by sliding it to the bottom blocks the guest app until he hangs up.
- Co-browsing not working
- Failing UHD image uploads try to upload forever, and block the app UI
- Consent Declined does not inform the agent 

## 2.3.1
> 2020/07/13
> __mucl 5a1a3791__

### Change
- Add Offline media upload
- Add OCR teacher
- Add Live OCR

### Fix
- MultiPart Call participants flush view
- Screen cast issue
- Hide take screenshot button when pause video is enabled
- Save picture issue
- Chat View design

## 2.3.0
> 2020/06/05
> __mucl 6a17a032__

### Fix
- Screen cast issue
- Agent push notification
- MGA-827 Notes on Picture feature is not localized
- MGA-830 Recording SightCall sessions using Mobile Agent App is not working
- MGA-835 Redirect to agent survey

## 2.2.0
> 2019/11/18
> __rtcc 6.10.3__

### Change
- Add live QR Bar Code scanner
- Upload UHD pictures in Background task

### Fix
- Disable camera when guest take a picture
- Fix Crash on iPad when guest touch share media button

## 2.1.7
> 2019/11/12  
> __rtcc 6.10.2__

### Fix
- MGA-737 Warnings on non-main thread UI Activity
- LSN-4614 Fix fuzzy green video issue


## 2.1.6
> 2019/09/16  
> __rtcc 6.10.2__  

### Change
- The screencasting local button only appears if the feature is supported by the embedding App
- Use WKWebView instead of depreciated UIWebKitView
- Rename various unprefixed internal classes

### Fix
- Broadcast Menu not appearing on iOS 13 
- MGA-718 Fix zoom level not being reset on webconsole on camera stop
- MGA-640 Fix Video player frame rotation
- LSN-4405 Don't send chat transcript if said not to

## 2.1.5
> 2019/08/19  
> __rtcc 6.10.2__  

### Fixed
- Crash in the video player

## 2.1.4
> 2019/08/12  
> __rtcc 6.10.2__  

### Fixed
- MGA-702 Crash on armv7 hardware


## 2.1.3
> Unreleased  
> __rtcc 6.10.1__

### Fixed 
- MGA-692 Video stops on share stop
- MGA-694 ACD External reference and value switched

## 2.1.2
> 2019/07/15  
> __rtcc 6.10.1__

### Fixed
- MGA-688 Localization for disconnecting popup
- Update documentation

## 2.1.1
> 2019/07/01  
> __rtcc 6.10.0__

### Fixed
- A crash on AR stop


## 2.1.0
> 2019/07/01  
> __rtcc 6.10.0__

### Added:
- Hangup popup 
- AR
- Screencast (iOS 11+)

### Fixed
- MGA-543 Add support for arbitrary URL base for API calls
- MGA-652 Keep torch during snapshot
- MGA-461 Reference not appearing in survey 
- MGA-656 Crash on "Take Picture"



## 2.0.8
> Unreleased  
> __rtcc 6.9.9__

### Fixed
- Customization callback not covering all buttons


## 2.0.7
> Unreleased  
> __rtcc 6.9.9__  

### Changed
- Video player UI


## 2.0.6
> Unreleased  
> __rtcc 6.9.9__

### Added 
- Greek (el) localization

### Fixed
- Status message could not be sent on call start


### Changed
- Tapping hangup will show a confirmation popup
- Global localization update
- Podfile update 


## 2.0.5
> Unreleased  
> __rtcc 6.9.8__

### Added
- Turkish (tr) localization

### Fixed
- Fixes invitation as attendee support


## 2.0.4
> Unreleased  
> __rtcc 6.9.8__

### Changed
- Registration starts when notificationToken is set and is delayed until then

### Fixed
- Video profile is not respected on call start
- Video pause state not kept after a background/foreground cycle

## 2.0.3
>  Unreleased   
> __rtcc 6.9.6__

### Changed
- Enable bitcode for the Universal SDK

## 2.0.2
>  2019/03/05  
> __rtcc 6.9.5__

### Fixed
- Agent registration fails with an Internal Server error

## 2.0.0
>  2019/03/03    
> __rtcc 6.9.5__

### Changed
- New agent
- Upgraded support for localization


## 1.4.11
> 2018/11/22  
> __rtcc 6.9.4__

### Added
- Support for variable external ACD endpoint

### Changed
- Enhance camera source selection for iOS10+ devices
- Uses `uid` for `calleeid` if the later is not present in the queryparameter URL
- Disable bitcode generation

### Fixed
- Snapshot not respecting device orientation (MGA-550)


## 1.4.10
> 2018/10/03  
> __rtcc 6.9.3__  

### Fixed
- Fix a crash when some mandatory parameters of the hash reference change to optional

### Changed
- Removed dead code

## 1.4.9
> 2018/08/20  
> __rtcc 6.9.2__

### Added
- Agent can save pictures to device's Photo library
- Bulgarian language translations

### Fixed
- Stuck when attempting to start a call while refreshing agent status
- Snapshot preventing camera stream to restart


## 1.4.6
> 2018/06/18  
> __rtcc 6.9.0__  

### Fixed
- Crash on external/reference returning non HTTP response
- Taking a snapshot on non portrait returns a rotated picture
- Video player skip 
- Incorrect JSON format for attendee and host action

## 1.4.0
> 2018/05/24  
> __rtcc 6.9.0__  

### Added
- Consent form support


### Fixed
- Agent could become stuck on connection
- Crash on camera change
- Video displayed at the wrong size after a snpashot


## 1.3.0
> 2018/04/09  
> __rtcc 6.8.6__

### Added
- OCR
- Chat

## 1.2.12

> 2018/03/23  
> __rtcc 6.8.5__

### Fixed
- Fix the ACD start

## 1.2.11
> 2018/01/19  
> __rtcc 6.8.4__

### Fixed
- Sign-in could fail on agent starting a call as guest
- Picture uploads freezes the App
- App crashes on call end
- Drawing colors displayed by attendees in multiparty calls (host / guest / attendees)


## 1.2.4
> 2017/12/18  
> __rtcc 6.8.1__


### Added
- Support for Agent to Agent ACD
- Support for Proposal & Signature

### Fixed
- Zoom factor returned 100% when no camera is available
- Process locks during agent registration
- Drawing with low point counts
- Crash on share snapshot

### Changed
- URL and Message (email / SMS) invite creation each add 2 entries to the activity list



## 1.1.2
> 2017/11/20  
> __rtcc 6.8.1__  

### Added
- Support for new case reports
- Proposal & Signature

### Fixed
- Drawing on video and share



## 1.0.1
> 2017/09/14  
> __rtcc 6.7.2__

### Fixed
- Remote video share stop
- Invalid call duration returned after call end
- Agent call would not start after the guest accept the invitation
- QoS webpage displaying wrong platform info
- QoS results could not be shared sometimes
- Drawing while video pause on the image edges

### Added
- Support for Agent local save picture
- Support for Agent recording pause / resume

### Changed
- Call menu buttons behaviour and colours


## 0.10.1

> 2017/07/20  
> __rtcc 6.7.0__

#### Added
- Quality of Service
- Agent to Agent
- Invite creation without notification being sent


#### Changed
- RtccSDK 6.7.0


## 0.9.12

> 2017.03.30  
> __rtcc 6.6.15__

#### Fixed
- The drawing and pointers were slow

#### Changed
- RtccSDK 6.6.15


## 0.9.3

> 2017.02.15   
> __rtcc 6.6.5__

#### Added
- Save picture

#### Fixed
- Enhanced agent's local menu bar behavior related to player


## 0.9.2

> 2017.02.09  


#### Fixed
- MenuBar customization
- Some drawing points fix

#### Changed
- RtccSDK 6.6.10

## 0.9.1

> 2017.01.05  
> __rtcc 6.6.7__

#### Added


#### Fixed
- SMS phone number in international format (+XX) support


## 0.9.0

> 2016.12.23  
> __rtcc 6.6.7__

#### Added
- Documentation related to Privacy statements declaration
- Snapshot mode

#### Changed
- RtccSDK 6.6.7

## 0.8.1

> 2016.12.12  
> __rtcc 6.6.5__

#### Added
- RTCCSTATUS command family
- HAPv3 hidden support
- Battery and network monitoring support

#### Fixed
- ACD external waiting time

#### Changed
- RtccSDK 6.6.5


## 0.8.0

> 2016.12.08  

#### Added
- Support for external ACD 

#### Fixed
- Default source crash if AVCaptureDevice not available 
- Various drawing and pointer issues on share


