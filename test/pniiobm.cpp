#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <pni/core/Types.hpp>
#include <pni/core/benchmark/ChronoTimer.hpp>
#include <pni/core/benchmark/BenchmarkRunner.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include "benchmark/benchmark_factory.hpp"
#include "benchmark/file_io_benchmark.hpp"

using namespace pni::core;

int main(int argc,char **argv)
{
    typedef ChronoTimer<std::chrono::high_resolution_clock,
                        std::chrono::milliseconds> bm_timer_t;
    configuration config;
    //setup program configuration
    config.add_option(config_option<String>("backend","b",
                      "HDF5 or PNINX backend","pninx"));
    config.add_option(config_option<size_t>("nx","x",
                      "number of point along first dimension",1024));
    config.add_option(config_option<size_t>("ny","y",
                      "number of points along second dimension",1024));
    config.add_option(config_option<String>("type","t",
                      "data type to use for writing","uint8"));
    config.add_option(config_option<size_t>("nframes","n",
                      "number of frames to write per run",10));
    config.add_option(config_option<size_t>("nruns","r",
                      "number of runs to perform for the benchmark",1));
    config.add_option(config_option<String>("output","o",
                      "name of output file","pninxbm.h5"));
    config.add_option(config_option<String>("logfile","l",
                      "name of a logfile"));
                     
   
    //parse commmand line options 
    try
    {
        parse(config,argc,(const char**)argv);
    }
    catch(cli_help_request &error)
    {
        std::cerr<<config<<std::endl;
        return 1;
    }

    //create the benchmark factory
    benchmark_factory factory(config.value<String>("output"),
                              config.value<size_t>("nx"),
                              config.value<size_t>("ny"),
                              config.value<size_t>("nframes"));

    //create the bechmark
    std::unique_ptr<file_io_benchmark> bmptr =
        factory.create(config.value<String>("type"),
                       config.value<String>("backend"));

    //create the benchmark runner instance
    BenchmarkRunner runner;

    BenchmarkRunner::function_t f = std::bind(&file_io_benchmark::run,bmptr.get());
    BenchmarkRunner::function_t pre_run =
        std::bind(&file_io_benchmark::create,bmptr.get());
    BenchmarkRunner::function_t post_run = 
        std::bind(&file_io_benchmark::close,bmptr.get());

    runner.prerun(pre_run);
    runner.postrun(post_run);
    runner.run<bm_timer_t>(config.value<size_t>("nruns"),f);

    if(config.has_option("logfile"))
    {
        //open log file for writting
        std::ofstream logfile(config.value<String>("logfile"));
        
        //write header
        logfile<<"#"<<runner.begin()->unit()<<std::endl;
        for(auto res: runner)
            logfile<<res.time()<<std::endl;
    }

    //need to evaluate the results
    BenchmarkResult av_result = average(runner);
    std::cout<<av_result<<std::endl;
    



    return 0;
}
