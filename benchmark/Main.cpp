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

/*
#include "bmark.h"
#include "run.h"
*/

#include "BenchmarkConfig.hpp"
#include "BenchmarkRun.hpp"
#include "HDF5Run.hpp"


template<typename T> double run_benchmark(const BenchmarkConfig &c)
{
    HDF5Run<T> benchmark(c);

    return benchmark.run();
}


int main(int argc,char **argv){
    String filename;
    
    unsigned long run;
    unsigned long i = 0;

    //read configuration from the command line
    BenchmarkConfig config(argc,argv);
 

    run_benchmark<UInt8>(config);

    return 0;
}
