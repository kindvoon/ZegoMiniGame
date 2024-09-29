//
//  ZegoMiniGameEngine.h
//  ZegoMiniGameEngine
//
//  Created by zego on 2022/12/2.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ZegoGameEngineError.h"
#import "ZegoGameDefines.h"
#import "ZegoGameInfo.h"
#import "ZegoGameUserInfo.h"
#import "ZegoGameEngineHandler.h"
#import "ZegoGameLanguage.h"
#import "ZegoGameInfoDetail.h"
#import "ZegoGameOrientation.h"
#import "ZegoGameMode.h"
#import "ZegoGameTaxType.h"
#import "ZegoGameRobotConfig.h"
#import "ZegoUserSeatInfo.h"
#import "ZegoRobotSeatInfo.h"
#import "ZegoStartGameConfig.h"
#import "ZegoCloudGameEngine.h"
#import "ZegoGameComponent.h"

@interface ZegoMiniGameEngine : NSObject

/// Create ZegoMiniGameEngine singleton object
///
/// Available since: 1.0.0 and above.
/// Description:Create ZegoMiniGameEngine singleton object
/// When to call:The engine needs to be created before calling other functions.
/// Caution: The SDK only supports the creation of one instance of ZegoMiniGameEngine. Multiple calls to this function return the same object.
///
/// @return Engine singleton instance
+ (ZegoMiniGameEngine *_Nonnull)sharedEngine;

/// This function is unavailable.
///
/// Please use [sharedEngine] instead
+ (instancetype _Nonnull )new NS_UNAVAILABLE;

/// This function is unavailable.
///
/// Please use [sharedEngine] instead
- (instancetype _Nonnull )init NS_UNAVAILABLE;

/// Gets the SDK's version number.
///
/// Available since: 1.0.0 and above.
/// Description: If you encounter an abnormality during the running of the SDK, you can submit the problem, log and other information to the ZEGO technical staff to locate and troubleshoot. Developers can also collect current SDK version information through this API, which is convenient for App operation statistics and related issues.
/// When to call: Any time.
/// Caution: None.
///
/// @return SDK version.
+ (NSString *_Nullable)getVersion;

/// Initializing the ZegoMiniGameEngine.
///
/// Available since: 1.0.0 and above.
/// Description: Initializing the ZegoMiniGameEngine.
/// When to call: Called first after the getInstance method
/// Caution: None.
///
/// @param appID appID requested from Zego
/// @param token token generated by the business server.
/// @param userInfo Basic information of users
/// @param callBack Receive the result callback of init
- (void)init:(long)appID token:(NSString *_Nonnull)token userInfo:(ZegoGameUserInfo *_Nonnull)userInfo callBack:(IZegoCommonCallBack _Nonnull)callBack;

/// Update the SDK's token
///
/// Available since: 1.0.0 and above.
/// Description: To update the token, the token passed during init has a validity period. After the validity period expires, if the token is not updated, some interface requests such as getGameList and getGameInfo will fail. Therefore, you need to use updateToken to refresh the token after the token expires.
/// When to call: After init, it is called when the token expires.
/// Caution: None.
///
/// @param token  token generated by the business server.
- (void)updateToken:(NSString *_Nonnull)token;

/// Destroy the ZegoMiniGameEngine singleton object and deinitialize the SDK.
///
/// Available since: 1.0.0 and above.
/// Description: Destroy the ZegoMiniGameEngine singleton object and deinitialize the SDK.
/// When to call: When the SDK is no longer used, the resources used by the SDK can be released through this interface.
/// Caution: call after init:
- (void)unInit;

/// Set the parent container of the game view
///
/// Available since: 1.0.0 and above.
/// Description: Set the parent container of the game view to host the mini game view.
/// When to call: After calling the [init] method, before calling the [loadGame] method.
/// Caution: If no parent container is set, an error will be reported when calling [loadGame], error code 7000010.
///
/// @param gameContainer  A container for hosting mini-games
- (void)setGameContainer:(UIView *_Nonnull)gameContainer;

