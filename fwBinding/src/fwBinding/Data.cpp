#include "fwBinding/Data.hpp"

#include <fwData/Object.hpp>
#include <fwData/factory/new.hpp>

#include <fwTools/Object.hpp>
#include <fwTools/UUID.hpp>


namespace fwBinding
{

typedef std::map<std::string, ::fwData::Object::sptr> DataRegType;
DataRegType s_dataRegistry;

//-----------------------------------------------------------------------------

Data::Data(const std::string& implementation,
           const std::string& uid) :
    m_implementation(implementation),
    m_uid(uid.empty() ? ::fwTools::UUID::generateUUID() : uid)
{
    ::fwData::Object::sptr obj = ::fwData::registry::get()->create(implementation);
    obj->setID(m_uid);
    DataRegType::const_iterator it = s_dataRegistry.find(m_uid);
    if(it != s_dataRegistry.end())
    {
        SLM_ERROR("Data '"+m_uid+"' already registered");
    }
    s_dataRegistry[m_uid] = obj;
}

//-----------------------------------------------------------------------------

Data::~Data()
{
    DataRegType::const_iterator it = s_dataRegistry.find(m_uid);
    if(it != s_dataRegistry.end())
    {
        s_dataRegistry.erase(it);
    }
}

//-----------------------------------------------------------------------------

std::string Data::getUID() const
{
    return m_uid;
}

//-----------------------------------------------------------------------------

std::string Data::getImplementation() const
{
    return m_implementation;
}

//-----------------------------------------------------------------------------

} // fwBinding

