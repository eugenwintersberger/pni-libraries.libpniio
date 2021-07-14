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

using namespace pni;
using namespace pni;

using Float32Frame = pni::dynamic_array<pni::float32>;

int main(int argc,char **argv){

  if(argc<2){
    std::cerr<<"Usage: cbf_reader_test <filename>"<<std::endl;
    return -1;
  }

  //get the name of the file to copen
  std::string file_name(argv[1]);


  pni::cbf_reader reader(file_name);
  pni::image_info info = reader.info(0);
  std::cout<<info<<std::endl;

  Float32Frame::storage_type buffer;
  try
  {
    buffer = reader.image<Float32Frame::storage_type>(0);
  }
  catch(pni::file_error &error)
  {
    std::cout<<error<<std::endl;
    return -1;
  }
  catch(pni::memory_allocation_error &error)
  {
    std::cerr<<error<<std::endl;
    return -1;
  }
  auto a = Float32Frame::create(pni::shape_t{info.nx(),info.ny()},buffer);

  reader.close();

  return 0;
}
