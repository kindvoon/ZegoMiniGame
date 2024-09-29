Pod::Spec.new do |s|
  s.name             = 'ZegoMiniGame'
  s.version          = '1.0.0'
  s.summary          = 'A short description of ZegoMiniGame.'
  s.homepage         = 'https://github.com/kindvoon/ZegoMiniGame.git'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'kindvoon' => 'kindvoon@gmail.com' }
  s.source           = { :git => 'https://github.com/kindvoon/ZegoMiniGame.git', :tag => s.version.to_s }
  s.ios.deployment_target = '12.0'
  s.frameworks = 'ZegoConnection', 'ZegoMiniGameEngine'
  s.ios.vendored_frameworks = 'Frameworks/ZegoConnection.xcframework', 'Frameworks/ZegoMiniGameEngine.xcframework'
  s.libraries   = "iconv", "z", "stdc++", "c++"
  s.requires_arc = true
  s.pod_target_xcconfig = { 'VALID_ARCHS' => 'x86_64 armv7 arm64' }
  
end

