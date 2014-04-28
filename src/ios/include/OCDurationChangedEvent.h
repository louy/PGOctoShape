#import <Foundation/Foundation.h>
#import "OCEvent.h"
#import <stdint.h>

/**
 * Resets an on-demand file duration previously reported in an OCSeekTypeInfoEvent.
 *
 * <p>
 * In very rare cases the file duration may be adjusted after an <see cref="OCSeekTypeInfoEvent"/> has been sent.
 * Currently the only situation this can happen in, is if the stream is a multi-stream, and
 * the contained base streams has not been encoded with exactly same length.
 * </p>
 * 
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 *
 */ 
@interface OCDurationChangedEvent : OCEvent
	
/**
 * Duration of VOD stream in milliseconds.
 */ 
@property(readonly) int64_t duration;

@end