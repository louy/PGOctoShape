//
//  PGOctoShape.m
//  Abu Dhabi TV
//
//  Created by Louy on ٢٦‏/٣‏/٢٠١٤.
//
//

#import "PGOctoShape.h"

#import <MediaPlayer/MediaPlayer.h>
#import <Cordova/CDV.h>
#import "OCAPI.h"

@implementation PGOctoShape

- (void)init:(CDVInvokedUrlCommand*)command {
    callbackId = command.callbackId;
//    [self sendUpdate:@{@"type":@"ready"}];
}
- (void)play:(CDVInvokedUrlCommand*)command {
    NSString* link = [command argumentAtIndex:0];
    [self initStreamPlayerWithLink:link];
}
- (void)stop:(CDVInvokedUrlCommand*)command {
    if( [self closePlayer] ) {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK] callbackId:command.callbackId];
        return;
    }
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
}

- (void)pluginInitialize {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onPause) name:UIApplicationDidEnterBackgroundNotification object:nil];
    [self initTheOctoShapeSystem];
}

- (BOOL) closePlayer
{
    if (movieController != nil)
    {
        [movieController dismissMoviePlayerViewControllerAnimated];
        movieController = nil;
    }
    if (streamPlayer != nil) {
        [streamPlayer close];
        streamPlayer = nil;

        [self sendUpdate:@{@"type":@"stop"}];
    
        return true;
    }
    return false;
}

// Init the octoshapre system
- (void)initTheOctoShapeSystem
{
    octoshapeSystem = [OCOctoStatic createOctoshapeSystem];
    [[NSNotificationCenter defaultCenter] addObserverForName:kOCProblemEvent object:octoshapeSystem queue:[NSOperationQueue mainQueue] usingBlock: ^(NSNotification *note)
     {
         OCProblemEvent *p = (OCProblemEvent *)[[note userInfo] objectForKey:kOCEventKey];
         if ([p isNormal]) {
             return;
         }
         NSLog(@"%@", p.message);
         UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"An Error Occurred" message:p.message delegate:nil cancelButtonTitle:nil otherButtonTitles:@"Ok", nil];
         [alert show];
     }];
    [octoshapeSystem addPlayerName:kOCMediaPlayerIosNative andVersion:[[UIDevice currentDevice] systemVersion] forKey:@"videoplayer"];
    [octoshapeSystem open];
}

// Octoshape stream player
- (void)initStreamPlayerWithLink:(NSString*)myOctoLink
{
    streamPlayer = [octoshapeSystem createStreamPlayer:myOctoLink];
    [[NSNotificationCenter defaultCenter]
     addObserverForName:kOCUrlEvent
     object:streamPlayer
     queue:[NSOperationQueue mainQueue]
     usingBlock:^(NSNotification *note) {
         OCUrlEvent* event = (OCUrlEvent*)[[note userInfo] objectForKey:kOCEventKey];
//                                                      videoLink = event.url;
//                                                      descLabel.text = [NSString stringWithFormat:@"The OctoShape URL:%@", videoLink];
//                                                      [playVideo setEnabled:YES];
         NSLog(@"The OctoShape URL:%@",event.url);
         
         [self sendUpdate:@{@"type":@"start",@"link":myOctoLink}];
         
         [self persentVideoWithLink:event.url];
     }];
    
    [[NSNotificationCenter defaultCenter]
     addObserverForName:kOCProblemEvent
     object:streamPlayer
     queue:[NSOperationQueue mainQueue]
     usingBlock: ^(NSNotification *note) {
         OCProblemEvent* p = (OCProblemEvent*)[[note userInfo] objectForKey:kOCEventKey];
         NSLog(@"Stream unavailable (702)");
         // handle problem event.
         [self sendProblem:@{@"type":@"error",
                             @"code": [@(p.errorCode) stringValue],
                             @"message": p.message}];
         [self closePlayer];
     }];
    
    [streamPlayer initialize:YES];
    [streamPlayer play];
}

// Present video
- (void)persentVideoWithLink:(NSString*)videoLink
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(moviePlayerExit:)
                                                 name:MPMoviePlayerPlaybackDidFinishNotification
                                               object:nil];
    
    NSURL *movieURL = [NSURL URLWithString:videoLink];
    movieController = [[MPMoviePlayerViewController alloc] initWithContentURL:movieURL];
    [super.viewController presentMoviePlayerViewControllerAnimated:movieController];
    
    [movieController.moviePlayer play];
}

-(void)moviePlayerExit:(NSNotification*)aNotification{
    [self closePlayer];
}

- (void) onPause {
    [self closePlayer];
}

-(void)sendUpdate:(NSDictionary*)dictionary {
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                  messageAsDictionary:dictionary];
    [pluginResult setKeepCallback:[NSNumber numberWithBool:YES]];
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:callbackId];
}

-(void)sendProblem:(NSDictionary*)dictionary {
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                                  messageAsDictionary:dictionary];
    [pluginResult setKeepCallback:[NSNumber numberWithBool:YES]];
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:callbackId];
}
@end
