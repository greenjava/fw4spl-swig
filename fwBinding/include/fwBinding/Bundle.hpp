#ifndef __FWBINDING_BUNDLE_HPP__
#define __FWBINDING_BUNDLE_HPP__

#include "fwBinding/config.hpp"

#include <string>

namespace fwBinding
{

/**
 * @class Bundle
 */
class FWBINDING_CLASS_API Bundle
{

public:

    /// Constructor.
    FWBINDING_API Bundle(const std::string& identifier, const std::string& version);

    /// Desctructor.
    FWBINDING_API virtual ~Bundle();

    FWBINDING_API void start();

    FWBINDING_API void stop();

    FWBINDING_API void initialize();

    FWBINDING_API void uninitialize();

    FWBINDING_API void setEnable(bool state);

    FWBINDING_API std::string getIdentifier() const;

    FWBINDING_API std::string getVersion() const;

private:

    std::string m_identifier;
    std::string m_version;

};

} // fwBinding

#endif // __FWBINDING_BUNDLE_HPP__
