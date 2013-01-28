/*example for the library using a thread*/

#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<queue>
#include<vector>

#include<pni/core/types.hpp>
#include<pni/io/nx/nx.hpp>
#include<pni/io/nx/nxdate_time.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class io_queue
{
    private:
        std::mutex _mutex;
        std::queue<string> _queue;
        std::condition_variable _data_ready;
    public:
        void push(const string &value)
        {
            std::lock_guard<std::mutex> guard(_mutex);
            _queue.push(value);
            _data_ready.notify_one();
        }

        void blocking_pop(string &value)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _data_ready.wait(lock,[this]{ return !_queue.empty(); });
            value = _queue.front();
            _queue.pop();
        }
};


class writer
{
    private:
        string _filename;
        io_queue &_queue;
        h5::nxfile  _log_file;
        h5::nxfield _log_data;
        h5::nxfield _log_time;

        //private method writing a single log entry
        void __write_entry(const string &s){
            //grow the data fields by one element
            _log_time.grow(0);
            _log_data.grow(0);

            //write the data
            _log_time(_log_time.dim(0)-1).write(nxdate_time::get_date_time_str());
            _log_data(_log_data.dim(0)-1).write(s);

            //flush the new log entry
            _log_file.flush();
        }

        //method creating the initial structure of the log
        void __init_log(){
            //create log group
            auto g = _log_file.create_group("log");

            //create a field with holding the timestamp when the 
            //log was created
            g.create_field<string>("created")
                .write(nxdate_time::get_date_time_str());

            
            //create log data and timestamp field
            _log_data = g.create_field<string>("data",{0});
            _log_time = g.create_field<string>("timestamp",{0}); 

            //flush the file after initialization
            _log_file.flush();
        }
    public:
        writer(const string &fname,io_queue &q):
            _filename(fname),
            _queue(q)
        { }

        void operator()(){
            std::cout<<"create file"<<std::endl;
            //works with HDF5
            _log_file = h5::nxfile::create_file(_filename,true);

            //initialize the log
            __init_log();

            //write an initial log entry
            __write_entry("Starting new log");

            while(true)
            {
                string log_entry;
                _queue.blocking_pop(log_entry);
                if(log_entry == "quit") break;
                try
                {
                    __write_entry(log_entry);
                }
                catch(shape_missmatch_error &e)
                {
                    std::cout<<e<<std::endl;
                    break;
                }
                _log_file.flush();
            }


            //close the log file when finished
            _log_file.close();
        }
};

class cli_reader
{
    private:
        string _prompt;
        io_queue &_queue;
    public:
        cli_reader(const string &prompt,io_queue &q):
            _prompt(prompt),
            _queue(q)
        { }

        void operator()()
        {
            string input;
            while(true)
            {
                std::cout<<_prompt;
                std::getline(std::cin,input);
                _queue.push(input);
                if(input=="quit") break;
            }
        }
};


int main(int argc,char **argv)
{
    io_queue q;
    writer write("userlog.nx",q);
    cli_reader cli("Nexus log $>",q);
    std::thread wthread(write);
    std::thread clithread(cli);

    //in the very end we need to join the thread
    wthread.join();
    clithread.join();

    return 0;
}    
