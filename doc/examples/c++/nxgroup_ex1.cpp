#include<iostream>

#include<pni/nx/NX.hpp>
using namespace pni::nx::h5;

int main(int argc,char **argv){
	NXFile file;
	NXGroup group;

	file.setFileName("nxgruop_ex1.h5");
	file.setOverwrite(true);
	file.create();

	//create groups
	group = file.createGroup("data1");
	group = group.createGroup("dir");
	group = file.createGroup("data2","NXentry");
	group = file.createGroup("data3/detector/data","NXdata");

	//open existing groups
	group = file.openGroup("data1");
	group = group.openGroup("dir");

	//using attributes
	group.setAttribute("strattr","Hell world");


	return 0;
}



