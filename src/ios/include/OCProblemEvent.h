#import <Foundation/Foundation.h>
#import "OCEvent.h"
	
/**
 * Indicates that a problem has occurred.
 * 
 * <p>This event can be triggered by <code>OCStreamPlayer</code> and <code>OCOctoshapeSystem</code>.</p>
 *
 * <p>Note that this object has the <code>message</code> property which is already an
 * appropriate text message to show to the user based on the problem itself.</p>
 */ 
@interface OCProblemEvent : OCEvent

 /**
  * <p>This returns a recommended English message to show to the user in case <code>isNormal</code> returns <code>NO</code>.
  * If isNormal returns true, it returns null.</p>
  * <p>In the current SDK this is implemented as follows:</p>
<pre>
if ([problem isNormal]) {
    return nil;
}
if ([problem hasId:@"admin"]) {
    if([problem hasId:@"geofilter"]) {
        return [NSString stringWithFormat:@"This stream is not allowed to be viewed in your area (%%d)", problem.errorCode];
    } else {
        return [NSString stringWithFormat:@"You do not have permission to view this stream (%%d)", problem.errorCode];
    }
} else {
    return [NSString stringWithFormat:@"This stream is currently unavailable (%%d)", problem.errorCode];
}
</pre> 
	 */
@property(readonly) NSString* message;
		
/**
 * This is the Octoshape error code for this problem. The error code will normally be 
 * 2-4 decimal digits. Please always include this error code in decimal format when notifying 
 * the user about the problem as this may simplify debugging and user support allot. 
 * Also, please do not write program logic that depends on error codes as error codes may 
 * change between releases of Octoshape software.
 */
@property(readonly) int errorCode;

/**
 *  This can be used to probe about the nature of the problem. 
 *  Here are the things that can be detected from this:
 *  <ul>
 *  <li><strong>IF</strong> this problem has <code>geofilter</code> as problem id, it means that the stream cannot be played in the area the user is located in.</li>
 *	<li><strong>IF</strong> this problem has <code>admin</code> as problem id, it means that the user is not allowed to see this stream. In this case, an automatic retry to play should <strong>never</strong> be performed.</li>
 *  <li><strong>IF</strong> this problem has <code>tooold</code> as problem id, then <code>OCStreamPlayer#requestPlayLiveWithLatency</code> or <code>OCStreamPlayer#requestPlayLiveTimePosition</code>
 *  was used to play at an unavailable location</li>
 *  <li><strong>IF</strong> this problem has both <code>link</code> AND <code>notfound</code> as problem ids, it means that the stream that was tried to play did not exists.</li>
 *  </ul>
 *
 * @param problemId the id of the problem to check.
 *
 * @return <code>YES</code> if the problem contains the argument id 
 */
-(BOOL) hasId:(NSString*)problemId;

/**
 * Returns <code>YES</code> if there is not anything wrong and no error should be reported to the user. 
 * You may receive a problem with this message returning <code>YES</code> if stream stop was expected; 
 * see the <code>OCStreamPlayer</code>
 */
-(BOOL) isNormal;
	
@end