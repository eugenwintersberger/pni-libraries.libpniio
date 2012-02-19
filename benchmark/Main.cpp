/*
    This file is part of the HDRI HDF5 benchmark suite.

    The HDRI HDF5 benchmark suite  is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software 
    Foundation, either version 2 of the License, or (at your option) any later version.

    The HDFI HDF5 benchmark suite is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.  See the NU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    the HDRI HDF5 benchmark suite. 
    If not, see <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>.
*/

#include<stdlib.h>
#include<stdio.h>

#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>

using namespace pni::utils;

/*
#include "bmark.h"
#include "run.h"
*/

#include "BenchmarkConfig.hpp"
#include "BenchmarkRun.hpp"
#include "HDF5Run.hpp"


template<typename T> double run_benchmark(const BenchmarkConfig &c)
{
   
    BenchmarkRun<T> *Run = nullptr;

    if(c.libid() == LibID::HDF5){
        std::cout<<"Instantiating HDF5 benchmark run ..."<<std::endl;
        Run = new HDF5Run<T>(c);
    }else if(c.libid() == LibID::PNINX){
        std::cerr<<"not implemented yet!"<<std::endl;
        return 0;
    }

    //run the simulation 
    for(size_t i = 0; i < c.nruns(); i++){
        double etime = Run->run();
        std::cout<<etime<<std::endl;
    }

   
    //free memory
    delete Run;

    return 0.;
}


int main(int argc,char **argv){
    
    //read configuration from the command line
    BenchmarkConfig config(argc,argv);
 
    if(config.typecode() == TypeID::UINT8) run_benchmark<UInt8>(config);
    else if(config.typecode() == TypeID::INT8) run_benchmark<Int8>(config);
    else if(config.typecode() == TypeID::UINT16) run_benchmark<UInt16>(config);
    else if(config.typecode() == TypeID::INT16) run_benchmark<Int16>(config);
    else if(config.typecode() == TypeID::UINT32) run_benchmark<UInt32>(config);
    else if(config.typecode() == TypeID::INT32) run_benchmark<Int32>(config);
    else if(config.typecode() == TypeID::UINT64) run_benchmark<UInt64>(config);
    else if(config.typecode() == TypeID::INT64) run_benchmark<Int64>(config);


    return 0;
}
