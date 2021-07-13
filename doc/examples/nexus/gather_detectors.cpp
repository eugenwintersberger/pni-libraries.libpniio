#include <pni/core/types.hpp>
#include <pni/nexus.hpp>
#include <h5cpp/hdf5.hpp>


using namespace pni::core;
using namespace pni::io;

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
  hdf5::file::File file = nexus::create_file("gather_detectors.nxs",hdf5::file::AccessFlags::TRUNCATE);
  hdf5::node::Group root_group = file.root();
  nexus::xml::create_from_string(root_group,file_struct);

  hdf5::node::Group entry = root_group.nodes["entry"];
  nexus::GroupList detectors = nexus::search(entry,nexus::IsDetector(),true);

  std::cout<<"Found "<<detectors.size()<<" detectors"<<std::endl;
  for(auto d: detectors)
    std::cout<<d.link().path().name()<<std::endl;

  return 0;
}
