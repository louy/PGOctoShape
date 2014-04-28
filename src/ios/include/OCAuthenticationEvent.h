#import <Foundation/Foundation.h>
#import "OCEvent.h"
	   
/** 
 * Handles authentication of users by communication with a web server.
 * 
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 * @see OCAuthentication
 * @see OCStreamPlayer#setAuthentication:
 * @see OCStreamPlayer#setAutheticationEventListener:queue:
 * @see OCStreamPlayer#removeAutheticationEventListener
 */
@interface OCAuthenticationEvent : OCEvent
		
/**
 * Handles authentication of users by communication with a web server.
 *
 * <p>
 *  When this event is sent (by the Octoshape system) the <code>authId</code> element must be transfered  
 *  to the web server which performs the actual validation of the user. The web server reply must be packed into 
 *  an <code>OCAuthentication</code> object which is handed back to the Octoshape system
 *  by calling the the <code>OCStreamPlayer#setAuthentication:</code> on the appropriate 
 *  <code>OCStreamPlayer</code> object.
 * </p>
 *
 * @param authId is the string that should be authorized to view the stream.
 * Call <code>OCStreamPlayer#setAuthentication:</code> to set the authorization.
 * @see OCStreamPlayer#setAuthentication:
 */
@property (readonly) NSString* authId;		

@end