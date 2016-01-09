%module(directors="1") fw4spl
%{
#include "fwBinding/Runtime.hpp"
#include "fwBinding/Service.hpp"
#include "fwBinding/Data.hpp"
#include "fwBinding/Bundle.hpp"
#include "fwBinding/Callback.hpp"
%}

%include <std_string.i>
%include <std_vector.i>
// Instantiate templates
namespace std {
   %template(StringVector) vector<string>;
}

%feature("director") Callback;
%include "fwBinding/Callback.hpp"
%include "fwBinding/config.hpp"
%include "fwBinding/Runtime.hpp"
%include "fwBinding/Data.hpp"
%include "fwBinding/Service.hpp"
%include "fwBinding/Bundle.hpp"