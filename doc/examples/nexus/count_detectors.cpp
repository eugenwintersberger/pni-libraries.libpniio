#include <pni/types.hpp>
#include <pni/nexus.hpp>
#include <h5cpp/hdf5.hpp>

using namespace pni::core;
using namespace pni::io;

static const string file_struct = 
"<group name=\"/\" type=\"NXroot\">"
"    <group name=\"entry\" type=\"NXentry\">"
"        <group name=\"instrument\" type=\"NXinstrument\">"
"            <group name=\"pilatus\" type=\"NXdetector\"/>"
"            <group name=\"mythen\" type=\"NXdetector\"/>"
"            <group name=\"psd\" type=\"NXdetector\"/>"
"        </group>"
"    </group>"
"</group>";


int main(int,char **)
{
  hdf5::file::File file = nexus::create_file("count_detectors.nxs",
                                             hdf5::file::AccessFlags::TRUNCATE);
  hdf5::node::Group root_group = file.root();
  nexus::xml::create_from_string(root_group,file_struct);

  //get all entries from the file
  nexus::GroupList entries = nexus::get_objects(root_group,nexus::Path::from_string(":NXentry"));

  for(auto entry: entries)
  {
    std::cout<<"Predicate search: "<<nexus::search(entry,nexus::IsDetector(),true).size()<<std::endl;

    nexus::GroupList detectors = nexus::get_objects(entry,nexus::Path::from_string(":NXinstrument/:NXdetector"));
    std::cout<<"Path search: "<<detectors.size()<<std::endl;
  }

  return 0;
}
