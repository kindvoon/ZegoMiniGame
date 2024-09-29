//
//  ZegoGameRobotConfig.h
//  ZegoMiniGameEngine
//
//  Created by zego on 2023/5/11.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZegoGameRobotConfig : NSObject

/// The difficulty of the robot, 0-5, 0 is random, 1-5, increasing from easy to difficult, other values are treated as 0.
@property (nonatomic, assign) int robotLevel;

/// The name of the bot.
@property (nonatomic, copy) NSString *robotNickName;

/// The url of the robot avatar, the communication protocol must be HTTPS.
@property (nonatomic, copy) NSString *robotAvatar;

/// Match the waiting time of real people, and use robots after this matching time. The unit is seconds.
@property (nonatomic, assign) int useRobotAfterTime;

@property (nonatomic, assign) int minRobotPoints;

@property (nonatomic, assign) int maxRobotPoints;

- (instancetype)initWithRobotLevel:(int)robotLevel
           robotNickName:(NSString *)robotNickName
             robotAvatar:(NSString *)robotAvatar
       useRobotAfterTime:(int)useRobotAfterTime
           minRobotPoints:(int)minRobotPoints
           maxRobotPoints:(int)maxRobotPoints;

@end

NS_ASSUME_NONNULL_END
