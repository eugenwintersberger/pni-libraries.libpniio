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
#include<pni/tiff/tiff_reader.hpp>
#include <pni/arrays.hpp>

using Float32Frame = pni::dynamic_array<pni::float32>;

int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"usage: tif_reader_test <filename>"<<std::endl;
    	return -1;
    }

    //open file for reading
    std::string filename(argv[1]);
    pni::tiff_reader reader(filename);
    std::cout<<reader.info(0)<<std::endl;
    
    
    auto buffer = reader.image<Float32Frame::storage_type>(0);
    pni::shape_t image_shape{reader.info(0).nx(),reader.info(0).ny()};
    auto array = Float32Frame::create(image_shape,buffer);

    return 0;
}
