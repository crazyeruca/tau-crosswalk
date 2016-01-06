#import <Foundation/Foundation.h>
#include "common/app_build_capabilities.h"

extern void Init_Crosswalk_API();

void Init_Crosswalk_extension()
{
    Init_Crosswalk_API();
}