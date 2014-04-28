#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import <stdint.h>
	
/**
 * Event containing information about the currently playing base stream.
 *
 * <p>
 * Listening for this information might be especially useful when playing a multistream, as this will 
 * then identify the base stream currently playing. 
 * Note that this event may be sent with nil and -1 values when the current stream is about to, or has stopped playing
 * (e.g., if a new play request call is made).  
 * </p>
 * 
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 */ 
@interface OCCurrentStreamInfoEvent : OCEvent
	
/**
 * An Octoshape base stream name, or <code>nil</code> if no stream is currently playing.
 */
@property(readonly) NSString* streamName;
	
/**
 * The bitrate this base stream is configured to have, or <code>-1</code> if unknown.
 */ 
@property(readonly) int64_t rateset;

@end