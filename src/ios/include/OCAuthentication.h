#import <Foundation/Foundation.h>

/**
 * Obtained authentication that should be given to the Octoshape system.
 * 
 * @see OCAuthenticationEvent
 * @see OCStreamPlayer#setAuthentication:
 */ 
@interface OCAuthentication : NSObject
	
/**
 *  A string with information about the type of authentication
 *  to be used. It must be a comma separated list of key-value pairs.
 *  <dl>
 *    	<dt>Currently the following keys are defined:</dt>
 *    	<dd> 
 *			<dl>
 *      		<dt><code>hardexpire</code></dt>
 * 				<dd>If set, it must be set to a number of UT1 milliseconds since 0:00 UTC on 1 January 1970
 *      		     where this certificate expires. If not set, the certificate will never expire.
 *      		     The client MAY be thrown off during playing when this expires. In the future it
 *      		     will probably always be kicked off while it currently sometimes will and sometimes
 *      		     will not.
 *     	 		 </dd>
 *     	 		 <dt><code>softexpire</code></dt>
 *     	 		 <dd>As hardexpire except that a playing client will never be kicked off if the
 *       		    certificate expires while playing. A hacker will currently rather easily be 
 *       		    able to hack softexpire but will not be able to hack hardexpire equally easy.
 *       		</dd>
 *       		<dt><code>useauthid</code></dt>
 *       		<dd>See the <code>#hash</code> property. The value is true by default.
 *       		</dd>
 *       		<dt><code>user</code></dt>
 *       		<dd>This can be set to some id identifying the user. Is currently only used 
 *					by the Octoshape servers and only in log files
 *      		</dd>
 *    		</dl>
 *		</dd>
 *	</dl>
 */

@property(retain, nonatomic) NSString* info;
	
/**
 * The md5 sum of the utf-8 encoding of the string
 *    <code>password,authid,authinfo</code>
 *    or if <code>useauthid</code> is false in the <code>authInfo</code> argument, the string
 *      <code>password,authinfo</code>
 *    <dl>
 *       <dt>where:</dt>
 *		<dd>    
 *    <dl>
 *       <dt><code>password</code></dt>
 *       <dd>Is the password setup for this stream on the Octoshape streaming
 *           servers</dd>
 *       <dt><code>authid</code></dt>
 *       <dd>Is the value of the <code>authid</code> property in the 
 *           <code>OCAuthenticationEvent</code> that triggered getting this authentication.
 *       </dd>
 *       <dt><code>authinfo</code></dt>
 *       <dd>Is the content of the <code>info</code> parameter.</dd>
 *    </dl>
 * </dd>
 * </dl>	 	
 */ 
@property(retain, nonatomic) NSString* hash;

@end