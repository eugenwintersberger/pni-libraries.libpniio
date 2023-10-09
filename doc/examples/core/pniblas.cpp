//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Nov 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "pniblas.hpp"
#include <chrono>

extern "C"
{
#include <cblas.h>
}
using namespace pni;

namespace blas = pni::blas;

typedef blas::vector_type<float64> dvector;
typedef blas::matrix_type<float64> dmatrix;

typedef std::chrono::high_resolution_clock clock_type;
typedef std::chrono::milliseconds duration_type;

static const size_t N=10000;
static const size_t M=10000;

int main(int ,char **)
{
    auto a = dvector::create(shape_t{N});
    auto b = dvector::create(shape_t{N});
    auto m = dmatrix::create(shape_t{N,M});

    std::fill(a.begin(),a.end(),1.0);
    std::fill(b.begin(),b.end(),2.0);
    std::fill(m.begin(),m.end(),3.0);

    //std::cout<<blas::dot(a,b)<<std::endl;
    std::cout<<"Dot product ..."<<std::endl;
    auto start_time = clock_type::now();
    std::cout<<blas::dot(a,b)<<std::endl;
    auto end_time   = clock_type::now();
    auto elapsed = end_time-start_time;
    
    std::cout<<"elapsed time: "<<elapsed.count()<<std::endl;
    
    std::cout<<"Simple dot product ..."<<std::endl;
    start_time = clock_type::now();
    std::cout<<blas::dot_simple(a,b)<<std::endl;
    end_time   = clock_type::now();
    elapsed = end_time-start_time;

    std::cout<<"elapsed time: "<<elapsed.count()<<std::endl;

    start_time = clock_type::now();
    std::cout<<cblas_ddot(N,a.data(),1,b.data(),1)<<std::endl;
    end_time   = clock_type::now();
    elapsed = end_time - start_time;
    std::cout<<"elapsed time: "<<elapsed.count()<<std::endl;

    std::cout<<"Vector Matrix product ..."<<std::endl;
    std::cout<<"Running C++ BLAS ..."<<std::endl;
    start_time = clock_type::now();
    a = blas::gemv(b,m);
    end_time = clock_type::now();
    //std::cout<<a<<std::endl;
    elapsed = end_time-start_time;
    
    std::cout<<elapsed.count()<<std::endl;
    
    std::cout<<"Running BLAS dgemv..."<<std::endl;
    start_time = clock_type::now();
    a = dvector::create(shape_t{N});
    cblas_dgemv(CblasRowMajor,CblasTrans,
                M,N,1.,m.data(),
                N,
                b.data(),1,
                0.,a.data(),1);
    end_time = clock_type::now();
    //std::cout<<a<<std::endl;
    elapsed = end_time-start_time;

    std::cout<<elapsed.count()<<std::endl;

    return 0;
}
