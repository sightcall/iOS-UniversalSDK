#
# Be sure to run `pod lib lint LSUniversalSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
    s.name             = 'LSUniversalSDK'
    s.version          = '2.4.1.4'
    s.summary          = 'The higher level "Universal App" SDK'
    s.swift_version    = '5.3.1'
  
    s.description      = <<-DESC
  Add long description of the pod here.
                         DESC
  
    s.homepage         = 'https://git.core.cloud.weemo.com/ios/livesight-universalsdk'
    s.author           = { 'martinprot' => 'martin.prot@sightcall.com' }
    s.source           = { :http => 'https://github.com/sightcall/iOS-UniversalSDK/LSUniversalSDK.xcframework.zip' }
  s.vendored_frameworks = 'LSUniversalSDK.xcframework'
  
    s.ios.deployment_target = '9.0'
    
    # This command will be executed during the "pod install", after cocoapod cloned the repo
    #s.prepare_command = <<-CMD
    #    ./update_mucl.sh
    #CMD

    s.source_files = 'LSUniversalSDK/**/*.h', 'LSUniversalSDK/**/*.m', 'LSUniversalSDK/**/*.swift', 'LSUniversalSDK/**/*.c',
                     'mucl/headers/*.h'
    s.public_header_files = 'LSUniversalSDK/**/External/*.h'
                    
    s.ios.vendored_library = 'mucl/libmucl.a'

    s.resources =   'LSUniversalSDK/Assets/Images.xcassets',
                    'LSUniversalSDK/Assets/Lang/**/*.strings',
                    'LSUniversalSDK/Assets/UI/*.xib',
                    'LSUniversalSDK/Assets/UI/*.storyboard',
                    'LSUniversalSDK/Assets/Database/*.xcdatamodeld',
                    'LSUniversalSDK/Assets/MaterialComponent/*.bundle'

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
  
