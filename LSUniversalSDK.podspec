#
# Be sure to run `pod lib lint LSUniversalSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
    s.name             = 'LSUniversalSDK'
    s.version          = '2.5.1'
    s.summary          = 'The SDK to integrate SightCall's services into your iOS and iPadOS applications'
    s.swift_version    = '5.3.1'
  
    s.description      = <<-DESC
    SightCall is an enterprise-grade video cloud platform helping service leaders improve outcomes without deploying unnecessary support to the field. We blend the digital and physical worlds into a real-time collaborative environment that empowers technicians, reduces spend and improves the customer experience.
                         DESC
  
    s.homepage         = 'https://github.com/sightcall/iOS-UniversalSDK'
    s.author           = { 'sightcall' => 'developer@sightcall.com' }
    s.source           = { :git => 'https://github.com/sightcall/iOS-UniversalSDK.git' }
    s.ios.deployment_target = '9.0'

  s.subspec 'AdvancedAnnotations' do |aa|
    aa.vendored_frameworks = 'AdvancedAnnotations.xcframework'

    aa.dependency 'SVGgh'
  end

  s.subspec 'USDK' do |usdk|
    usdk.vendored_frameworks = 'LSUniversalSDK.xcframework'
  
    usdk.dependency 'AFNetworking/NSURLSession', '~> 3'
    usdk.dependency 'MMWormhole/Core', '~> 2.0.0'
    usdk.dependency 'libPhoneNumber-iOS', '0.9.13'
    usdk.dependency 'FormatterKit/LocationFormatter', '~> 1.8'
    usdk.dependency 'FormatterKit/TimeIntervalFormatter', '~> 1.8'
    usdk.dependency 'MTBBarcodeScanner'
    usdk.dependency 'MaterialComponents/TextFields'
    usdk.dependency 'MaterialComponents/TextFields+ColorThemer'
    usdk.dependency 'MaterialComponents/TextFields+Theming'
    usdk.dependency 'MaterialComponents/TextFields+TypographyThemer'
    usdk.dependency 'MaterialComponents/ActivityIndicator'
  end
end
