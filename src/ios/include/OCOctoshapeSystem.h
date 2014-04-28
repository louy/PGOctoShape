#import <Foundation/Foundation.h>
#import "OCStreamPlayer.h"

/**
 * Represents the Octoshape library at run time.
 * <p>
 * The program will contain exactly one instance of this interface after the
 * Octoshape library has been initialized. This instance is returned from the
 * <see cref="OCOctoStatic::createOctoshapeSystem:messageFilePath:"/>.
 * </p>
 * <p>
 * After initializing the libary we recommend that you install a listener for
 * problem notifications in the <see cref="OCProblemEvent"/> property. It is also
 * necessary to call <see cref="addPlayerName:andVersion:forKey:"/> to define an
 * available media player. After that, the <see cref="open"/> method must be called,
 * which will make the Octoshape library start it internal workings fully and begin
 * contacting the Octoshape servers.
 * </p>
 * <p>
 * It is possible to create and initialize <see cref="OCStreamPlayer"/> objects both
 * before and after calling <see cref="open"/>. If your app hardcodes a smallish
 * number of streams that it is able to play, we recommend creating
 * <see cref="OCStreamPlayer"/>s for them before <see cref="open"/> this will make
 * the initialization slightly more efficient because the library can start
 * handshaking with the Octoshape system about the streams immediately. (Of course,
 * media data will not be transfered until you actually start streaming).
 * </p>
 *
 * <p>This class can generate the following events:
 * <code>OCOctoshapeSystemsStartedEvent</code>,
 * <code>OCPortBoundEvent</code>,
 * <code>OCProblemEvent</code>.
 *
 */
@interface OCOctoshapeSystem : NSObject

- (NSString*) openHTTPTunnel:(NSString*) domains;

- (int) getHTTPTunnelTotalBytesReceived;

- (int) getHTTPTunnelSegmentBytesReceived;

- (void) resetHTTPTunnelCounters;

/**
 * Complete initialization of the Octoshape library.
 * <p>
 * The library will not try to communicate on the network before this method has been
 * called once. (Additional calls are no-ops).
 * </p>
 * <p>
 * All necessary calls to <see cref="addPlayerName:andVersion:forKey:"/> must have happened
 * before <see cref="open"/> is called.
 * </p>
 */
- (void) open;

/**
 * Suspends the <code>OCOctoshapeSystem</code>. To be called whenever the application which uses
 * this class has to go in any kind of suspend like state that forces any
 * kind of application sockets to shut down.
 * 
 * <p>This will cause the socket system to close all OS-level sockets. Listening TCP
 * sockets will be implicitly recreated when <code>resume</code> has been called - 
 * connections and everything UDP based will be killed, instead.</p>
 *
 * <p>Once <code>OCOctoshapeSystem</code> has been suspended, a <code>kOCSuspendedEvent</code>
 * will be generated.</p>
 * 
 */
- (void) suspend;

/**
 * Resumes the <code>OctoshapeSystem</code>, recreating any suspended socket via
 * <code>suspend</code> method.
 * 
 * <p>This method has to be called only if <code>suspend</code> has
 * been called earlier.</p>
 */
- (void) resume;

/**
 * Define media players that the user code supports.
 * <p>
 *  Use this method to tell the Octoshape library which media players
 *  (i.e. codec/rendering libraries) your app has available for rendering  the media data
 *  that the library will be fetching for you. The library uses this information to
 *  select between protocols for delivering the media data to the player, and between
 *  parameter sets for each protocol that we have found optimize the streaming experience
 *  for particular players.
 * </p>
 * <p>
 *   Currently this method is mostly a placeholder, since the present iOS build of the
 *   Octoshape SDK supports only two media players (see below). You're still required to
 *   call it, though, to maintain forward source compatibility with possible future
 *   releases that will support more players.
 * </p>
 * <p>
 *	Please use one of the <code>kOCMediaPlayer...</code> constants as name and set the
 *	version as described in the documentation of that constant. In case the media player
 *	you wish to use is not defined as one of the <code>kOCMediaPlayer...</code>
 *	constants, please contact Octoshape to find an appropriate value to use.
 *	(If only media players that are not known to the client are added, then the client
 *	will choose one in the list at random and set the
 *	<see cref="OCSeekTypeInfoEvent::mediaPlayer"/> property to that value.
 *	In this case osa-seek may or may not work correctly).
 * </p>
 * <p>
 *   The function can be called multiple times to supply a list of available players.
 *   All necessary calls to it should happen before the <see cref="open"/>" method is
 *   called.
 * </p>
 * <p>
 *  If more than one stream player type has been defined, the Octoshape library will
 *  select the one most suited to the stream being played, and report which one is to be
 *  used in the <see cref="OCSeekTypeInfoEvent::mediaPlayer"/>.
 * </p>
 *
 * @param key This identifier will be passed back as the playerId parameter to the
 * <see cref="OCSeekTypeInfoEvent"/> callback when the library decides that this player
 * is to be used.
 * @param name The name of the media player. May be one of the
 * <code>kOCMediaPlayer...</code> constants.
 * @param version The version of the media player.
 */
- (void) addPlayerName:(NSString*)name andVersion:(NSString*)version forKey:(NSString*)key;

/**
 * Constructs a new <code>OCStreamPlayer</code> object.
 * <p>
 * You can create a StreamPlayer before calling <see cref="open"/>, but remember that
 * your object will not actually be able to stream until <see cref="open"/> has been
 * called on the <see cref="OCOctoshapeSystem"/> object. Pre-creating
 * <see cref="OCStreamPlayer"/>s in this way may slightly improve the performance of
 * your app, though.
 * </p>
 * @param octoLink Identifies the stream to play in the Octoshape system. Usually this is
 * a string that begins with "octoshape://" and identifies the name the stream is set up
 * with in the Octoshape server complex. The link string may contain additional
 * parameters that modify how the stream is fetched and/or passed to the media player;
 * use these as directed by Octoshape or described in other documentation.
 */
- (OCStreamPlayer*) createStreamPlayer:(NSString*)octoLink;

/**
 * The Octoshape version identifier string for the iOS SDK.
 */
-(NSString*) version;

/**
 * The Octoshape version string with build info. 
 */
-(NSString*) buildVersionInfo;

/**
 * The platform identification encoded in base64.
 */
-(NSString*) platformIdentificationInBase64;

@end





