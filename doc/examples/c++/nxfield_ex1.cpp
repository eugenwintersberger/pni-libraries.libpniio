#include<iostream>

#include<pni/nx/NX.hpp>
#include<pni/utils/PNITypes.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

int main(int argc,char **argv){
	ArrayShape shape(2);
	shape.setDimension(0,1024);
	shape.setDimension(1,512);

	UInt16Array data(shape,"detector1","cps","first detector");
	data = 1;

	//create the file
	NXFile file;
	NXField field;
	NXGroup group;
	file.setFileName("nxfield_ex1.h5");
	file.setOverwrite(true);
	file.create();

	//create groups where data shall be stored
	file.createGroup("motors");
	group = file.createGroup("detectors");

	//automatic from memory object
	field = group.createNumericField(data);

	//manually
	field = group.createNumericField("detector2",
				  PNITypeID::UINT32,shape,
				  "cps","a second testing detector");

	group = file.openGroup("motors");
	//creating scalar fields
	Float32Scalar motor("omega","degree","motor omega of goniometer");
	motor = 1.2;
	field = group.createNumericField(motor);
	field = group.createNumericField("tth",PNITypeID::FLOAT32,"degree",
			"motor tth of goniometer");

	//creating a string field
	field = file.createStringField("comments");

	file.close();

	return 0;
}



