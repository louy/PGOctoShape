#import <Foundation/Foundation.h>
#import "OCTimeInfoEvent.h"
#import <stdint.h>
	
/**
 * Time info from the Octoshape client for VOD.
 *
 * <p>This event can be triggered by <code>OCStreamPlayer</code>.</p>
 */	  
@interface OCTimeInfoOnDemandEvent : OCTimeInfoEvent

/**
 * The octotime of the beginning of the file.
 */
@property(readonly) int64_t startTime;

/**
 * The octotime of the end of the file.
 */
@property(readonly) int64_t endTime;

/**
 * The permil offset in the file of what is being played right now.
 */	 	
@property(readonly) int64_t promilleOffset;

/**
 * The amount of bytes that where skipped by the seek command.
 */
@property(readonly) int64_t skippedBytes;

/**
 * The amount of bytes the client has sent to the player so far.
 */
@property(readonly) int64_t mediaIndex;

/**
 * The size of the actual media content in an on-demand file, in bytes.
 */
@property(readonly) int64_t mediaSize;

/**
 * The size of the file if we are playing an on-demand file.
 */
@property(readonly) int64_t fileSize;

/**
 * The amount of bytes the client has sent to the player so far, including metadata.
 */
@property(readonly) int64_t byteOffset;

/**
 * The header size.
 */
@property(readonly) int64_t headerSize;

/**
 * The number of written bytes.
 */
@property(readonly) int64_t writtenBytes;
	
@end