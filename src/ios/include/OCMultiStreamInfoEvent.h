#import <Foundation/Foundation.h>
#import "OCEvent.h"
	
/**
 * Information on how the multi-stream is configured in the Octoshape system. 	 
 *
 * 
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 * <p>
 * This event is only sent if the stream is a multi-stream. 
 * </p>
 */
@interface OCMultiStreamInfoEvent : OCEvent
	
/** 		
 * A NSArray containing a NSDictionary for each base stream in the multi-stream.
 * The name of the base stream is stored under the <code>name</code> key.  
 * The bitrate of the base stream is stored under the <code>bitrate</code> key. 
 */
@property(readonly) NSArray* baseStreams;

@end