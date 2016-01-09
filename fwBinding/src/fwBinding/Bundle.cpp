#include "fwBinding/Bundle.hpp"

#include <fwRuntime/Version.hpp>
#include <fwRuntime/Bundle.hpp>
#include <fwRuntime/Runtime.hpp>
#include <fwRuntime/operations.hpp>

namespace fwBinding
{

//-----------------------------------------------------------------------------

SPTR( ::fwRuntime::Bundle ) getBundle(const std::string& identifier, const std::string& ver)
{
    ::fwRuntime::Runtime * runtime = ::fwRuntime::Runtime::getDefault();
    ::fwRuntime::Version version(ver);
    SPTR( ::fwRuntime::Bundle ) bundle = runtime->findBundle(identifier, version);
    FW_RAISE_IF("Bundle '"+identifier+"' is missing", !bundle);
    return bundle;
}

//-----------------------------------------------------------------------------

Bundle::Bundle(const std::string& identifier, const std::string& version) :
    m_identifier(identifier), m_version(version)
{
}

//-----------------------------------------------------------------------------

Bundle::~Bundle()
{
}

//-----------------------------------------------------------------------------

void Bundle::start()
{
    SPTR( ::fwRuntime::Bundle ) bundle = getBundle(m_identifier, m_version);
    bundle->start();
}

//-----------------------------------------------------------------------------

void Bundle::initialize()
{
    SPTR( ::fwRuntime::Bundle ) bundle = getBundle(m_identifier, m_version);
    bundle->initialize();
}

//-----------------------------------------------------------------------------

void Bundle::uninitialize()
{
    SPTR( ::fwRuntime::Bundle ) bundle = getBundle(m_identifier, m_version);
    bundle->uninitialize();
}

//-----------------------------------------------------------------------------

void Bundle::stop()
{
    SPTR( ::fwRuntime::Bundle ) bundle = getBundle(m_identifier, m_version);
    bundle->stop();
}

//-----------------------------------------------------------------------------

void Bundle::setEnable(bool state)
{
    SPTR( ::fwRuntime::Bundle ) bundle = getBundle(m_identifier, m_version);
    bundle->setEnable(state);
}

//-----------------------------------------------------------------------------

std::string Bundle::getIdentifier() const
{
    return m_identifier;
}

//-----------------------------------------------------------------------------

std::string Bundle::getVersion() const
{
    return m_version;
}

//-----------------------------------------------------------------------------

} // fwBinding

