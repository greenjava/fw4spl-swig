#include "fwBinding/Service.hpp"

#include <fwServices/op/Get.hpp>
#include <fwServices/registry/ObjectService.hpp>
#include <fwServices/registry/ServiceFactory.hpp>
#include <fwServices/IService.hpp>

#include <fwData/Object.hpp>

#include <fwTools/Object.hpp>
#include <fwTools/UUID.hpp>

#include <fwRuntime/io/BundleDescriptorReader.hpp>
#include <fwRuntime/ConfigurationElement.hpp>

#include <libxml/parser.h>

#include <strstream>

namespace fwBinding
{

//-----------------------------------------------------------------------------

Service::Service(const ::fwBinding::Data& obj,
                 const std::string& implementation,
                 const std::string& uid) :
    m_object(obj),
    m_implementation(implementation),
    m_uid(uid.empty() ? ::fwTools::UUID::generateUUID() : uid)
{
    ::fwServices::IService::sptr srv;
    ::fwServices::registry::ServiceFactory::sptr srvFactory = ::fwServices::registry::ServiceFactory::getDefault();

    srv = srvFactory->create(m_implementation);
    SLM_ASSERT("Cannot instantiate service '"+m_implementation+"'", srv);
    srv->setID(m_uid);

    ::fwTools::Object::sptr baseObj = ::fwTools::fwID::getObject(m_object.getUID());
    ::fwData::Object::sptr dataObj  = ::fwData::Object::dynamicCast(baseObj);
    ::fwServices::OSR::registerService(dataObj, srv);
}

//-----------------------------------------------------------------------------

Service::~Service()
{
    this->stop();
    this->unregisterService();
}

//-----------------------------------------------------------------------------

void Service::unregisterService()
{
    ::fwServices::IService::sptr srv = ::fwServices::get(m_uid);
    if(srv)
    {
        ::fwServices::OSR::unregisterService(srv);
    }
}

//-----------------------------------------------------------------------------

std::string Service::getUID() const
{
    return m_uid;
}

//-----------------------------------------------------------------------------

std::string Service::getImplementation() const
{
    return m_implementation;
}

//-----------------------------------------------------------------------------

void Service::configure(const std::string& config)
{
    ::fwRuntime::ConfigurationElement::sptr cfgElement;

    xmlDocPtr doc = xmlParseMemory(config.c_str(), config.size());
    if (doc != nullptr)
    {
        xmlNodePtr root = xmlDocGetRootElement(doc);
        SPTR(::fwRuntime::Bundle) bundle;
        cfgElement = ::fwRuntime::io::BundleDescriptorReader::processConfigurationElement(root, bundle);
        xmlFreeDoc(doc);
    }

    ::fwServices::IService::sptr srv = ::fwServices::get(m_uid);
    srv->setConfiguration(cfgElement);
    srv->configure();
}

//-----------------------------------------------------------------------------

void Service::start()
{
    ::fwServices::IService::sptr srv = ::fwServices::get(m_uid);
    srv->start();
}

//-----------------------------------------------------------------------------

void Service::stop()
{
    ::fwServices::IService::sptr srv = ::fwServices::get(m_uid);
    if(srv && srv->isStarted())
    {
        srv->stop();
    }
}

//-----------------------------------------------------------------------------

void Service::update()
{
    ::fwServices::IService::sptr srv = ::fwServices::get(m_uid);
    srv->update();
}

//-----------------------------------------------------------------------------

std::vector< std::string > Service::getServices()
{
    return ::fwServices::registry::ServiceFactory::getDefault()->getFactoryKeys();
}

//-----------------------------------------------------------------------------

std::vector< std::string > Service::getServices(const std::string& object, const std::string& serviceType)
{
    ::fwServices::registry::ServiceFactory::sptr factory;
    factory = ::fwServices::registry::ServiceFactory::getDefault();
    return factory->getImplementationIdFromObjectAndType(object, serviceType);
}

//-----------------------------------------------------------------------------

} // fwBinding

