//
//  CrosswalkImpl.cpp
#include "common/RhoStd.h"
#include "common/AutoPointer.h"
#include "common/RhodesApp.h"
#include "common/RhoConf.h"
#include "generated/cpp/CrosswalkBase.h"
#include "logging/RhoLog.h"

namespace rho {
    
    using namespace apiGenerator;
    using namespace common;
    
    class CCrosswalkSingletonImpl: public CCrosswalkSingletonBase
    {
    public:
        
        CCrosswalkSingletonImpl(): CCrosswalkSingletonBase(){}
        
        //methods

    };
    
    class CCrosswalkImpl : public CCrosswalkBase
    {
    public:
        virtual ~CCrosswalkImpl() {}

        //methods

        virtual void getProperty( const rho::String& propertyName, rho::apiGenerator::CMethodResult& oResult) {

        } 

        virtual void getProperties( const rho::Vector<rho::String>& arrayofNames, rho::apiGenerator::CMethodResult& oResult) {

        } 

        virtual void getAllProperties(rho::apiGenerator::CMethodResult& oResult) {

        } 

        virtual void setProperty( const rho::String& propertyName,  const rho::String& propertyValue, rho::apiGenerator::CMethodResult& oResult) {

        } 

        virtual void setProperties( const rho::Hashtable<rho::String, rho::String>& propertyMap, rho::apiGenerator::CMethodResult& oResult) {

        } 

    };
    
    ////////////////////////////////////////////////////////////////////////
    
    class CCrosswalkFactory: public CCrosswalkFactoryBase    {
    public:
        CCrosswalkFactory(){}
        
        ICrosswalkSingleton* createModuleSingleton()
        { 
            return new CCrosswalkSingletonImpl();
        }
        
        virtual ICrosswalk* createModuleByID(const rho::String& strID){ return new CCrosswalkImpl(); };
        
    };
    
}

extern "C" void Init_Crosswalk_extension()
{
    rho::CCrosswalkFactory::setInstance( new rho::CCrosswalkFactory() );
    rho::Init_Crosswalk_API();
    
}