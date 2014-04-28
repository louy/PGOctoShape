#import <Foundation/Foundation.h>
#import "OCTimeInfoEvent.h"
#import <stdint.h>
 
/**
 * Time info from the Octoshape client for live streams.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 */
@interface OCTimeInfoLiveEvent : OCTimeInfoEvent
	
/** The octotime of the most recent data packet send to the player which is also a start point/key frame. */
@property(readonly) int64_t lastFrame;
		
/** The maximal time stamp which can, at this moment, be played when 
 * playing live data. 
 * <p>Typically, a live stream will play longer back 
 * 	than this since we always start playing on a frame. 
 * </p>
 */
@property(readonly) int64_t maxLive;
		
/** 
 * The octotime of the most recently downloaded data or -1 if the information is unavailable. 
 */
@property(readonly) int64_t currentdownloaded;

@end