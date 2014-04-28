#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import "OCStreamPlayer.h"
	
/**
 * The status of the OCStreamPlayer changed.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *	
 */ 
@interface OCStatusUpdateEvent : OCEvent
		
/**
 * The new status.
 */
@property(readonly) StreamPlayerStatus newStatus;
		
/**
 * The old status.
 */
@property(readonly) StreamPlayerStatus oldStatus;
	
@end