/// Set the game's event callback
///
/// Available since: 1.0.0 and above.
/// Description: Set the game's event callback.
/// When to call: After calling the [init] method, before calling the [loadGame] method.
/// Caution: None
///
/// @param handler Event notification callback. [nil] means not receiving any callback notifications.
- (void)setGameEngineHandler:(nullable id<ZegoGameEngineHandler>)handler;

/// Set the language of the game
///
/// Available since: 1.0.0 and above.
/// Description:Set the language of the mini game.
/// When to call: After calling the [init] method, before calling the [loadGame] method.
/// Caution: None
///
/// @param language the language of the mini game.
- (void)setGameLanguage:(ZegoGameLanguage)language;

/// Get a list of all games
///
/// Available since: 1.0.0 and above.
/// Description: Get a list of all games
/// When to call: After calling the [init] method
/// Caution: None
///
/// @param callBack Method execution result callback.
- (void)getAllGameList:(IZegoGameListCallBack _Nullable )callBack;

/// Get a list of games by game mode
///
/// Available since: 1.0.0 and above.
/// Description: Get a list of games by game mode.
/// When to call: After calling the [init] method
/// Caution: None
///
/// @param gameMode Request game mode, you can use the following options.
///            ZegoGameModeHostsGame Return to the host's game with play mode.
///            ZegoGameModeShowGame Return to show mode games.
///            ZegoGameModeMallGame Return to pure play mode.
///            ZegoGameModeMatchInGame Return to match in game mode games.
/// @param callBack Method execution result callback.
- (void)getGameList:(ZegoGameMode)gameMode callBack:(IZegoGameListCallBack _Nullable )callBack;

/// Get game details
///
/// Available since: 1.0.0 and above.
/// Description: Get game details based on game ID
/// When to call: After calling the [init] method
/// Caution: None
///
/// @param gameID  game ID
/// @param callBack Method execution result callback.
- (void)getGameInfo:(NSString *_Nonnull)gameID callBack:(IZegoGameInfoDetailCallBack _Nullable)callBack;

/// Load Game
///
/// Available since: 1.0.0 and above.
/// Description: Load Game
/// When to call: After calling the [init] method, before the [onUnloadGame] callback method
/// Caution: None
///
/// @param gameID game ID
/// @param gameMode game loading mode.
///                ZegoGameModeHostsGame : the host's game with play mode.
///                ZegoGameModeShowGame :  show mode games.
///                ZegoGameModeMallGame :  pure play mode.
///                ZegoGameModeMatchInGame : match in game mode.
/// @param gameConfig   ome games support configuring through this parameter during loading. Before configuring, please confirm the configurable fields of the game with ZEGO technology.
///     "customPlaySound"  : BOOL type   (Whether to customize playing game sounds. If set to true, you need to play the sound based on the callback notification from [onGameSoundPlay]. If set to false, the sound will be automatically played by the webView.)
///     "roomID"  :  NSString type  (Game room ID, corresponding to the business room ID created by the anchor, required when the anchor plays in random matching mode.)
///     "pointIconUrl" :  NSString type   ( URL of the point icon in the game, type is String. If developers want to use their own point icon, please pass in the icon resource address with HTTPS communication protocol.)
///     "minGamePoint"  : int type  (The minimum number of game points required to play the game.)
///     "useRobot"  :BOOL type  (Whether to use robots in the game, in the half-screen mode and full-screen mode. true means to use, false means not to use. If set to true, you need to return the configuration of the game robot in [onRobotConfigRequire].)
/// @param callBack Method execution result callback.
- (void)loadGame:(NSString *_Nonnull)gameID gameMode:(ZegoGameMode)gameMode gameConfig:(NSDictionary <NSString *, id> *_Nonnull)gameConfig callBack:(IZegoLoadGameCallBack _Nullable )callBack;

