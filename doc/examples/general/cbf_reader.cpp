/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>
#include<cmath>


#include <pni/cbf/cbf_reader.hpp>
#include <pni/image_info.hpp>
#include <pni/arrays.hpp>
#include <pni/error.hpp>

using namespace pni::core;
using namespace pni::io;

using Float32Frame = pni::core::dynamic_array<pni::core::float32>;

int main(int argc,char **argv){

  if(argc<2){
    std::cerr<<"Usage: cbf_reader_test <filename>"<<std::endl;
    return -1;
  }

  //get the name of the file to copen
  std::string file_name(argv[1]);


  pni::io::cbf_reader reader(file_name);
  pni::io::image_info info = reader.info(0);
  std::cout<<info<<std::endl;

  Float32Frame::storage_type buffer;
  try
  {
    buffer = reader.image<Float32Frame::storage_type>(0);
  }
  catch(pni::core::file_error &error)
  {
    std::cout<<error<<std::endl;
    return -1;
  }
  catch(pni::core::memory_allocation_error &error)
  {
    std::cerr<<error<<std::endl;
    return -1;
  }
  auto a = Float32Frame::create(pni::core::shape_t{info.nx(),info.ny()},buffer);

  reader.close();

  return 0;
}
