#ifndef __DATA_HPP__
#define __DATA_HPP__

#include<vector>
#include<pni/utils/Types.hpp>

using namespace pni::utils;

//-----------------------------------------------------------------------------
/*!
\brief create scalar test data

Template function creates a scalar test value. This function is used to test
scalar data IO. Specialized functions are available for Bool and String types.
\tparam T data type requested
\return data value
*/
template<typename T> T create_scalar_data()
{
    return T(1);
}

template<> String create_scalar_data<String>();
template<> Bool create_scalar_data<Bool>();

//-----------------------------------------------------------------------------
/*!
\brief create array test data

Creates array test data. The data is stored in a std::vector container. 
Data can be used for array data IO. Spezialied functions are available for Bool
and String types.
\tparam T requested data type
\param n number of elements to create
\return container with data values
*/
template<typename T> std::vector<T> create_array_data(size_t n)
{
    std::vector<T> v(n);

    std::fill(v.begin(),v.end(),T(1));
    return v;
}

template<> std::vector<String> create_array_data(size_t n);
template<> std::vector<Bool> create_array_data(size_t n);


#endif
