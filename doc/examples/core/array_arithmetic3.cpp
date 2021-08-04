//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Mar 18, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
// basic linear algebra
//-----------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <random>
#include <pni/types.hpp>
#include <pni/arrays.hpp>

using namespace pni;

// define the matrix and  vector types
template<typename T,size_t N> using matrix_temp = static_array<T,N,N>;
template<typename T,size_t N> using vector_temp = static_array<T,N>;

//-----------------------------------------------------------------------------
// print a matrix
template<typename T,size_t N>
std::ostream &operator<<(std::ostream &o,const matrix_temp<T,N> &m)
{
    for(size_t i = 0;i<3;++i)
    {
        o<<"| ";
        for(size_t j=0;j<3;++j) o<<m(i,j)<<" ";
        o<<"|"<<std::endl;
    }

    return o;
}

//-----------------------------------------------------------------------------
// print a vector
template<typename T,size_t N>
std::ostream &operator<<(std::ostream &o,const vector_temp<T,N> &v)
{
    for(auto x: v) o<<"| "<<x<<" |"<<std::endl;
    return o;
}

//-----------------------------------------------------------------------------
// matrix-vector multiplication
template<typename T,size_t N>
vector_temp<T,N> mv_mult(const matrix_temp<T,N> &m,const vector_temp<T,N> &v)
{
    vector_temp<T,N> result;

    size_t i = 0;
    for(auto &r: result)
    {
        const auto row = m(i++,slice(0,N));
        r = std::inner_product(v.begin(),v.end(),row.begin(),T(0));
    }
    return result;
}

//-----------------------------------------------------------------------------
// vector-matrix multiplication
template<typename T,size_t N>
vector_temp<T,N> mv_mult(const vector_temp<T,N> &v,const matrix_temp<T,N> &m)
{
    vector_temp<T,N> result;

    size_t i = 0;
    for(auto &r: result)
    {
        const auto col = m(slice(0,N),i++);
        r = std::inner_product(col.begin(),col.end(),v.begin(),T(0));
    }
    return result;
}

//-----------------------------------------------------------------------------
// matrix-matrix multiplication
template<typename T,size_t N>
matrix_temp<T,N> mv_mult(const matrix_temp<T,N> &m1,const matrix_temp<T,N> &m2)
{
    matrix_temp<T,N> result;

    for(size_t i=0;i<N;++i)
    {
        for(size_t j=0;j<N;++j)
        {
            const auto row = m1(i,slice(0,N));
            const auto col = m2(slice(0,N),j);
            result(i,j) = std::inner_product(row.begin(),row.end(),
                                             col.begin(),T(0));
        }
    }
    return result;
}

//-----------------------------------------------------------------------------
// define some local types
typedef float64                    number_type;
typedef vector_temp<number_type,3> vector_type;
typedef matrix_temp<number_type,3> matrix_type;


int main(int ,char **)
{
    vector_type v;
    matrix_type m1,m2; 
    m1 = {1,2,3,4,5,6,7,8,9};
    m2 = {9,8,7,6,5,4,3,2,1};
    v  = {1,2,3};

    std::cout<<"m1 = "<<std::endl<<m1<<std::endl;
    std::cout<<"m2 = "<<std::endl<<m2<<std::endl;
    std::cout<<"v  = "<<std::endl<<v<<std::endl;
    std::cout<<"m1.v = "<<std::endl<<mv_mult(m1,v)<<std::endl;
    std::cout<<"v.m1 = "<<std::endl<<mv_mult(v,m1)<<std::endl;
    std::cout<<"m1.m2 = "<<std::endl<<mv_mult(m1,m2)<<std::endl;
                               
    return 0;
}

