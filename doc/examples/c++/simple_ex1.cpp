//file: simple_ex1.cpp

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Scalar.hpp>

#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include <vector>
#include <map>
#include <iostream>

#include "NXHelper.hpp"

typedef std::map<String,NXNumericField *> file_record;
typedef std::map<String,NumericObject *> mem_record;

void setup_records(NXGroup &scan,file_record &frec,mem_record &mrec){
    mrec["OMS"] = new Float32Scalar("OMS","degree","sample angle");
    mrec["TTS"] = new Float32Scalar("TTS","degree","detector angle");
    mrec["current"] = new Float32Scalar("current","mA","ring current");
    ArrayShape shape(1); shape.setDimension(0,2048);
    mrec["detector"] = new UInt32Array(shape,"detector","count","detector");
    
    frec["OMS"] = new NXNumericField(std::move(scan.open("sample/OMS/value")));
    frec["TTS"] = new NXNumericField(std::move(scan.open("instrument/detector/TTS/value")));
    frec["current"] = new NXNumericField(std::move(scan.open("instrument/DORIS/current")));
    frec["detector"] = new NXNumericField(std::move(scan.open("instrument/detector/data")));

}

NXGroup scan_setup(NXFile &file,const String &scan){
    NXGroup scan_group = file.createGroup(scan,"NXentry");
    NXGroup ig = scan_group.createGroup("instrument","NXinstrument");
    NXGroup sg = scan_group.createGroup("sample","NXsample");
    NXGroup g;

    //sample
    NXHelper::createNXpositioner(sg,"XS","mm","XS","sample x-translation");
    NXHelper::createNXpositioner(sg,"OMS","degree","OMS","angle of incidence");
    NXHelper::createNXpositioner(sg,"YS","mm","YS","sample y-translation");

    //create storage ring
    g = ig.createGroup("DORIS","NXsource");
    g.createNumericField("current",PNITypeID::FLOAT32,"mA","ring current");
    
    //create detector
    ArrayShape shape(1); shape.setDimension(0,2048);
    g = ig.createGroup("detector","NXdetector");
    g.createNumericField("data",PNITypeID::UINT32,shape,"count","detector data");
    NXHelper::createNXpositioner(g,"TTS","degree","TTS","detector scattering angle");

    return scan_group;
}

int main(int argc,char **argv){
    NXFile f;
    file_record frec;
    mem_record mrec;
    std::vector<String> rkeys;

    f.setFileName("simple_ex1.nx.h5"); f.setOverwrite(true);
    f.create();

    NXGroup scan = scan_setup(f,"scan_1");
    f.flush();
    setup_records(scan,frec,mrec);

    rkeys.push_back("OMS"); 
    rkeys.push_back("TTS");
    rkeys.push_back("current");
    rkeys.push_back("detector");

    //major scan loop
    for(UInt64 i=0;i<10;i++){
        //collect data

        //save data
        for(auto key=rkeys.begin();key!=rkeys.end();key++){
            NumericObject &data = *mrec[*key];
            NXNumericField &field = *frec[*key];
           
            if(field.getElementShape().getRank()==0){
                field << (ScalarObject &) data;
            }else{
                field << (ArrayObject &) data;
            }

        }
    }

    return 0;
}
