#include <pni/core/types.hpp>
#include <pni/io/nexus.hpp>
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

  auto cnt = std::count_if(hdf5::node::RecursiveNodeIterator::begin(entries[0]),
                           hdf5::node::RecursiveNodeIterator::end(entries[0]),
                           nexus::IsDetector());

  std::cout<<cnt<<std::endl;
  return 0;
}
