#pragma once

#include "ICrosswalk.h"
#include "logging/RhoLog.h"
#include "common/StringConverter.h"
#include "common/ExtManager.h"


namespace rho {

using namespace rho::apiGenerator;
using namespace rho;

// hash keys used in properties and parameters 

class CCrosswalkFactoryBase : public CModuleFactoryBase<ICrosswalk, ICrosswalkSingleton, ICrosswalkFactory>
{
protected:
    static rho::common::CAutoPtr<CCrosswalkFactoryBase> m_pInstance;
    HashtablePtr<rho::String,ICrosswalk*> m_hashModules;

public:

    static void setInstance(CCrosswalkFactoryBase* pInstance){ m_pInstance = pInstance; }
    static CCrosswalkFactoryBase* getInstance(){ return m_pInstance; }

    static ICrosswalkSingleton* getCrosswalkSingletonS(){ return getInstance()->getModuleSingleton(); }

    virtual ICrosswalk* getModuleByID(const rho::String& strID)
    {
        if ( !m_hashModules.containsKey(strID) )
        {
            ICrosswalk* pObj = createModuleByID(strID);
            m_hashModules.put(strID, pObj );

            return pObj;
        }

        return m_hashModules[strID];
    }

    virtual ICrosswalk* createModuleByID(const rho::String& strID){ return (ICrosswalk*)0; };
    virtual void deleteModuleByID(const rho::String& strID)
    {
        m_hashModules.remove(strID);
    }

};

class CCrosswalkSingletonBase : public CModuleSingletonBase< ICrosswalkSingleton >, public rho::common::IRhoExtension
{
protected:
    DEFINE_LOGCLASS;


    rho::String m_strDefaultID;




public:
    virtual rho::LogCategory getModuleLogCategory(){ return getLogCategory(); }

    CCrosswalkSingletonBase();
    ~CCrosswalkSingletonBase();




    virtual void setDefaultID(const rho::String& strDefaultID){ m_strDefaultID = strDefaultID; }
    virtual rho::String getDefaultID()
    { 
        if ( m_strDefaultID.length() == 0 )
            setDefaultID(getInitialDefaultID());
        return m_strDefaultID; 
    }

};

class CCrosswalkBase: public ICrosswalk
{
protected:
    DEFINE_LOGCLASS;


    rho::Hashtable<rho::String, rho::String> m_hashProps;
    rho::Hashtable<rho::String, rho::apiGenerator::CMethodAccessor< ICrosswalk > *> m_mapPropAccessors;

public:


    CCrosswalkBase();

    virtual void getProperty( const rho::String& propertyName, CMethodResult& oResult);
    virtual void getProperties( const rho::Vector<rho::String>& arrayofNames, CMethodResult& oResult);
    virtual void getAllProperties(CMethodResult& oResult);
    virtual void setProperty( const rho::String& propertyName,  const rho::String& propertyValue, CMethodResult& oResult);
    virtual void setProperties( const rho::Hashtable<rho::String, rho::String>& propertyMap, CMethodResult& oResult);
    virtual void clearAllProperties(CMethodResult& oResult);



    static CCrosswalkBase* getInstance(){ return static_cast< CCrosswalkBase* >(CCrosswalkFactoryBase::getInstance()->getModuleByID(CCrosswalkFactoryBase::getCrosswalkSingletonS()->getDefaultID())); }
 

};

extern "C" void Init_Crosswalk_API();


}
