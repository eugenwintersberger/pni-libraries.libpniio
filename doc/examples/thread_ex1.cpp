/*example for the library using a thread*/

#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<queue>
#include<vector>
#include<pni/hdf5/hdf5.h>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>
#include<pni/nx/NXDateTime.hpp>

using namespace pni::utils;
using namespace pni::nx;

class IOQueue{
    private:
        std::mutex _mutex;
        std::queue<String> _queue;
        std::condition_variable _data_ready;
    public:
        void push(const String &value){
            std::lock_guard<std::mutex> guard(_mutex);
            _queue.push(value);
            _data_ready.notify_one();
        }

        void blocking_pop(String &value)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _data_ready.wait(lock,[this]{ return !_queue.empty(); });
            value = _queue.front();
            _queue.pop();
        }
};


class Writer{
    private:
        String _filename;

        IOQueue &_queue;

        h5::NXFile  _log_file;
        h5::NXField _log_data;
        h5::NXSelection _log_datas;
        h5::NXField _log_time;
        h5::NXSelection _log_times;

        //private method writing a single log entry
        void __write_entry(const String &s){
            //grow the data fields by one element
            _log_time.grow(0);
            _log_data.grow(0);

            //update the selction offsets
            _log_times.offset(0,_log_time.dim(0)-1);
            _log_datas.offset(0,_log_data.dim(0)-1);

            //write the data
            _log_times.write(NXDateTime::get_date_time_str());
            _log_datas.write(s);

            //flush the new log entry
            _log_file.flush();
        }

        //method creating the initial structure of the log
        void __init_log(){
            //create log group
            auto g = _log_file.create_group("log");

            //create a field with holding the timestamp when the 
            //log was created
            g.create_field<String>("created")
                .write(NXDateTime::get_date_time_str());

            
            //create log data and timestamp field
            _log_data = g.create_field<String>("data",{0});
            _log_time = g.create_field<String>("timestamp",{0}); 

            //obtain selections which are used to write data
            _log_datas = _log_data.selection();
            _log_times = _log_time.selection();

            //set shape offset and stride for the log data selection
            _log_datas.shape({1});
            _log_datas.offset({0});
            _log_datas.stride({1});

            //set shape offset and stride for the log time selection
            _log_times.shape({1});
            _log_times.offset({0});
            _log_times.stride({1});

            //flush the file after initialization
            _log_file.flush();
        }
    public:
        Writer(const String &fname,IOQueue &q):
            _filename(fname),
            _queue(q)
        { }

        void operator()(){
            std::cout<<"create file"<<std::endl;
            //works with HDF5
            _log_file = h5::NXFile::create_file(_filename,true);

            //initialize the log
            __init_log();

            //write an initial log entry
            __write_entry("Starting new log");

            while(true)
            {
                String log_entry;
                _queue.blocking_pop(log_entry);
                if(log_entry == "quit") break;
                try{
                    __write_entry(log_entry);
                }catch(ShapeMissmatchError &e){
                    std::cout<<e<<std::endl;
                    break;
                }
                _log_file.flush();
            }


            //close the log file when finished
            _log_file.close();
        }
};

class CLIReader{
    private:
        String _prompt;
        IOQueue &_queue;
    public:
        CLIReader(const String &prompt,IOQueue &q):
            _prompt(prompt),
            _queue(q)
        { }

        void operator()(){
            String input;
            while(true){
                std::cout<<_prompt;
                std::getline(std::cin,input);
                _queue.push(input);
                if(input=="quit") break;
            }
        }
};


int main(int argc,char **argv)
{
    IOQueue q;
    Writer writer("userlog.nx",q);
    CLIReader cli("Nexus log $>",q);
    std::thread wthread(writer);
    std::thread clithread(cli);

    //in the very end we need to join the thread
    wthread.join();
    clithread.join();

    return 0;
}    
