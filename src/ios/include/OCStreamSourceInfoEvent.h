#import <Foundation/Foundation.h>
#import "OCEvent.h"

/**
 * Stream source information from an OCStreamPlayer.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 */
@interface OCStreamSourceInfoEvent : OCEvent
		
/**
 * This will be set to "grid" or "unicast" depending on where we get the data from, or nil if unknown.
 */
@property(readonly) NSString* streamSource;
 	
/**
 * The current multicast status, or nil if unknown.
 */ 
@property(readonly) NSString* multiCastStatus;		

@end