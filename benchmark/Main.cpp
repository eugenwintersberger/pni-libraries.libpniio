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


#include "BenchmarkConfig.hpp"
#include "BenchmarkRun.hpp"
#include "BenchmarkResult.hpp"
#include "HDF5Run.hpp"
#include "PNIRun.hpp"


template<typename T> std::vector<BenchmarkResult> run_benchmark(const BenchmarkConfig &c)
{
   
    BenchmarkRun<T> *Run = nullptr;
    std::vector<BenchmarkResult> results(0);

    if(c.libid() == LibID::HDF5) Run = new HDF5Run<T>(c);
    else if(c.libid() == LibID::PNINX) Run = new PNIRun<T>(c);

    //run the simulation 
    for(size_t i = 0; i < c.nruns(); i++){
        double etime = Run->run();
        //need to compute results for every run
        BenchmarkResult r(etime,c);
        std::cout<<i<<"\t"<<r<<std::endl;
        results.push_back(r);
    }
   
    //free memory
    delete Run;

    return results;
}


int main(int argc,char **argv){
    
    //read configuration from the command line
    BenchmarkConfig config(argc,argv);
    std::vector<BenchmarkResult> result;

    std::cout<<config<<std::endl;
    if(config.typecode() == TypeID::UINT8) 
        result = run_benchmark<UInt8>(config);
    else if(config.typecode() == TypeID::INT8) 
        result = run_benchmark<Int8>(config);
    else if(config.typecode() == TypeID::UINT16) 
        result = run_benchmark<UInt16>(config);
    else if(config.typecode() == TypeID::INT16) 
        result = run_benchmark<Int16>(config);
    else if(config.typecode() == TypeID::UINT32) 
        result = run_benchmark<UInt32>(config);
    else if(config.typecode() == TypeID::INT32) 
        result = run_benchmark<Int32>(config);
    else if(config.typecode() == TypeID::UINT64) 
        result = run_benchmark<UInt64>(config);
    else if(config.typecode() == TypeID::INT64) 
        result = run_benchmark<Int64>(config);


    BenchmarkResult av = average(result);
    std::cout<<std::endl;
    std::cout<<"average: "<<std::endl;
    std::cout<<"\t"<<av<<std::endl;
    return 0;
}
