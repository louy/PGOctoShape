//
//  PGOctoShape.h
//  Abu Dhabi TV
//
//  Created by Louy on ٢٦‏/٣‏/٢٠١٤.
//
//

#import <Cordova/CDV.h>
#import "OCAPI.h"
#import <MediaPlayer/MediaPlayer.h>

@interface PGOctoShape : CDVPlugin
{
    OCOctoshapeSystem *octoshapeSystem;
    OCStreamPlayer *streamPlayer;
    MPMoviePlayerViewController *movieController;
    NSString* callbackId;
}

- (void)init:(CDVInvokedUrlCommand*)command;
- (void)play:(CDVInvokedUrlCommand*)command;
- (void)stop:(CDVInvokedUrlCommand*)command;

- (void) onPause;
@end
