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
       
#include "BenchmarkResult.hpp"

BenchmarkResult::BenchmarkResult(double etime,const BenchmarkConfig &c)
{
    _etime = etime;
    _fps = ((double)c.nframes())/etime;
    _data_rate = ((double)c.data_size())/etime/1024./1024.;
}

BenchmarkResult::BenchmarkResult(double etime,double fps,double datarate):
    _etime(etime),
    _fps(fps),
    _data_rate(datarate)
{
}
     
double BenchmarkResult::elapsed_time() const
{
    return _etime;
}

double BenchmarkResult::data_rate() const
{
    return _data_rate;
}

double BenchmarkResult::frames_per_second() const
{
    return _fps;
}

BenchmarkResult average(std::vector<BenchmarkResult> &results)
{
    double av_etime = 0;
    double av_fps = 0;
    double av_drate = 0;

    for(BenchmarkResult &r: results){
        av_etime += r.elapsed_time();
        av_drate += r.data_rate();
        av_fps   += r.frames_per_second();
    }

    return BenchmarkResult(av_etime/results.size(),
                           av_fps/results.size(),
                           av_drate/results.size());
}

std::ostream &operator<<(std::ostream &o,const BenchmarkResult &r)
{
    o<<r.elapsed_time()<<"\t"<<r.frames_per_second()<<"\t"<<
        r.data_rate();
    return o;
}
