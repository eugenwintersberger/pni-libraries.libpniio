/*!
\defgroup ascii_io ASCII support

*libpniio* provides support for reading and writing ASCII data. While there is
reading support is provided for all kind of concrete ASCII formats, writing
support is only supported up to some elementary extent. 

*/

/*! 
\ingroup ascii_io
\defgroup parser_classes Parsers: creating objects from strings
    
These classes are dedicated for generating objects from strings using the boost
spirit parser framework. The heart of the parser fraemwork is the
parser<T,ITERT> template. To use it include `pni/io/parsers.hpp` in your source
file. The pni::io::parser<T,ITERT>  template currently works for 

\li all scalar primitive types as defined by `libpnicore` 
\li and std::vector<T> where T is a scalar primitive type as defined by
`libpnicore`

In general the usage of the template is fairly easy. The following code snipped
reads a single scalar from a string 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <pni/core/types.hpp> 
#include <pni/io/parsers.hpp>

using namespace pni::core;
using namespace pni::io;

typedef parser<float64> float64_parser_type; 

int main(int,char **)
{
    float64 data; 
    string input; 
    float64_parser_type p; 
    
    std::cin>>input;
    data = p(input); 
    return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The ITERT template parameter normaly must not be set by the user. Its default
value is `pni::core::string::const_iterator` which should meet the most common
use cases. 
In the same manner as a scalare one can read a comman separated list of
floating point numbers from a string 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <pni/core/types.hpp>
#include <pni/io/parsers.hpp>
#include <pni/io/container_io_config.hpp>
#include <vector>

using namespace pni::core;
using namespace pni::io;

typedef std::vector<float64> f64_v_type;
typedef parser<f64_v_type> f64_v_parser_type; 

int main(int, char**)
{
    f64_v_type data; 
    string input; 
    f64_v_parser_type p(container_io_config(','));

    std::cin << input;
    data = p(input);

    return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
When parsing a list of items to a vector all whitespace characters before or
after the items are ignored or interpreted es separator symbols when
whitespaces are used as separators. This is true for all types except for
strings. Strings get some special treatment as described in the next section. 

Parsing strings 
---------------

As always strings are different. When parsing a single string the input string
is passed unchanged with all leading and trailing whitspace characters to the
output. 
When parsing a list of strings to a std::vector some special rules apply 

\li if the separator for the list items is a whitespace multiple whitespaces
are treated like a single one. Whitespace characters adjacent to a start symbol
and those directly before a stop symbol are ignored. 
\li for any other separator symbol only the whitespaces around the separator
and after and before the start and stop symbol are ignored. 

*/

/*!
\ingroup parser_classes
\defgroup parser_internal_classes Internal classes used by the parsers

*/

/*!
\ingroup ascii_io
\defgroup formatter_classes Formatters: converting data to strings

The basic facility to convert data to a string is the formatter<T> template. 
It can be accessed by including `formatter.hpp` in the source code. 
Its usage is fairly simple, for a scalar type use 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/formatter.hpp>

using namespace pni::core;
using namespace pni::io;

typedef pni::io::formatter<float64> float_fmt_type;

int main(int argc,char **argv)
{
    float_fmt_type float_formatter; 
    float64 data=4.3902e+2;

    std::cout<<float_formatter(data)<<std::endl;

    return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Also container types can be handled by using the container_io_config type. 
To convert the data stored in a `std::vector` to a string use something like
this 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <iostream>
#include <vector>
#include <pni/core/types.hpp>
#include <pni/io/formatter.hpp>

using namespace pni::core;
using namespace pni::io;

typedef std::vector<uint32> mca_type; 
typedef formatter<mca_type> mca_fmt_type; 

int main(int,char **)
{
    mca_fmt_type mca_fmt(container_io_config('[',']',';')); 
    mca_type mca{1,20,84,11};
    container_io_config mca_cfg;

    std::cout<<mca_fmt(mca)<<std::endl;
//    //  will output
//    //  [1;20;84;11]

    return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*!
\ingroup formatter_classes
\defgroup formatter_internal_classes Internal classes used by the formatters

The classes, functions, and data structures described in this section are only
of interest for developers of `libpniio`. 
The formatter framework provided by `libpniio` is based on
`boost::spirit::karma`. 

Container traits
----------------

In order to make `boost::spirit::karma` recognizing `pni::core::mdarray` and
`pni::core::array` as containers, specializiations for the container traits
must be provided in `boost::spirit:traits` for those types.
Specializations are provided for the following traits

\li `boost::spirit::traits::is_container` - identifying the types as containers
\li `boost::spirit::container_iterator` - providing the interator type
\li `boost::spirit::begin_container` - returning the iterator the first element
\li `boost::spirit::end_container` - returning the iterator for the last element

Custom policies 
---------------

Custom formatting policies are used for

\li all floating point numbers
\li complex numbers
\li unsigned 8Bit integers 

A custom policiy for floating point numbers was required due to the fact that 
C++, by default, does not write floating point numbers with their full 
numerical resolution. This can cause truncation effects where zeros are
writting simply because the number is too small. The custom policy avoids this
problem. 



Custom generators
-----------------

For some of the types provided by `libpnicore` custom generators are provided.
Obviously, custom generators are required for the scalar type erasures
`pni::core::value` and `pni::core::value_ref`. Both types are handled by the 
pni::io::value_generator template. 

*/