/// Start the game (Not all robots)
///
/// Available since: 1.0.0 and above.
/// Description: Start the game --- the host plays with the mode (ZegoGameModeHostsGame), no need to call it in the normal field (it can include robots)
/// When to call: After calling the [init] method,
/// Caution: userSeatInfoList cannot be empty
///
/// @param gameID game ID
/// @param roomID room ID such as language chat room ID, live room ID.
/// @param gameConfig Game configuration items, such as: tax rate, timeout. . .
/// @param userSeatInfoList Game player seat information (must have a value, not all robots).
/// @param robotSeatInfoList Robot Player Seat Information.
/// @param callBack Method execution result callback.
- (void)startGame:(NSString *_Nonnull)gameID
           roomID:(NSString *_Nullable)roomID
       gameConfig:(ZegoStartGameConfig *_Nullable)gameConfig
 userSeatInfoList:(NSArray <ZegoUserSeatInfo *>*_Nullable)userSeatInfoList
robotSeatInfoList:(NSArray<ZegoRobotSeatInfo *> *_Nullable)robotSeatInfoList
         callBack:(IZegoStartGameCallBack _Nullable)callBack;

/// Start the game (Not all robots)
///
/// Available since: 1.0.0 and above.
/// Description: Start the game --- the host plays with the mode (ZegoGameModeHostsGame), no need to call it in the normal field (it can include robots)
/// When to call: After calling the [init] method,
/// Caution: userSeatInfoList cannot be empty
///
/// @param gameConfig Game configuration items, such as: tax rate, timeout. . .
/// @param userSeatInfoList Game player seat information (must have a value, not all robots).
/// @param robotSeatInfoList Robot Player Seat Information.
/// @param callBack Method execution result callback.
- (void)startGame:(ZegoStartGameConfig *_Nullable)gameConfig
 userSeatInfoList:(NSArray <ZegoUserSeatInfo *>*_Nullable)userSeatInfoList
robotSeatInfoList:(NSArray<ZegoRobotSeatInfo *> *_Nullable)robotSeatInfoList
         callBack:(IZegoStartGameCallBack _Nullable)callBack;

/// Unload game
///
/// Available since: 1.0.0 and above.
/// Description: Unloading the game will not affect the continued game of other players.
/// When to call: After calling the [loadGame] method.
/// Caution: None
///
/// @param forceQuit  When forceQuit is true, force quit, which is equivalent to disconnection. When forceQuit is false, the game will voluntarily exit, receive the [onUnloaded: ]event notification, and close successfully.
- (void)unloadGame:(BOOL)forceQuit;

- (void)refreshGamePoint;

/// Refresh microphone and speaker status.
///
/// Available since: 1.3.0 and above.
/// Description: Audio game, the notification game informs the current user about the microphone and speaker status of all players (e.g., when the current user disconnects and needs to know the status of other players).
/// When to call: After calling the [loadGame] method.
/// Caution: None
- (void)refreshMicAndSpeakerState;

/// Set in-game sound effects on/off
///
/// Available since: 1.0.0 and above.
/// Description: Set in-game sound effects on/off
/// When to call: After receiving the [onGameLoadStateUpdate] event callback, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param mute  true means turning off the game music, false means turning on the game music.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)muteGameMusic:(BOOL)mute;

/// Get the current status of the game music switch.
///
/// Available since: 1.0.0 and above.
/// Description: Get the current game music switch status.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameMusicSwitch:(IZegoCommonCallBack _Nullable )callBack;

/// Turn on/off game sound effects.
///
/// Available since: 1.0.0 and above.
/// Description: Turn on/off game sound effects.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param mute  true means turning off the game music, false means turning on the game music.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)muteGameSoundEffect:(BOOL)mute;

/// get the volume of the game sound effect.
///
/// Available since: 1.0.0 and above.
/// Description: get the volume of the game sound effect.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameSoundEffectSwitch:(IZegoCommonCallBack _Nullable )callBack;

/// Set the on/off of game vibration.
///
/// Available since: 1.0.0 and above.
/// Description: Enable/disable game vibration.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param isVibrate  true is for enabling game vibration, false is for disabling game vibration.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)enableGameVibrate:(BOOL)isVibrate;

