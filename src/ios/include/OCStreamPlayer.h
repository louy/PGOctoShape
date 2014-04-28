#import <Foundation/Foundation.h>
#import "OCAuthentication.h"
#import "OCAuthenticationEvent.h"
#import "OCEvent.h"
#import "OCEventTypes.h"
#import "OCSeekTypeInfoEvent.h"
#import <stdint.h>

@class OCOctoshapeSystem;

/**
 * Controls retrieval and playback for one particular stream.
 * <p>
 * Implementations of this interface can be retrieved from
 * <see cref="OCOctoshapeSystem::createStreamPlayer:"/>.
 * </p>
 * <p>
 * After creating the object, you should install observers for any notifications/events
 * you need to react to. At a minimum this ought to include
 * <see cref="OCSeekTypeInfoEvent"/>, <see cref="OCUrlEvent"/>, and
 * <see cref="OCProblemEvent"/>.
 * </p>
 * <p>
 * After setting up observers, you can call one of the <see cref="play"/> methods to
 * start streaming, or <see cref="initialize:"/> to retrieve information about the
 * stream without retrieving the stream itself.
 * </p>
 * <p>
 * At any point in time the <see cref="OCStreamPlayer"/> object is on one of the
 * states described by the <see cref="StreamPlayerStatus"/> enumeration.
 * </p>
 *
 * <p>This class can generate the following events:
 * <code>OCAuthenticationEvent</code>,
 * <code>OCCurrentStreamInfoEvent</code>,
 * <code>OCDurationChangedEvent</code>,
 * <code>OCMultiStreamInfoEvent</code>,
 * <code>OCProblemEvent</code>,
 * <code>OCSeekTypeInfoEvent</code>,
 * <code>OCStatusUpdateEvent</code>,
 * <code>OCStreamConfigEvent</code>,
 * <code>OCTimeInfoEvent</code>,
 * <code>OCTimeInfoLiveEvent</code>,
 * <code>OCTimeInfoOnDemandEvent</code>,
 * <code>OCUMetaEvent</code>,
 * <code>OCUrlEvent</code>.
 *
 * </p>
 */
@interface OCStreamPlayer : NSObject

/**
 * The octolink this object was created with.
 */
@property (retain, nonatomic, readonly) NSString* octolink;

/**
 * If this property is true then the <code>OCStreamPlayer</code> ensures that an <code>OCTimeInfoEvent</code>
 * is sent on every key frame.
 *
 * @see OCTimeInfoEvent
 */
@property (nonatomic) BOOL timeInfoOnEveryKeyFrame;

/**
 * Enumeration defining states of <see cref="OCStreamPlayer"/> objects.
 *
 * <p> <code>uninitialized</code> -  Not initialized.
 * Either the <see cref="initialize:"/> method has never been called, or some problem occurred. </p>
 * <p> <code>initializing</code> - Currently initializing. </p>
 * <p> <code>ready</code> - Initialized, but not asked to play yet.
 * Calling one of the <see cref="play"/> methods should fairly quickly result in call
 * to the observer of <see cref="OCUrlEvent"/></p>
 * <p> <code>playInitializing</code> - Preparing to play.
 * A <see cref="play"/> method has been called,	but the request has not resulted in a
 * media player URL	(or a problem) yet. </p>
 * <p> <code>playing</code> - Currently playing.
 * The <see cref="OCStreamPlayer"/> has reported a media player URL to be played via
 * the observer of <see cref="OCUrlEvent"/>. In this state it is expected that the app
 * will be streaming data.</p>
 * <p> <code>closed</code> -  Closed and deallocated.
 * The <see cref="close"/> method have been called, which means that this object cannot
 * be used again.</p>
 *
 * @see OCStreamPlayer:status.
 */
typedef enum {uninitialized, initializing, ready, playInitializing, playing, closed} StreamPlayerStatus;

