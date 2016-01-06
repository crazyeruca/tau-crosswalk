#include "rhodes.h"
#include "Crosswalk.h"

#include "logging/RhoLog.h"
#undef DEFAULT_LOGCATEGORY
#define DEFAULT_LOGCATEGORY "Crosswalk_impl"

#define CROSSWALK_FACTORY_CLASS "com.rho.crosswalk.CrosswalkFactory"

extern "C" void Init_Crosswalk_API(void);

extern "C" void Init_Crosswalk(void)
{
    RAWTRACE(__FUNCTION__);

    JNIEnv *env = jnienv();
    if(env)
    {
        jclass cls = rho_find_class(env, CROSSWALK_FACTORY_CLASS);
        if(!cls)
        {
            RAWLOG_ERROR1("Failed to find java class: %s", CROSSWALK_FACTORY_CLASS);
            return;
        }
        jmethodID midFactory = env->GetMethodID(cls, "<init>", "()V");
        if(!midFactory)
        {
            RAWLOG_ERROR1("Failed to get constructor for java class %s", CROSSWALK_FACTORY_CLASS);
            return;
        }
        jobject jFactory = env->NewObject(cls, midFactory);
        if(env->IsSameObject(jFactory, NULL))
        {
            RAWLOG_ERROR1("Failed to create %s instance", CROSSWALK_FACTORY_CLASS);
            return;
        }
        
        RAWTRACE("Initializing Java factory");

        rho::CCrosswalkBase::setJavaFactory(env, jFactory);

        RAWTRACE("Deleting JNI reference");

        env->DeleteLocalRef(jFactory);

        RAWTRACE("Initializing API");

        Init_Crosswalk_API();

        RAWTRACE("Init_Crosswalk succeeded");
    }
    else
    {
        RAWLOG_ERROR("Failed to initialize Crosswalk API: jnienv() is failed");
    }

}

extern "C" void Init_Crosswalk_extension() {
    Init_Crosswalk();
}
