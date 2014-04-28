#import <Foundation/Foundation.h>
#import "OCOctoshapeSystem.h"

/**
 * 	 Name constant for native iOS media player.
 * <p>
 *	Constant used as name argument to <see cref="OCOctoshapeSystem::addPlayerName:andVersion:forKey:"/>.
 *   The version of the player should be
 *   set to the iOS version <code>([[UIDevice currentDevice] systemVersion])</code>.
 * </p>
 */
static NSString* kOCMediaPlayerIosNative = @"iosmplayer";

/**
 *  Name constant for using a Shoutcast player on iOS.
 * <p>
 *	Constant used as name argument to <see cref="OCOctoshapeSystem::addPlayerName:andVersion:forKey:"/>.
 *	The version can be set to '1.0'.
 * </p>
 * <p>
 *	This player name should be added when using the Shoutcast player from the iOS SDK examples to play.
 *	In this case the 'version' should be '1.0'.
 * </p>
 */
static NSString* kOCMediaPlayerIosShoutcast = @"iosscplayer";


/**
 * Contains static methods to initialize the Octoshape library.
 */
@interface OCOctoStatic : NSObject

/**
 * Initializes the Octoshape libray.
 * <p>
 * Only the first call to this method does anyhting; subsequent calls will return the
 * <see cref="OCOctoshapeSystem"/> object already created and ignore their parameters.
 * </p>
 * <p>
 * This method initialializes the Octoshape libary to a point where you can start creating
 * <see cref="OCStreamPlayer"/> objects using the <see cref="OCOctoshapeSystem::createStreamPlayer:"/>
 * factory method. The library will not actually start communicating on the network
 * until you call its <see cref="OCOctoshapeSystem::open"/> method (but if you statically know the names of
 * the streams you will play, it is slightly more efficient to create the <see cref="OCStreamPlayer"/>s
 * before open than afterwards). You must also call <see cref="OCOctoshapeSystem::addPlayerName:andVersion:forKey:"/>
 * immediately after creating the <see cref="OCOctoshapeSystem"/>, in order to declare which media
 * players your app supports.
 * </p>
 *
 */
+(OCOctoshapeSystem*) createOctoshapeSystem;

/**
 * Enable log to console </summary>
 * <p>
 * This method should be called before <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
 * (What it really does is to preload values for some parameters to
 * the internal <see cref="OCOctoshapeSystem"/> constructor that are not used except
 * for debugging purposes).
 * </p>
 */
+(void) enableLogToConsole;

/**
 * Enable log to file </summary>
 * <p>
 * This method should be called before <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
 * (What it really does is to preload values for some parameters to
 * the internal <see cref="OCOctoshapeSystem"/> constructor that are not used except
 * for debugging purposes).
 * </p>
 */
+(void) enableLogToFile;


/**
* Enable log to server </summary>
* <p>
* This method should be called before <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
* (What it really does is to preload values for some parameters to
* the internal <see cref="OCOctoshapeSystem"/> constructor that are not used except
* for debugging purposes).
* </p>
*/
+(void) enableLogToServer;

/**
 * Specify the directory where the octoshape system writes its files.
 * <p>
 * If the given path is not absolute, it will interpreted as a
 * relative path wrt the local storage folder of the app.
 * </p>
 * <p>
 * This method should be called before <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
 * (What it really does is to preload values for some parameters to
 * the internal <see cref="OCOctoshapeSystem"/> constructor that are not used except
 * for debugging purposes).
 * </p>
 * @param directory The path to the octoshape directory.
 */
+(void) outputDirectory:(NSString*)directory;

/**
 * For internal Octoshape testing only!
 * <p>
 * Beware that this method may disappear or change without notice
 * in future versions of the SDK.
 * If used, this method should be called before <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
 * (What it really does is to preload values for some parameters to
 * the internal <see cref="OCOctoshapeSystem"/> constructor that are not used except
 * for internal debugging purposes).
 * </p>
 * @param logmode Controls the log configuration of the built-in SUA and
 * PM components; instead of the environment variable used on platforms
 * that have those.
 */
+(void) logMode:(NSString*)logmode;

#if 0

/**
 * For internal Octoshape testing only!
 * <p>
 * Beware that this method may disappear or change without notice
 * in future versions of the SDK.
 * If used, this method should be called before <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
 * (What it really does is to preload values for some parameters to
 * the internal <see cref="OCOctoshapeSystem"/> constructor that are not used except
 * for internal debugging purposes).
 * </p>
 * @param filename The absolute path of a file that low-level
 * console output and debugging traces should be written to.
 */
+(void) enableLowLevelLogging:(NSString*)filename;

#endif

@end