/// Get the switch status of game vibration.
///
/// Available since: 1.0.0 and above.
/// Description: Get the switch status of game vibration.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameVibrateSwitch:(IZegoCommonCallBack _Nullable )callBack;

/// Set the volume of the game music.
///
/// Available since: 1.0.0 and above.
/// Description:Set the volume of the game music while the game is in progress
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param volume Volume value, value range: 0 - 100
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)setGameMusicVolume:(int)volume;

/// Get the volume of game music
///
/// Available since: 1.0.0 and above.
/// Description:Get the volume of game music，value range: 0 - 100
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameMusicVolume:(IZegoCommonCallBack _Nullable )callBack;

/// Set the volume of the game sound effect.
///
/// Available since: 1.0.0 and above.
/// Description:Set the volume of the game sound effect，value range: 0 - 100
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param volume Volume value, value range: 0 - 100
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)setGameSoundEffectVolume:(int)volume;

/// Get the volume of  game sound effect
///
/// Available since: 1.0.0 and above.
/// Description: Get the volume of  game sound effect，value range: 0 - 100
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameSoundEffectVolume:(IZegoCommonCallBack _Nullable )callBack;

/// Get a list of components
///
/// Available since: 1.0.0 and above.
/// Description: Get a list of components that the current game can control (show / hide).
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameComponentList:(IZegoCommonCallBack _Nullable)callBack;

/// Set the game control to show / hide.
///
/// Available since: 1.0.0 and above.
/// Description: Set the game control to show / hide.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param componentName  The name of the game component.
/// @param isVisible  True is displayed, false is hidden.
/// @param callBack  Method execution result callback.
- (int)setGameComponent:(NSString *_Nullable)componentName isVisible:(BOOL)isVisible callBack:(IZegoCommonCallBack _Nullable)callBack;

/// Get the list of methods that the current game can run
///
/// Available since: 1.0.0 and above.
/// Description: Get the list of methods that the current game can run (the result information of [getGameFunctionList] is used in conjunction with [runGameFunction])
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)getGameFunctionList:(IZegoCommonCallBack _Nullable)callBack;

/// Perform the methods in the game.
///
/// Available since: 1.0.0 and above.
/// Description: Perform the methods in the game.
/// When to call: After receiving the callback from the [onGameLoadStateUpdate] event, it is known that the gameLoadState is ZegoGameLoaded.
/// Caution: None
///
/// @param functionName  The name of the game method. Corresponds to the name in the data [ZegoGameFunction] returned by [getGameFunctiontList].
/// @param callBack  Method execution result callback.
/// @return ZegoMiniGameEngineSuccess or ZegoGameEngineErrorGameIsNotRunning
- (int)runGameFunction:(NSString * _Nonnull)functionName callBack:(IZegoCommonCallBack _Nonnull)callBack;

/// PreLoad Game
///
/// Available since: 1.5.0 and above.
/// Description: Preloading Game
/// When to call: After calling the [init] method, before the [onUnloadGame] callback method
/// Caution: None
///
/// @param gameID game ID
/// @param callBack Method execution result callback.
- (void)preLoadGame:(NSString * _Nonnull)gameID callBack:(IZegoPreLoadCallBack _Nullable)callBack;

/// unPreLoad Game
///
/// Available since: 1.5.1 and above.
/// Description: cancel preloading Game
/// When to call: After calling the [preLoadGame] method, before the [onUnloadGame] callback method
/// Caution: None
///
/// @param gameID game ID
- (void)unPreloadGame:(NSString * _Nonnull)gameID;

/// Clear Game Resources
///
/// Available since: 1.5.1 and above.
/// Description: Clear Game Resources
/// When to call: After calling the [onUnloadGame] method
/// Caution: None
///
/// @param gameID game ID
- (void)clearGameResources:(NSString * _Nonnull)gameID;
@end
