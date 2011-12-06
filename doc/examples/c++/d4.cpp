/*
 * d4.cpp
 *
 *  Created on: Nov 20, 2011
 *      Author: Eugen Wintersberger
 */

#include <iostream>
#include <map>

#include <pni/utils/PNITypes.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

#define FNAME "d4_test.h5"
#define SAMPLE "JJ0815"

typedef std::map<String,NXField> Record;

class D4File{
private:
	NXFile _file;
	NXGroup _instrument;
	NXGroup _sample;
	NXGroup _entry;
	String _sample_name;

	Record _record;

protected:
	void _setup_storage_ring();
	void _setup_bending_magnet();

public:
	D4File(const String &fname);
	virtual ~D4File();

	virtual void close();
	virtual void set_sample(const String &sample_name);
	virtual void setup_scan(const String &scan_name);

	NXField &operator[](const String &key);
};

D4File::D4File(const String &fname){
	_file.setFileName(fname);
	_file.setOverwrite(true);
	_file.create();

}

D4File::~D4File(){
	close();
}

void D4File::close(){
	_file.close();
	_record.clear();
}

void D4File::set_sample(const String &sample_name){
	_sample_name =sample_name;
}

NXField &D4File::operator[](const String &key){
	return _record[key];
}

void D4File::_setup_storage_ring(){
	NXGroup doris;
	NXNumericField nf;
    NXStringField sf;
	Float32Scalar emittance_x(410,"emittance_x","nm-rad","emittance in horizontal direction");
	Float32Scalar emittance_y(12,"emittance_y","nm-rad","emittance in vertical direction");
	Float32Scalar energy(4.45,"energy","GeV","positron energy");
	Float32Scalar current("current","mA","ring current");


	doris = _instrument.createGroup("DORIS","NXsource");
	nf = doris.createNumericField("distance",PNITypeID::FLOAT32,"m","distance to DORIS");
	nf<<Float32Scalar(40.);
	sf = doris.createStringField("name"); sf<<"DORIS";
	sf = doris.createStringField("type"); sf<<"Synchrotron X-ray Source";
	sf = doris.createStringField("probe"); sf<<"positron";
	nf = doris.createNumericField(emittance_x); nf<<emittance_x;
	nf = doris.createNumericField(emittance_y); nf<<emittance_y;
	nf = doris.createNumericField(energy); nf<<energy;

	//doris current might be written during scan
	//_record["doris_current"] = doris.createNumericField(current);
}

void D4File::_setup_bending_magnet(){

}

void D4File::setup_scan(const String &scan_name){
	NXGroup g;

	_entry = _file.createGroup(scan_name,"NXentry");
	_instrument = _entry.createGroup("D4","NXinstrument");
	_sample = _entry.createGroup(_sample_name,"NXsample");

	//setup the basic system
	_setup_storage_ring();
	_setup_bending_magnet();
}

int main(int argc,char **argv){
	D4File file(FNAME);

	file.set_sample(SAMPLE);
	file.setup_scan("scan_1");

	//run experiment
	for(UInt64 i=0;i<100;i++){
		//file["doris_current"]<<Float32Scalar(140-i*0.1,"current","mA");
	}


}