/**
 * Begin initialization of the stream player without actually playing just yet.
 * <p>
 *  Any observers you need to register should be registered before calling this method.
 * </p>
 * <p>
 * If the stream player is already initialized, or currently in the process of
 * initializing, calling this method has no effect. Otherwise the status will go to
 * <code>initializing</code> and finally to <code>ready</code>.
 * </p>
 * <p>
 * 	NB: Currently there may be some special cases where setting <code>getEarlyInfo</code>
 * 	to true has no effect, such that the information will only be ready after a request
 * 	to play has been made. This is currently the case for on-demand files that are stored
 * 	on the Octoshape servers in FLV format.
 * </p>
 * <p>
 * Calling any of the <see cref="play"/> methods will implicitly initialize the stream
 * player object (with <code>getEarlyInfo</code> set to false) if this method has not yet
 * been called.
 * </p>
 * <p>
 * Beware that the initialization cannot complete until <see cref="OCOctoshapeSystem::open"/>
 * is called. It is permitted to call this method before <see cref="OCOctoshapeSystem::open"/>,
 * but the object can only move out of the <code>initializing</code> state after
 * <see cref="OCOctoshapeSystem::open"/> is called.
 * </p>
 *
 * @param getEarlyInfo Set this to true to indicates that stream information that is
 * normally only available	after beginning to play the stream should be retrieved
 * already during the initialization phase. This entails a slight additional overhead.
 * If this is false, most information about the stream will be retrieved only right
 * before the stream player	begins to play for the first time, i.e., after calling one
 * of the play methods, but just before the URL callback is called.
 *
 */
-(void) initialize:(BOOL)getEarlyInfo;

/**
 * Start playing the stream.
 * <p>
 * This method returns nothing; the playback is started asynchronously. The caller can
 * expect that either the observer for <see cref="OCUrlEvent"/> or the observer for
 * <see cref="OCProblemEvent"/> will eventually be called to indicate success or
 * failure.
 * </p>
 * <p>
 * This method starts streaming data "in the ordinary way". For on-demand streams, this
 * means to play the stream from the beginning. For live streams, the stream will play
 * the most recent data the Octoshape system can provide.
 * </p>
 * <p>
 * In order to start at other positions in the stream, see
 * <see cref="playLiveTimePosition:"/> and <see cref="playLiveWithLatency:"/>
 * for live streams, or <see cref="playOnDemandTimePosition:"/>,
 * <see cref="playOnDemandMediaTimePosition:"/>, and
 * <see cref="playOnDemandPermilPosition:"/> for on-demand streams.
 * </p>
 * <p>
 * Calling this method will initialize the stream player, if that has not already been
 * done. If the stream player is currently initializing, the play request will be sent as
 * soon as the initialization ends.
 * </p>
 *
 * @see OCStreamPlayer#initialize:
 */
-(void) play;


/**
 * Start playing the stream with a given extra latency.
 * <p>
 * This method returns nothing; the playback is started asynchronously. The caller can
 * expect that either the observer for <see cref="OCUrlEvent"/> or the observer for
 * <see cref="OCProblemEvent"/> will eventually be called to indicate success or
 * failure.
 * </p>
 * <p>
 * This method starts streaming data from point the indicated amount of time in the past,
 * provided that sufficiently long DVR has been set up for the stream in the Octoshape
 * server complex.
 * </p>
 * <p>
 * This is the same as <see cref="playLiveTimePosition:"/>, except that the starting
 * position is specified by the amount of time delay rather than at an absolute past
 * timestamp.
 * </p>
 * <p>
 * Note that the latency parameter is IN ADDITION to the default distribution latency set
 * up for the stream in the Octoshape server complexes, so there is no exact way for the
 * user of the libary to know which <see cref="playLiveTimePosition:"/> timestamp
 * corresponds to a given amount of extra latency or vice versa.
 * </p>
 * <p>
 * Calling this method will initialize the stream player, if that has not already been
 * done. If the stream player is currently initializing, the play request will be sent as
 * soon as the initialization ends.
 * </p>
 * <p>
 * Note that before to call this method it's necessary to stop the Media Player first, and then resume it again
 * once the new m3u8 playlist has been received from the backend through <see cref="OCUrlEvent"/>.
 * </p>
 *
 * @param latency  The extra latency in milliseconds.
 *
 * @see OCStreamPlayer#initialize:
 */
-(void) playLiveWithLatency:(int64_t)latency;

/**
 * Start playing the stream at a given position.
 * <p>
 * This method returns nothing; the playback is started asynchronously. The caller can
 * expect that either the observer for <see cref="OCUrlEvent"/> or the observer for
 * <see cref="OCProblemEvent"/> will eventually be called to indicate success or
 * failure.
 * </p>
 * <p>
 * This method starts streaming data from a specified point in the past, provided that
 * sufficiently long DVR has been set up for the stream in the Octoshape server complex.
 * </p>
 * <p>
 * This is the same as <see cref="playLiveWithLatency:"/>, except that the starting
 * position is specified as an absolute point in time rather than so-and-so long time ago.
 * </p>
 * <p>
 * Calling this method will initialize the stream player, if that has not already been
 * done. If the stream player is currently initializing, the play request will be sent as
 * soon as the initialization ends.
 * </p>
 *
 * @param startPosition The start position in milliseconds since the beginning of 1970,
 * UTC.
 *
 * @see OCStreamPlayer#initialize:
 */
