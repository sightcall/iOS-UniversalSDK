# Changelog

<!-- MarkdownTOC levels="1,2" autolink="true" -->

- [2.1.4](#214)
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
## 2.1.4
> 2019/08/12  
> __rtcc 6.10.2__  

### Fixed 
- MGA-702 Crash on armv7 hardware


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


