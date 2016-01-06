

#include "logging/RhoLog.h"
#undef DEFAULT_LOGCATEGORY
#define DEFAULT_LOGCATEGORY "Crosswalk"

#include "CrosswalkBase.h"
#include "api_generator/js_helpers.h"
#include "api_generator/JSONResultConvertor.h"

#include "common/StringConverter.h"

extern "C" void rho_os_impl_performOnUiThread(rho::common::IRhoRunnable* pTask);

#ifdef OS_ANDROID
#include <jni.h>
extern "C" void* rho_nativethread_start();
JNIEnv* jnienv();
#endif //OS_ANDROID

using namespace rho;
using namespace rho::json;
using namespace rho::common;
using namespace rho::apiGenerator;


rho::String js_Crosswalk_getProperty(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    RAWTRACE4("getProperty(strObjID = %s, argc = %d, strCallbackID = %s, strJsVmID = %s)", strObjID.c_str(), argv.getSize(), strCallbackID.c_str(), strJsVmID.c_str());

#ifdef OS_ANDROID
    if ( jnienv() == 0 )
    {
        rho_nativethread_start();
    }
#endif

    rho::apiGenerator::CMethodResult oRes;


    oRes.setRequestedType(CMethodResult::eString);

    rho::common::CInstanceClassFunctorBase<rho::apiGenerator::CMethodResult>* pFunctor = 0;
    int argc = argv.getSize();

    rho::ICrosswalk* pObj = rho::CCrosswalkFactoryBase::getInstance()->getModuleByID(strObjID);

    if ( argc == 0 )
    {
        oRes.setArgError( "Wrong number of arguments: " + convertToStringA(argc) + " instead of " + convertToStringA(1) );
        return oRes.toJSON();
    }
    
    rho::String arg0 = "";
    if ( argc > 0 )
    {
        if ( argv[0].isString() )
        {
            arg0 = argv[0].getStringObject();
        }
        else if (!argv[0].isNull())
        {
            oRes.setArgError( "Type error: argument " "0" " should be " "string" );
            return oRes.toJSON();
        }
    }

    oRes.setCallInUIThread(false);
    oRes.setJSCallback( strCallbackID );
    oRes.setCallbackParam( strCallbackParam );

    if ( oRes.hasCallback() )
    {
        pFunctor = rho_makeInstanceClassFunctor2( pObj, &rho::ICrosswalk::getProperty, arg0,  oRes );
        rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->addCommandToQueue( pFunctor );
    }
    else 
    {

        pObj->getProperty( arg0,  oRes );
    }
    
    return oRes.toJSON();

}

rho::String js_Crosswalk_getProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    RAWTRACE4("getProperties(strObjID = %s, argc = %d, strCallbackID = %s, strJsVmID = %s)", strObjID.c_str(), argv.getSize(), strCallbackID.c_str(), strJsVmID.c_str());

#ifdef OS_ANDROID
    if ( jnienv() == 0 )
    {
        rho_nativethread_start();
    }
#endif

    rho::apiGenerator::CMethodResult oRes;


    oRes.setRequestedType(CMethodResult::eStringHash);

    rho::common::CInstanceClassFunctorBase<rho::apiGenerator::CMethodResult>* pFunctor = 0;
    int argc = argv.getSize();

    rho::ICrosswalk* pObj = rho::CCrosswalkFactoryBase::getInstance()->getModuleByID(strObjID);

    if ( argc == 0 )
    {
        oRes.setArgError( "Wrong number of arguments: " + convertToStringA(argc) + " instead of " + convertToStringA(1) );
        return oRes.toJSON();
    }
    
    rho::Vector<rho::String> arg0;
    if ( argc > 0 )
    {
        CJSONEntry value(argv[0]);
        if ( value.isArray() )
        {
            
            CJSONArray arParam(value);
            arg0.reserve(arParam.getSize());
            for( int i = 0; i < arParam.getSize(); i++ )
            {
                arg0.addElement( arParam[i].getStringObject() );
            }
            
        }
        else if (!value.isNull())
        {
            oRes.setArgError("Type error: argument " "0" " should be " "array" );
            return oRes.toJSON();
        }
    }

    oRes.setCallInUIThread(false);
    oRes.setJSCallback( strCallbackID );
    oRes.setCallbackParam( strCallbackParam );

    if ( oRes.hasCallback() )
    {
        pFunctor = rho_makeInstanceClassFunctor2( pObj, &rho::ICrosswalk::getProperties, arg0,  oRes );
        rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->addCommandToQueue( pFunctor );
    }
    else 
    {

        pObj->getProperties( arg0,  oRes );
    }
    
    return oRes.toJSON();

}

rho::String js_Crosswalk_getAllProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    RAWTRACE4("getAllProperties(strObjID = %s, argc = %d, strCallbackID = %s, strJsVmID = %s)", strObjID.c_str(), argv.getSize(), strCallbackID.c_str(), strJsVmID.c_str());

#ifdef OS_ANDROID
    if ( jnienv() == 0 )
    {
        rho_nativethread_start();
    }
#endif

    rho::apiGenerator::CMethodResult oRes;


    oRes.setRequestedType(CMethodResult::eStringHash);

    rho::common::CInstanceClassFunctorBase<rho::apiGenerator::CMethodResult>* pFunctor = 0;
    int argc = argv.getSize();

    rho::ICrosswalk* pObj = rho::CCrosswalkFactoryBase::getInstance()->getModuleByID(strObjID);

    oRes.setCallInUIThread(false);
    oRes.setJSCallback( strCallbackID );
    oRes.setCallbackParam( strCallbackParam );

    if ( oRes.hasCallback() )
    {
        pFunctor = rho_makeInstanceClassFunctor1( pObj, &rho::ICrosswalk::getAllProperties,  oRes );
        rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->addCommandToQueue( pFunctor );
    }
    else 
    {

        pObj->getAllProperties(  oRes );
    }
    
    return oRes.toJSON();

}

