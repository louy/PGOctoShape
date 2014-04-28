#import <Foundation/Foundation.h>
	
/**
 * Base class for events from the Octoshape client.
 */
@interface OCEvent : NSObject
{
	@private
	NSDictionary* eventData;
	NSString* name;
}

/**
 * Initialize an instance of OCEvent using the value stored in a dictionary.
 *
 * @param name The notification name of the event.
 * @param data The data used to initialize this event.
 */	
-(id)initWithName:(NSString*)name andData:(NSDictionary*)data;
	
/**
 * The notification name of the event.
 * 
 * @see OCEventTypes.h
 */
@property(readonly) NSString* name;
	
@end