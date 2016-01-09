#ifndef __FWBINDING_CALLBACK_HPP__
#define __FWBINDING_CALLBACK_HPP__

#include "fwBinding/config.hpp"

namespace fwBinding
{

/**
 * @class Callback
 */
class Callback
{
public:
    Callback()
    {
    }

    virtual ~Callback()
    {
    }

    virtual void call()
    {
    }
};

} // fwBinding

#endif // __FWBINDING_CALLBACK_HPP__
