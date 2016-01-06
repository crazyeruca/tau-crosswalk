
#import "ICrosswalk.h"
#import "CrosswalkBase.h"

@interface Crosswalk : CrosswalkBase<ICrosswalk> {
}

-(void) getPlatformName:(id<IMethodResult>)methodResult;
-(void) calcSumm:(int)a b:(int)b methodResult:(id<IMethodResult>)methodResult;
-(void) joinStrings:(NSString*)a b:(NSString*)b methodResult:(id<IMethodResult>)methodResult;



@end
