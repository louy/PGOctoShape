#import <Foundation/Foundation.h>

/** Key for <code>OCEvent</code>s in <code>NSNotification</code> <code>userInfo</code>  */
static NSString* kOCEventKey = @"event";

/** Notification name for <code>OCAuthenticationEvent</code>s  */
static NSString* kOCAuthenticationEvent = @"AuthenticationEvent";

/** Notification name for <code>OCCurrentStreamInfoEvent</code>s  */
static NSString* kOCCurrentStreamInfoEvent = @"CurrentStreamInfoEvent";

/** Notification name for <code>OCPortBound</code>s  */
static NSString* kOCPortBoundEvent = @"PortBound";

/** Notification name for <code>OCOctoshapeSystemStartedEvent</code>s  */
static NSString* kOCOctoshapeSystemStartedEvent = @"OctoshapeSystemStarted";

/** OCOctoshapeSystems suspended successfully notification*/
static NSString* kOCSuspendedEvent = @"Suspended";

/** Notification name for <code>OCDurationChangedEvent</code>s  */
static NSString* kOCDurationChangedEvent = @"DurationChangedEvent";

/** Notification name for <code>OCMultiStreamInfoEvent</code>s  */
static NSString* kOCMultiStreamInfoEvent = @"MultiStreamInfoEvent";

/** Notification name for <code>OCProblemEvent</code>s  */
static NSString* kOCProblemEvent = @"ProblemEvent";

/** Notification name for <code>OCSeekTypeInfoEvent</code>s  */
static NSString* kOCSeekTypeInfoEvent = @"SeekTypeInfoEvent";

/** Notification name for <code>OCStreamConfigEvent</code>s  */
static NSString* kOCStreamConfigEvent = @"StreamConfigEvent";

/** Notification name for <code>OCStreamPlayerStatusEvent</code>s  */
static NSString* kOCStreamPlayerStatusEvent = @"StreamPlayerStatusEvent";

/** Notification name for <code>OCStreamSourceInfoEvent</code>s  */
static NSString* kOCStreamSourceInfoEvent = @"StreamSourceInfoEvent";

/** Notification name for <code>OCTimeInfoLiveEvent</code>s  */
static NSString* kOCTimeInfoLiveEvent = @"TimeInfoLiveEvent";

/** Notification name for <code>OCTimeInfoOnDemandEvent</code>s  */
static NSString* kOCTimeInfoOnDemandEvent = @"TimeInfoOnDemandEvent";

/** Notification name for <code>OCUMetaEvent</code>s  */
static NSString* kOCUMetaEvent = @"UMetaDataEvent";

/** Notification name for <code>OCUrlEvent</code>s  */
static NSString* kOCUrlEvent = @"UrlEvent";