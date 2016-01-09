#ifndef __FWBINDING_RUNTIME_HPP__
#define __FWBINDING_RUNTIME_HPP__

#include "fwBinding/Callback.hpp"
#include "fwBinding/config.hpp"

#include <string>
#include <memory>

namespace fwBinding
{

/**
 * @class Runtime
 */
class FWBINDING_CLASS_API Runtime
{

public:

    /// Constructor.
    FWBINDING_API Runtime();

    /// Desctructor.
    FWBINDING_API virtual ~Runtime();

    FWBINDING_API void addBundles(const std::string& bundlesPath);

    FWBINDING_API void activateBundles();

    FWBINDING_API void run(Callback& callback);

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;
};

} // fwBinding

#endif // __FWBINDING_RUNTIME_HPP__
