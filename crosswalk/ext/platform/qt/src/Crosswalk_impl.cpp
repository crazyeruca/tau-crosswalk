#include "../../../shared/generated/cpp/CrosswalkBase.h"

namespace rho {

using namespace apiGenerator;

class CCrosswalkImpl: public CCrosswalkBase
{
public:
    CCrosswalkImpl(const rho::String& strID): CCrosswalkBase()
    {
    }

    virtual void getPlatformName(rho::apiGenerator::CMethodResult& oResult) {
         oResult.set("Win32");
    }

    virtual void calcSumm( int a,  int b, rho::apiGenerator::CMethodResult& oResult) {
         oResult.set(a+b);
    }
    
    virtual void joinStrings( const rho::String& a,  const rho::String& b, rho::apiGenerator::CMethodResult& oResult) {
         oResult.set(a+b);
    }

};

class CCrosswalkSingleton: public CCrosswalkSingletonBase
{
    ~CCrosswalkSingleton(){}
    virtual rho::String getInitialDefaultID();
    virtual void enumerate(CMethodResult& oResult);
};

class CCrosswalkFactory: public CCrosswalkFactoryBase
{
    ~CCrosswalkFactory(){}
    virtual ICrosswalkSingleton* createModuleSingleton();
    virtual ICrosswalk* createModuleByID(const rho::String& strID);
};

extern "C" void Init_Crosswalk_extension()
{
    CCrosswalkFactory::setInstance( new CCrosswalkFactory() );
    Init_Crosswalk_API();
}

ICrosswalk* CCrosswalkFactory::createModuleByID(const rho::String& strID)
{
    return new CCrosswalkImpl(strID);
}

ICrosswalkSingleton* CCrosswalkFactory::createModuleSingleton()
{
    return new CCrosswalkSingleton();
}

void CCrosswalkSingleton::enumerate(CMethodResult& oResult)
{
    rho::Vector<rho::String> arIDs;
    arIDs.addElement("SC1");
    arIDs.addElement("SC2");

    oResult.set(arIDs);
}

rho::String CCrosswalkSingleton::getInitialDefaultID()
{
    CMethodResult oRes;
    enumerate(oRes);

    rho::Vector<rho::String>& arIDs = oRes.getStringArray();
        
    return arIDs[0];
}

}