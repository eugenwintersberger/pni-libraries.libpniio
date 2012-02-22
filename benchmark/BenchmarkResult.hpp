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


#ifndef __BENCHMARKRESULTS_HPP__
#define __BENCHMARKRESULTS_HPP__

#include <iostream>
#include <vector>

#include "BenchmarkConfig.hpp"

class BenchmarkResult{
    private:
        double _etime;
        double _fps;
        double _data_rate;
    public:
        BenchmarkResult(){}
        BenchmarkResult(double etime,const BenchmarkConfig &);
        BenchmarkResult(double etime,double fps,double datarate);
        
        double elapsed_time() const;
        double data_rate() const;
        double frames_per_second() const;

};

//compute the average value for the benchmar results
BenchmarkResult average(std::vector<BenchmarkResult> &results);

std::ostream &operator<<(std::ostream &o,const BenchmarkResult &r);

#endif