rho::String js_Crosswalk_setProperty(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    RAWTRACE4("setProperty(strObjID = %s, argc = %d, strCallbackID = %s, strJsVmID = %s)", strObjID.c_str(), argv.getSize(), strCallbackID.c_str(), strJsVmID.c_str());

#ifdef OS_ANDROID
    if ( jnienv() == 0 )
    {
        rho_nativethread_start();
    }
#endif

    rho::apiGenerator::CMethodResult oRes;



    rho::common::CInstanceClassFunctorBase<rho::apiGenerator::CMethodResult>* pFunctor = 0;
    int argc = argv.getSize();

    rho::ICrosswalk* pObj = rho::CCrosswalkFactoryBase::getInstance()->getModuleByID(strObjID);

    if ( argc == 0 )
    {
        oRes.setArgError( "Wrong number of arguments: " + convertToStringA(argc) + " instead of " + convertToStringA(2) );
        return oRes.toJSON();
    }
    
    rho::String arg0 = "";
    if ( argc > 0 )
    {
        if ( argv[0].isString() )
        {
            arg0 = argv[0].getStringObject();
        }
        else if (!argv[0].isNull())
        {
            oRes.setArgError( "Type error: argument " "0" " should be " "string" );
            return oRes.toJSON();
        }
    }

    if ( argc == 1 )
    {
        oRes.setArgError( "Wrong number of arguments: " + convertToStringA(argc) + " instead of " + convertToStringA(2) );
        return oRes.toJSON();
    }
    
    rho::String arg1 = "";
    if ( argc > 1 )
    {
        if ( argv[1].isString() )
        {
            arg1 = argv[1].getStringObject();
        }
        else if (!argv[1].isNull())
        {
            oRes.setArgError( "Type error: argument " "1" " should be " "string" );
            return oRes.toJSON();
        }
    }

    if ( oRes.hasCallback() )
    {
        pFunctor = rho_makeInstanceClassFunctor3( pObj, &rho::ICrosswalk::setProperty, arg0, arg1,  oRes );
        rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->addCommandToQueue( pFunctor );
    }
    else 
    {

        pObj->setProperty( arg0, arg1,  oRes );
    }
    
    return oRes.toJSON();

}

rho::String js_Crosswalk_setProperties(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    RAWTRACE4("setProperties(strObjID = %s, argc = %d, strCallbackID = %s, strJsVmID = %s)", strObjID.c_str(), argv.getSize(), strCallbackID.c_str(), strJsVmID.c_str());

#ifdef OS_ANDROID
    if ( jnienv() == 0 )
    {
        rho_nativethread_start();
    }
#endif

    rho::apiGenerator::CMethodResult oRes;



    rho::common::CInstanceClassFunctorBase<rho::apiGenerator::CMethodResult>* pFunctor = 0;
    int argc = argv.getSize();

    rho::ICrosswalk* pObj = rho::CCrosswalkFactoryBase::getInstance()->getModuleByID(strObjID);

    if ( argc == 0 )
    {
        oRes.setArgError( "Wrong number of arguments: " + convertToStringA(argc) + " instead of " + convertToStringA(1) );
        return oRes.toJSON();
    }
    
    rho::Hashtable<rho::String, rho::String> arg0;
    if ( argc > 0 )
    {
        CJSONEntry value(argv[0]);
        if ( value.isObject() )
        {
            
            CJSONStructIterator objIter(value);

            for( ; !objIter.isEnd(); objIter.next() )
            {
                arg0[objIter.getCurKey()] = objIter.getCurString();
            }
            
        }
        else if (!value.isNull())
        {
            oRes.setArgError("Type error: argument " "0" " should be " "hash" );
            return oRes.toJSON();
        }
    }

    if ( oRes.hasCallback() )
    {
        pFunctor = rho_makeInstanceClassFunctor2( pObj, &rho::ICrosswalk::setProperties, arg0,  oRes );
        rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->addCommandToQueue( pFunctor );
    }
    else 
    {

        pObj->setProperties( arg0,  oRes );
    }
    
    return oRes.toJSON();

}



rho::String js_s_Crosswalk_getDefaultID(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    rho::apiGenerator::CMethodResult oRes;
    rho::String strDefaultID = rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->getDefaultID();
    oRes.set(strDefaultID);

    return oRes.toJSON();
}

rho::String js_s_Crosswalk_getDefault(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    rho::apiGenerator::CMethodResult oRes;
    rho::String strDefaultID = rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->getDefaultID();
    oRes.set(strDefaultID);
    oRes.setJSObjectClassPath("Rho.Crosswalk");

    return oRes.toJSON();
}

rho::String js_s_Crosswalk_setDefaultID(const rho::String& strObjID, rho::json::CJSONArray& argv, const rho::String& strCallbackID, const rho::String& strJsVmID, const rho::String& strCallbackParam)
{
    rho::apiGenerator::CMethodResult oRes;
    rho::json::CJSONEntry el = argv[0];

    if (el.isString()) {
        rho::CCrosswalkFactoryBase::getCrosswalkSingletonS()->setDefaultID(el.getString());
    } else {
        oRes.setError("Method parameter should be defined as string!");
    }

    return oRes.toJSON();
}


