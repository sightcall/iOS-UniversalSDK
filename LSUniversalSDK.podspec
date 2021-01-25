#
# Be sure to run `pod lib lint LSUniversalSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
    s.name             = 'LSUniversalSDK'
    s.version          = '2.4.1.5'
    s.summary          = 'The higher level "Universal App" SDK'
    s.swift_version    = '5.3.1'
  
    s.description      = <<-DESC
    Add long description of the pod here.
                         DESC
  
    s.homepage         = 'https://github.com/sightcall/iOS-UniversalSDK'
    s.author           = { 'developer' => 'developer@sightcall.com' }
    s.source           = { :git => 'https://github.com/sightcall/iOS-UniversalSDK.git' }
    s.vendored_frameworks = 'LSUniversalSDK.xcframework'
  
    s.ios.deployment_target = '9.0'

    s.dependency 'AFNetworking/NSURLSession', '~> 3'
    s.dependency 'MMWormhole/Core', '~> 2.0.0'
    s.dependency 'libPhoneNumber-iOS', '0.9.13'
    s.dependency 'FormatterKit/LocationFormatter', '~> 1.8'
    s.dependency 'FormatterKit/TimeIntervalFormatter', '~> 1.8'
    s.dependency 'MTBBarcodeScanner'
    s.dependency 'MaterialComponents/TextFields'
    s.dependency 'MaterialComponents/TextFields+ColorThemer'
    s.dependency 'MaterialComponents/TextFields+Theming'
    s.dependency 'MaterialComponents/TextFields+TypographyThemer'
    s.dependency 'MaterialComponents/ActivityIndicator'
  end
  
