#import <Foundation/Foundation.h>
#import "OCEvent.h"

/**
 * Octoshape u-meta data for the currently playing stream.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>	 
 */
@interface OCUMetaEvent : OCEvent		

/**
 * XML string or <code>nil</code>.
 */
@property(readonly) NSString* xmlString;

/**
 * U-meta type string or <code>nil</code>.
 */
@property(readonly) NSString* uMetaType;

/**
 * client version or <code>nil</code>.
 */	
@property(readonly) NSString* version;

/**
 * the branch client binary was built from or <code>nil</code>.
 */	
@property(readonly) NSString* branch;

/**
 * client variant or <code>nil</code>.
 */	
@property(readonly) NSString* variant;

/**
 * The clients TempId or <code>nil</code>.
 */	
@property(readonly) NSString* tempId;

/**
 * The authuniq of the currently played stream or <code>nil</code>.
 */	
@property(readonly) NSString* authUnique;

/**
 * The clients platform or <code>nil</code>.
 */	
@property(readonly) NSString* platform;

@end