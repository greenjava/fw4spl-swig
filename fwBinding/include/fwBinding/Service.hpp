#ifndef __FWBINDING_SERVICE_HPP__
#define __FWBINDING_SERVICE_HPP__

#include "fwBinding/Data.hpp"
#include "fwBinding/config.hpp"

#include <string>
#include <vector>

namespace fwBinding
{

/**
 * @class Service
 */
class FWBINDING_CLASS_API Service
{

public:

    /// Constructor.
    FWBINDING_API Service(const ::fwBinding::Data& obj,
                          const std::string& implementation,
                          const std::string& uid = "");

    /// Desctructor.
    FWBINDING_API virtual ~Service();

    FWBINDING_API void unregisterService();

    FWBINDING_API std::string getUID() const;

    FWBINDING_API std::string getImplementation() const;

    FWBINDING_API void configure(const std::string& config);

    FWBINDING_API void start();

    FWBINDING_API void stop();

    FWBINDING_API void update();

    FWBINDING_API static std::vector< std::string > getServices();

    FWBINDING_API static std::vector< std::string > getServices(const std::string& object,
                                                                const std::string& serviceType);

private:

    ::fwBinding::Data m_object;
    std::string m_implementation;
    std::string m_uid;

};

} // fwBinding

#endif // __FWBINDING_SERVICE_HPP__
