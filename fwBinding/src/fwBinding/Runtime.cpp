#include "fwBinding/Runtime.hpp"

#include <fwThread/Worker.hpp>

#include <fwServices/registry/ActiveWorkers.hpp>
#include <fwServices/registry/ServiceFactory.hpp>

#include <fwRuntime/profile/Profile.hpp>
#include <fwRuntime/Bundle.hpp>
#include <fwRuntime/Runtime.hpp>
#include <fwRuntime/operations.hpp>
#include <fwRuntime/IPlugin.hpp>

#include <fwCore/log/SpyLogger.hpp>

#include <boost/filesystem.hpp>

namespace fwBinding
{

//-----------------------------------------------------------------------------

struct Runtime::Impl
{
    ::fwRuntime::profile::Profile::sptr m_profile;
};

//-----------------------------------------------------------------------------

void initLog()
{
    typedef ::fwCore::log::SpyLogger SpyLogger;
    int logLevel = SpyLogger::SL_TRACE;

    SpyLogger &logger = fwCore::log::SpyLogger::getSpyLogger();
    logger.addStreamAppender(std::clog, static_cast<SpyLogger::LevelType>(logLevel));
}

//-----------------------------------------------------------------------------

Runtime::Runtime() : m_pimpl(new Impl())
{
    initLog();

    m_pimpl->m_profile = ::fwRuntime::profile::Profile::New();
    ::fwRuntime::profile::setCurrentProfile(m_pimpl->m_profile);
}

//-----------------------------------------------------------------------------

Runtime::~Runtime()
{
}

//-----------------------------------------------------------------------------

void Runtime::activateBundles()
{
    ::fwRuntime::Runtime* runtime = ::fwRuntime::Runtime::getDefault();
    ::fwRuntime::Runtime::BundleIterator iterBundles;
    for (iterBundles = runtime->bundlesBegin();
         iterBundles != runtime->bundlesEnd();
         ++iterBundles)
    {
        SPTR( ::fwRuntime::Bundle ) bundle = (*iterBundles);
        bundle->setEnable(true);
    }
}


//-----------------------------------------------------------------------------

void Runtime::addBundles(const std::string& bundlesPath)
{
    namespace fs = boost::filesystem;
    fs::path path(bundlesPath);

    if ( fs::is_directory(path))
    {
        ::fwRuntime::addBundles(path);
    }
    else
    {
        SLM_ERROR( "Bundle path '" + bundlesPath + "' do not exists or is not a directory.");
    }
}

//-----------------------------------------------------------------------------

void Runtime::run(Callback& callback)
{
    ::fwThread::Worker::sptr worker;
    worker = ::fwServices::registry::ActiveWorkers::getDefault()->getWorker(
        ::fwServices::registry::ActiveWorkers::s_DEFAULT_WORKER);
    worker->post( std::bind( &Callback::call, &callback) );

    worker->getFuture().wait();

    int result = ::boost::any_cast<int>(worker->getFuture().get());

    ::fwServices::registry::ActiveWorkers::getDefault()->clearRegistry();
    //::fwGui::registry::worker::reset();
    worker.reset();
}

//-----------------------------------------------------------------------------

} // fwBinding

