#import <Foundation/Foundation.h>
#import "OCEvent.h"
	
/**
 * Contains information on how the stream is configured in the Octoshape system.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 * <p>This feature is currently only supported for live streams.</p>
 */
@interface OCStreamConfigEvent : OCEvent
		
 /**
  * The XML that this stream has been configured with.
  */
@property(readonly) NSString* configXml;		
	
@end