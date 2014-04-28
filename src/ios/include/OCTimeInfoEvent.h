#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import <stdint.h>

/**
 * Time info from the Octoshape client.
 *
 * <p>Note that OCTimeInfo events gives time information about when data have been
 * delivered from the client to the media player, not about when the media player actually
 * played some data.</p>
 *
 * <p> 
 * <b>About OctoTime:</b>
 * </p>
 *
 * <br/>  
 *
 * <p>Octoshape maintains a global time called the <i>octotime</i> throughout the whole 
 * streaming system. This time is also maintained on the client computers on which 
 * this code runs. The time is an approximate estimate of the number 
 * of UT1 milliseconds since 0:00 UTC on 1 January 1970. When live data enters 
 * the Octoshape system on the encoder, it is timestamped with the current octotime.
 * This timestamp is available on the client through this event.</p>
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *  	
 * @see OCStreamPlayer#getTimeInfo
 * @see OCStreamPlayer#getTimeInfoOnEveryFrame
 */ 
@interface OCTimeInfoEvent : OCEvent
	
/**
 * The octotime right now.
 */ 
@property(readonly) int64_t wallclock;
	
/**
 * The octotime of the most recent data packet sent to the player.
 */
@property(readonly) int64_t current;

@end