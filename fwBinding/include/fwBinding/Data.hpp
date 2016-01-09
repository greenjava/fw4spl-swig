#ifndef __FWBINDING_DATA_HPP__
#define __FWBINDING_DATA_HPP__

#include "fwBinding/config.hpp"

#include <string>

namespace fwBinding
{

/**
 * @class Data
 */
class FWBINDING_CLASS_API Data
{

public:

    /// Constructor.
    FWBINDING_API Data(const std::string& objectType, const std::string& uid = "");

    /// Desctructor.
    FWBINDING_API virtual ~Data();

    FWBINDING_API std::string getUID() const;

    FWBINDING_API std::string getImplementation() const;

private:

    std::string m_implementation;
    std::string m_uid;
};

} // fwBinding

#endif // __FWBINDING_DATA_HPP__
