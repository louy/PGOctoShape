#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import <stdint.h>
	
/**
 * Event containing information about the port bound by the Octoshape client. This event
 * should not be listened at all in normal circumstances.
 * 
 * <p>This event can be triggered by <code>OCOctoshapeSystem</code>.</p>
 *
 */ 
@interface OCPortBoundEvent : OCEvent
	
/**
 * The port where the Octoshape client has been bound.
 */ 
@property(readonly) int port;

@end