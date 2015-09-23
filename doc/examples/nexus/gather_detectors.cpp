#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/is_class.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/xml.hpp>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>


using namespace pni::core;
using namespace pni::io::nx;

static const string file_struct = 
"<group name=\"/\" type=\"NXroot\">"
"    <group name=\"entry\" type=\"NXentry\">"
"        <group name=\"instrument\" type=\"NXinstrument\">"
"            <group name=\"detecor_01\" type=\"NXdetector\"/>"
"            <group name=\"detecor_02\" type=\"NXdetector\"/>"
"            <group name=\"detecor_03\" type=\"NXdetector\"/>"
"            <group name=\"detecor_04\" type=\"NXdetector\"/>"
"            <group name=\"detecor_05\" type=\"NXdetector\"/>"
"            <group name=\"detecor_06\" type=\"NXdetector\"/>"
"            <group name=\"detecor_07\" type=\"NXdetector\"/>"
"            <group name=\"detecor_08\" type=\"NXdetector\"/>"
"            <group name=\"detecor_09\" type=\"NXdetector\"/>"
"            <group name=\"detecor_10\" type=\"NXdetector\"/>"
"        </group>"
"    </group>"
"</group>";

int main(int,char **)
{
    //create the file structure
    h5::nxfile f = h5::nxfile::create_file("gather_detectors.nxs",true);
    auto root = f.root();
    xml::xml_to_nexus(xml::create_from_string(file_struct),root);

    //gather all the detectors
    std::vector<h5::nxgroup> detectors;

    h5::nxgroup instrument = get_object(root,"/:NXentry/:NXinstrument");
    
    std::copy_if(instrument.begin(),instrument.end(),
                 std::back_inserter(detectors),
                 [](const h5::nxobject &o)
                 { return is_class(o,"NXdetector"); });

    std::cout<<"Found "<<detectors.size()<<" detectors"<<std::endl;
    for(auto d: detectors)
        std::cout<<get_name(d)<<std::endl;

    return 0;
}
