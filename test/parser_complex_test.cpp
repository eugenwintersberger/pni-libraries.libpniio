#include <pni/core/types.hpp>
#include <pni/parsers.hpp>
#include <iostream>

using namespace pni::core;
using namespace pni::io;

int main()
{
    parser<complex32> p;
    
    try
    {
        complex32 value = p("34.+j123.e-3");
        std::cout<<"Got number: "<<std::endl;
    }
    catch(const parser_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    return 0;
}
