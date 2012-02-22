#include<iostream>

#include<pni/nx/NX.hpp>
#include<pni/utils/Types.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

int main(int argc,char **argv){
    //create the file
	NXFile file = NXFile::create_file("nxnumfield_ex1.h5",true,0);

    //create a array data 
    Shape shape = {1024,512};
	UInt16Array data(shape,"detector1","cps","first detector");
	data = 1;

	//automatic from memory object
	NXField field = file.create_field<UInt16>(data.name(),data.shape());

	//manually
	field = file.create_field<UInt32>("detector2",shape);

	//creating fields from scalars
	Float32Scalar motor("omega","degree","motor omega of goniometer");
	motor = 1.2;
	field = file.create_field<Float32>(motor.name());
	field = file.create_field<Float32>("tth");

	file.close();

	return 0;
}



