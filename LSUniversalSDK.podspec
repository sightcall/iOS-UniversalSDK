Pod::Spec.new do |s|
    s.name             = 'LSUniversalSDK'
    s.homepage         = 'https://github.com/sightcall/iOS-UniversalSDK'
    s.author           = { 'sightcall' => 'developer@sightcall.com' }
s.version='2.6.2'
    s.source           = { :http => "https://sightcall-ios-cocoapods.s3.amazonaws.com/universalSDK/#{s.version}/sdk.zip" }
    s.documentation_url = 'https://github.com/sightcall/iOS-Documentation/blob/main/README.md'
    s.swift_version    = '5.3.1'
    s.platform         = :ios
    s.ios.deployment_target = '9.0'

    s.summary          = 'The SDK to integrate SightCall services into your iOS and iPadOS applications'
    s.description      = <<-DESC
                            SightCall is an enterprise-grade video cloud platform helping service leaders improve outcomes without deploying unnecessary support to the field. We blend the digital and physical worlds into a real-time collaborative environment that empowers technicians, reduces spend and improves the customer experience.
                        DESC
  
    s.license          = { :type => 'Copyright', :text => <<-LICENSE
                                ©SightCall 2021. All rights reserved.
                            LICENSE
                        }
  
  s.subspec 'Multiparty' do |mp|
    mp.vendored_frameworks = 'Multiparty.xcframework'
  end
  
  s.subspec 'LiveTranslation' do |lt|
    lt.vendored_frameworks = 'LiveTranslation.xcframework'
  end
  
  s.subspec 'AdvancedAnnotations' do |aa|
    aa.vendored_frameworks = 'AdvancedAnnotations.xcframework'

    aa.dependency 'SVGgh', '~> 1.11'
  end

  s.subspec 'Core' do |core|
    core.vendored_frameworks = 'LSUniversalSDK.xcframework'
  
    core.dependency 'AFNetworking/NSURLSession', '~> 3'
    core.dependency 'MMWormhole/Core', '~> 2.0.0'
    core.dependency 'libPhoneNumber-iOS', '0.9.13'
    core.dependency 'FormatterKit/LocationFormatter', '~> 1.8'
    core.dependency 'FormatterKit/TimeIntervalFormatter', '~> 1.8'
    core.dependency 'MTBBarcodeScanner', '~> 5.0'
    core.dependency 'MaterialComponents/TextFields', '~> 104.0'
    core.dependency 'MaterialComponents/TextFields+ColorThemer', '~> 104.0'
    core.dependency 'MaterialComponents/TextFields+Theming', '~> 104.0'
    core.dependency 'MaterialComponents/TextFields+TypographyThemer', '~> 104.0'
    core.dependency 'MaterialComponents/ActivityIndicator', '~> 104.0'
  end
end