-(void) playLiveTimePosition:(int64_t)startPosition;

/**
 * Start playing at a given original timestamp.
 * <p>
 * This method returns nothing; the playback is started asynchronously. The caller can
 * expect that either the observer for <see cref="OCUrlEvent"/> or the observer for
 * <see cref="OCProblemEvent"/> will eventually be called to indicate success or
 * failure.
 * </p>
 * <p>
 * This method starts streaming data from a point in an on-demand stream, expressed as
 * the absolute point in time when the on-demand data were captured from a live source.
 * </p>
 * <p>
 * This only makes sense for some types of on-demand stream, and (of course) only when
 * the Octoshape servers have information about when the stream was captured. Contact
 * Octoshape for details before you use this option.
 * </p>
 * <p>
 * For other ways to specify the starting position in an on-demand stream, see
 * <see cref="playOnDemandMediaTimePosition:"/> and
 * <see cref="playOnDemandPermilPosition:"/>.
 * </p>
 * <p>
 * Calling this method will initialize the stream player, if that has not already been
 * done. If the stream player is currently initializing, the play request will be sent
 * as soon as the initialization ends.
 * </p>
 *
 * @param startPosition The start position in OctoTime.
 *
 * @see OCStreamPlayer#initialize:
 */
-(void) playOnDemandTimePosition:(int64_t)startPosition;

/**
 * Start playing at a given media time position.
 * <p>
 * This method returns nothing; the playback is started asynchronously. The caller can
 * expect that either the observer for <see cref="OCUrlEvent"/> or the observer for
 * <see cref="OCProblemEvent"/> will eventually be called to indicate success or
 * failure.
 * </p>
 * <p>
 * This method starts streaming data from a point in an on-demand stream expressed as a
 * certain amount of time after the beginning of the stream.
 * </p>
 * <p>
 * For other ways to specify the starting position in an on-demand stream, see
 * <see cref="playOnDemandTimePosition:"/> and
 * <see cref="playOnDemandPermilPosition:"/>.
 * </p>
 * <p>
 * Calling this method will initialize the stream player, if that has not already been
 * done. If the stream player is currently initializing, the play request will be sent
 * as soon as the initialization ends.
 * </p>
 *
 * @param startPosition Time relative to start of stream in milliseconds.
 *
 * @see OCStreamPlayer#initialize:
 */
-(void) playOnDemandMediaTimePosition:(int64_t)startPosition;

/**
 * Start playing at a given fractional position.
 * <p>
 * This method returns nothing; the playback is started asynchronously. The caller can
 * expect that either the observer for <see cref="OCUrlEvent"/> or the observer for
 * <see cref="OCProblemEvent"/> will eventually be called to indicate success or
 * failure.
 * </p>
 * <p>
 * This method starts streaming data from a point in an on-demand stream expressed as a
 * fraction of the entire duration of the stream.
 * </p>
 * <p>
 * For other ways to specify the starting position in an on-demand stream,
 * see <see cref="playOnDemandTimePosition:"/> and
 * <see cref="playOnDemandMediaTimePosition:"/>.
 * </p>
 * <p>
 * Calling this method will initialize the stream player, if that has not already been
 * done. If the stream player is currently initializing, the play request will be sent as
 * soon as the initialization ends.
 * </p>
 *
 * @param permilPosition The position as a value from 0 to 1000.
 *
 * @see OCStreamPlayer#initialize:
 */
-(void) playOnDemandPermilPosition:(int)permilPosition;

/**
 * Abort the current play session.
 * <p>
 * This method causes the <see cref="OCStreamPlayer"> to stop fetching media data from
 * the network and sending them to the media player. Streaming can be resumed later by
 * calling one of the <see cref="play"/> methods.
 * </p>
 * <p>
 * Calling this method will generate a {'userstop', 'normal'} problem event, unless
 * another play method is called immediately (or at least before the current play session
 * is finished).
 * </p>
 * <p>
 * Playback of this stream will be implicitly aborted if you call <see cref="play"/> on
 * this or a different StreamType object, so there is no need to call
 * <see cref="abortPlayback"/> explicitly simply to switch between streams or to move to
 * a different position in the current stream.
 * </p>
 * <p>
 * (This automatic abort can be suppressed by using special options in the octolinks used
 * to create the <see cref="OCStreamPlayer"/>s, but this is not covered by this
 * documentation).
 * </p>
 */
