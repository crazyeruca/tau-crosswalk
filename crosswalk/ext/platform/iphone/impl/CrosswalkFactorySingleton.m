
#import "ICrosswalk.h"
#import "CrosswalkFactoryBase.h"

static CrosswalkFactoryBase* ourCrosswalkFactory = nil;

@implementation CrosswalkFactorySingleton

+(id<ICrosswalkFactory>) getCrosswalkFactoryInstance {
    if (ourCrosswalkFactory == nil) {
        ourCrosswalkFactory = [[CrosswalkFactoryBase alloc] init];
    }
    return ourCrosswalkFactory;
}

@end