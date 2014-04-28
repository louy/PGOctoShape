#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import <stdint.h>
	
/**
 * Contains information about how to seek in the stream.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 */
@interface OCSeekTypeInfoEvent : OCEvent
		
/**
 * Describes the seek methods available.
 
 * <p> <code>nativeSeek</code> means that is it possible to use the selected media player's own method of seeking. </p>
 * <p> <code>osaSeek</code> means that the stream is seekable using the <code>play...</code> methods in <see cref="OCStreamPlayer"/>. </p>
 * <p> <code>none</code> means it is not possible to seek in the stream. </p>
 */
typedef enum {none, osaSeek, nativeSeek} SeekType;
	
/**
 * The selected seek method.
 */
@property(readonly) SeekType seekType;
	
/**
 * <code>True</code> if the stream is a live stream; <code>false</code> if it is an on-demand stream.
 */
@property(readonly) BOOL live;

/**
 * For an on-demand stream, this is the duration in milliseconds. For a live stream, this is the maximum DVR the stream is configured to have, or -1 if there is no DVR.
 */
@property(readonly) int64_t duration;
	
/**
 * The selected player id or <code>nil</code>
 */ 
@property(readonly) NSString* mediaPlayer;		

@end