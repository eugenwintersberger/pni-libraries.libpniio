#include<iostream>

#include<pni/nx/NX.hpp>
#include<pni/utils/PNITypes.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

int main(int argc,char **argv){
    //create the file
	NXFile file;
	file.setFileName("nxnumfield_ex1.h5");
	file.setOverwrite(true);
	file.create();
	
    //create a array data 
    ArrayShape shape(2);
	shape.setDimension(0,1024);
	shape.setDimension(1,512);
	UInt16Array data(shape,"detector1","cps","first detector");
	data = 1;

	//automatic from memory object
	NXNumericField field = file.createNumericField(data);

	//manually
	field = file.createNumericField("detector2",
			 	  PNITypeID::UINT32,shape,
				  "cps","a second testing detector");

	//creating fields from scalars
	Float32Scalar motor("omega","degree","motor omega of goniometer");
	motor = 1.2;
	field = file.createNumericField(motor);
	field = file.createNumericField("tth",PNITypeID::FLOAT32,"degree",
			"motor tth of goniometer");

	file.close();

	return 0;
}



