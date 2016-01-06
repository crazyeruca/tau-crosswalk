
#import "ICrosswalk.h"
#import "CrosswalkSingletonBase.h"

@interface CrosswalkSingleton : CrosswalkSingletonBase<ICrosswalkSingleton> {
}


-(NSString*)getInitialDefaultID;


-(void) enumerate:(id<IMethodResult>)methodResult;




@end