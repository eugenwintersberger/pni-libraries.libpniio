#include<iostream>

#include<pni/nx/NX.hpp>
#include<pni/utils/PNITypes.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

int main(int argc,char **argv){
	ArrayShape shape(2);
	shape.setDimension(0,1024);
	shape.setDimension(1,512);

	UInt16Array data(shape);
	data = 1;

	//create the file
	NXFile file;
	NXField field;
	NXGroup group;
	file.setFileName("nxfield_ex1.h5");
	file.setOverwrite(true);
	file.create();


	//create an field that holds an array
	data.setName("detector");
	data.setUnit("cps");
	data.setDescription("a testing detector");

	//automatic from memory object
	field = file.createNumericField(data);

	//manually
	field = file.createNumericField("detector2",PNITypeID::UINT32,shape,
								    "cps","a second testing detector");









	file.close();

	return 0;
}