-(void) abortPlayback;

/**
 * Request an <code>OCTimeInfoEvent</code> for the currently playing stream.
 * <p>
 * If we are not currently playing, then calling this will have no effect.
 * Otherwise <code>OCTimeInfoEvent</code> will be sent one time, when the
 * information is ready.
 * </p>
 * 
 * @see OCTimeInfoEvent
 */
-(void) getTimeInfo;

/**
 * Closes and discards the <see cref="OCStreamPlayer"/>.
 * 
 * <p>
 * This method destroys the <see cref="OCStreamPlayer"/> and releases all resources
 * the library has allocated in connection with it, including caches of
 * data that are being kept in anticipation of a future play session.
 * </p>
 * <p>
 * After this method has been called, the effect of calling any other
 * methods on the <see cref="OCStreamPlayer"/> object is undefined and unpredictable.
 * </p>
 * <p>
 * Beware that it is possible to receive callbacks after this method
 * has been called; it does NOT block until all the library's internal
 * worker threads have been notified about the closure.
 * </p>
 * <p>
 * Beware also that in the current release of the SDK, callbacks
 * set in a <see cref="OCStreamPlayer"/> object will NEVER be deallocated even if the
 * <see cref="OCStreamPlayer"/> is explicitly closed. We hope to fix this in a later
 * release, but for the time being user code that opens and closes
 * StreamPlayers many times over an the lifetime of the application process
 * should take its own measures to limit the effects of this memory
 * leak (such as protecting references from the callback object to
 * other objects in the application using weak references, or explicitly
 * zeroing them out when you close the <see cref="OCStreamPlayer"/>).
 * </p>
 */
-(void) close;

/**
 * A callback that receives requests for authentication of users.
 * 
 * <p>
 * Set this callback if (and only if) the stream you're playing is
 * one that is configured in the server complex to require "ticket"
 * authorization of users.
 * </p>
 * <p>
 * If the callback is set, it will be called as part of the stream
 * or play initialization with a request to produce an authorization
 * ticket.
 * </p>
 * <p>
 * After the callback is called, it is up to the user code to procure
 * appropriate credentials for playing the stream in a way decided by
 * the broadcaster. Once this has happened, it must call the
 * <see cref="setAuthentication:"/> method to deliver the credentials.
 * If the application fails to obtain credentials, it is responsible for
 * canceling the playback instead of calling <see cref="setAuthentication:"/>.
 * </p>
 * <p>
 * Unfortunately there is currently no way for the application to ask whether
 * a given stream requires authorization or not; that has to be
 * communicated through other means.
 * </p>
 * <p>
 * Setting the callback is relatively harmless if the stream happens
 * not to require authorization. The application will still be asked to produce
 * authorization credentials, and must still call <see cref="setAuthentication:"/>,
 * but any authHash will be accepted.	  
 * </p>
 *
 * @param listener The listener.
 * @param queue The <code>NSOperationQueue</code> the listener will be added to.
 * @see OCAuthenticationEvent
 */
-(void) setAutheticationEventListener:(void (^)(OCAuthenticationEvent*, OCStreamPlayer*))listener queue:(NSOperationQueue *)queue;

/**
 * Removes the authentication listener.
 * 
 * <p>
 * Call this method if the authentication event listener is no more needed. Calling
 * this method even though no listener has been registered before will not cause
 * any side effect.
 * <p>
 */
-(void) removeAutheticationEventListener;

/**
 * Install obtained authentication credentials.
 *
 * <p>
 * This method should be called in response to a
 * <see cref="setAutheticationEventListener"/> registered callback if the user code
 * manages to produce appropriate credentials for playing. The
 * Octoshape library will check that the provided credentials
 * are valid; if they are not, a suitable <see cref="OCProblemEvent"/>
 * will be reported.
 * </p>
 * <p>
 * The precise format of the credentials is not documented here;
 * typically the application will get them wholesale from a server run by
 * the content provider using a protocol not specified by Octoshape.
 * </p>
 *
 * @param authentication The authentication that has been obtained.
 */
-(void) setAuthentication:(OCAuthentication*)authentication;

@end