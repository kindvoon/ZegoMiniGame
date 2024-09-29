//
//  ZegoGameComponent.h
//  ZegoMiniGameEngine
//
//  Created by zego on 2024/6/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZegoGameComponent : NSObject

/// name
@property (nonatomic, copy) NSString *name;

/// label
@property (nonatomic, copy) NSString *label;

/// isVisible
@property (nonatomic, assign) BOOL isVisible;

+ (instancetype)modelWithDictionary:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
