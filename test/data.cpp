#include "data.hpp"


//-----------------------------------------------------------------------------
template<> string create_scalar_data<string>()
{
    return "hello world";
}

//-----------------------------------------------------------------------------
template<> Bool create_scalar_data<Bool>()
{
    return true;
}

//-----------------------------------------------------------------------------
template<> std::vector<string> create_array_data(size_t n)
{
    std::vector<string> v;

    std::stringstream ss;
    for(size_t i=0;i<n;i++)
    {
        ss<<i;
        v.push_back(ss.str());
    }

    return v;
}

//-----------------------------------------------------------------------------
template<> std::vector<Bool> create_array_data(size_t n)
{
    std::vector<Bool> v(n);

    for(size_t i=0;i<n;i++)
    {
        if(i%2) v[i] = true;
        else v[i] = false;
    }

    return v;
}

