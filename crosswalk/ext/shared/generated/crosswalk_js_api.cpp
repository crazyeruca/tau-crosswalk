#include "api_generator/js_helpers.h"
#include "api_generator/Api.h"

#include "logging/RhoLog.h"
#undef DEFAULT_LOGCATEGORY
#define DEFAULT_LOGCATEGORY "Crosswalk"




rho::String js_Crosswalk_getProperty(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_def_getProperty(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);

rho::String js_Crosswalk_getProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_def_getProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);

rho::String js_Crosswalk_getAllProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_def_getAllProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);

rho::String js_Crosswalk_setProperty(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_def_setProperty(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);

rho::String js_Crosswalk_setProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_def_setProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);



rho::String js_s_Crosswalk_getDefaultID(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_getDefault(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);
rho::String js_s_Crosswalk_setDefaultID(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam);



namespace {
  using namespace rho::apiGenerator;
  class CrosswalkDispatcher : public ApiHandler<Func_JS>
  {
  public:
    CrosswalkDispatcher() : ApiHandler("Rho:Crosswalk") {}
    virtual ~CrosswalkDispatcher() {}
    virtual void initialize();
  };
  
  void CrosswalkDispatcher::initialize()
  {
    ApiHandler<Func_JS>::initialize();
    
    RAWTRACE("Initializing Rho:Crosswalk API...");


    defineInstanceMethod("getProperty", js_Crosswalk_getProperty);
    //  should define static method !     defineStaticMethod("def_getProperty", js_s_Crosswalk_def_getProperty);;


    defineInstanceMethod("getProperties", js_Crosswalk_getProperties);
    //  should define static method !     defineStaticMethod("def_getProperties", js_s_Crosswalk_def_getProperties);;


    defineInstanceMethod("getAllProperties", js_Crosswalk_getAllProperties);
    //  should define static method !     defineStaticMethod("def_getAllProperties", js_s_Crosswalk_def_getAllProperties);;


    defineInstanceMethod("setProperty", js_Crosswalk_setProperty);
    //  should define static method !     defineStaticMethod("def_setProperty", js_s_Crosswalk_def_setProperty);;


    defineInstanceMethod("setProperties", js_Crosswalk_setProperties);
    //  should define static method !     defineStaticMethod("def_setProperties", js_s_Crosswalk_def_setProperties);;


    defineStaticMethod("getDefaultID", js_s_Crosswalk_getDefaultID);
    defineStaticMethod("getDefault", js_s_Crosswalk_getDefault);
    defineStaticMethod("setDefaultID", js_s_Crosswalk_setDefaultID);

    RAWTRACE("Rho:Crosswalk API - done");
  }
}

extern "C" void Init_JSAPI_Crosswalk(void)
{
  rho::apiGenerator::defineJSApiModule(new CrosswalkDispatcher);
}
