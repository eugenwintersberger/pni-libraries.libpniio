//file: simple_ex1.cpp

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Scalar.hpp>

#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include <vector>
#include <map>
#include <iostream>

#include "NXHelper.hpp"

typedef std::map<String,NXField> file_record;
typedef std::map<String,NumericObject *> mem_record;

class Record
{
    private:
        std::
    
    public:
        //! default constructor
        Record():_sinks() {}

        void append(const String &name,const NXField &f,

        //write data to disk
        void operator() const;

};

void Record::operator() const
{
    for(auto v
}

void setup_records(NXGroup &scan,file_record &frec,mem_record &mrec){
    mrec["OMS"] = new Float32Scalar("OMS","degree","sample angle");
    mrec["TTS"] = new Float32Scalar("TTS","degree","detector angle");
    mrec["current"] = new Float32Scalar("current","mA","ring current");
    Shape shape = {2048};
    mrec["detector"] = new UInt32Array(shape,"detector","count","detector");
    
    frec["OMS"] = scan.open("sample/OMS/value");
    frec["TTS"] = scan.open("instrument/detector/TTS/value");
    frec["current"] = scan.open("instrument/DORIS/current");
    frec["detector"] = scan.open("instrument/detector/data");

}

NXGroup scan_setup(NXFile &file,const String &scan){
    NXGroup scan_group = file.create_group(scan,"NXentry");
    NXGroup ig = scan_group.create_group("instrument","NXinstrument");
    NXGroup sg = scan_group.create_group("sample","NXsample");
    NXGroup g;

    //sample
    NXHelper::createNXpositioner(sg,"XS","mm","XS","sample x-translation");
    NXHelper::createNXpositioner(sg,"OMS","degree","OMS","angle of incidence");
    NXHelper::createNXpositioner(sg,"YS","mm","YS","sample y-translation");

    //create storage ring
    g = ig.create_group("DORIS","NXsource");
    NXField f =g.create_field<Float32>("current");
    f.attr<String>("unit").write(String("mA"));
    f.attr<String>("description").write("ring current");
    
    //create detector
    Shape shape = {2048};
    g = ig.create_group("detector","NXdetector");
    
    f = g.create_field<UInt32>("data",shape);
    f.attr<String>("unit").write("count");
    f.attr<String>("description").write("detector data");
    NXHelper::createNXpositioner(g,"TTS","degree","TTS","detector scattering angle");

    return scan_group;
}

int main(int argc,char **argv){
    file_record frec;
    mem_record mrec;
    std::vector<String> rkeys;

    NXFile f = NXFile::create_file("simple_ex1.nx.h5",true,0);
    
    NXGroup scan = scan_setup(f,"scan_1");
    f.flush();
    setup_records(scan,frec,mrec);

    rkeys.push_back("OMS"); 
    rkeys.push_back("TTS");
    rkeys.push_back("current");
    rkeys.push_back("detector");

    //major scan loop
    for(size_t i=0;i<10;i++){
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
