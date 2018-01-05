/*example for the library using a thread*/

#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<queue>
#include<vector>

#include <pni/core/types.hpp>
#include <pni/io/nexus.hpp>
#include <h5cpp/hdf5.hpp>
#include <boost/filesystem.hpp>

#include "ioqueue.hpp"

using namespace pni::core;
using namespace pni::io;


using StringIOQueue = IOQueue<std::string>;

class Writer
{
  private:
    boost::filesystem::path _filename;
    StringIOQueue          &_queue;
    hdf5::file::File        _file;
    hdf5::node::Dataset     _data;
    hdf5::node::Dataset     _time;
    hdf5::dataspace::Hyperslab _selection;
    size_t _index;

    //private method writing a single log entry
    void _write_entry(const string &s);

    //method creating the initial structure of the log
    void _init_log();
  public:
    Writer(const boost::filesystem::path &fname,StringIOQueue &q):
      _filename(fname),
      _queue(q),
      _file(),
      _data(),
      _selection(),
      _index(0)
    { }

    void operator()();
};

void Writer::_write_entry(const string &s)
{
  //grow the data fields by one element
  _time.extent(0,1);
  _data.extent(0,1);
  _selection.offset(0,_index);


  //write the data
  _time.write(nexus::DateTime::get_date_time_str(),_selection);
  _data.write(s,_selection);
  _index++;

  //flush the new log entry
  _file.flush(hdf5::file::Scope::LOCAL);
}

void Writer::_init_log()
{
  //create log group
  auto g = _file.root().create_group("log");

  //create a field with holding the timestamp when the
  //log was created
  hdf5::dataspace::Simple space{{0},{hdf5::dataspace::Simple::UNLIMITED}};
  auto type = hdf5::datatype::create<std::string>();

  hdf5::node::Dataset(g,"create",type,hdf5::dataspace::Scalar()).write(nexus::DateTime::get_date_time_str());

  //create log data and timestamp field
  _data = nexus::FieldFactory::create(g,"data",type,space,{1024});
  _time = nexus::FieldFactory::create(g,"timestamp",type,space,{1024});
  _selection = hdf5::dataspace::Hyperslab({0},{1});

  //flush the file after initialization
  _file.flush(hdf5::file::Scope::LOCAL);
}

void Writer::operator()()
{
  std::cout<<"create file"<<std::endl;
  //works with HDF5
  _file = nexus::create_file(_filename,hdf5::file::AccessFlags::TRUNCATE);

  //initialize the log
  _init_log();

  //write an initial log entry
  _write_entry("Starting new log");

  while(true)
  {
    string log_entry;
    _queue.blocking_pop(log_entry);
    if(log_entry == "quit") break;
    try
    {
      _write_entry(log_entry);
    }
    catch(shape_mismatch_error &e)
    {
      std::cout<<e<<std::endl;
      break;
    }
    _file.flush(hdf5::file::Scope::LOCAL);
  }


  //close the log file when finished
  _file.close();
}



class CliReader
{
    private:
        string _prompt;
        StringIOQueue &_queue;
    public:
        CliReader(const string &prompt,StringIOQueue &q):
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


int main(int ,char **)
{
    StringIOQueue q;
    Writer write("userlog.nx",q);
    CliReader cli("Nexus log $>",q);
    std::thread wthread(write);
    std::thread clithread(cli);

    //in the very end we need to join the thread
    wthread.join();
    clithread.join();

    return 0;
}    
