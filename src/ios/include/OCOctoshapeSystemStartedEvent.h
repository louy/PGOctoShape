#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import <stdint.h>
	
/**
 * Event containing information about the port bound by the Octoshape client.
 * 
 * <p>This event can be triggered by <code>OCOctoshapeSystem</code>.</p>
 *
 */ 
@interface OCOctoshapeSystemsStartedEvent : OCEvent
	
/**
 * The authId The authId of the current Octoshape client launch, or <code>nil</code> if the the client is too old for reporting this.
 */ 
@property(readonly) NSString *authId;

@end