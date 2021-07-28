//File: count_entries.cpp
#include <iostream>
#include <pni/types.hpp>
#include <pni/nexus.hpp>
#include <h5cpp/hdf5.hpp>

using namespace pni;

static const string scan_struct = 
"<group name=\"instrument\" type=\"NXinstrument\">"
"    <group name=\"detector\" type=\"NXdetector\"/>"
"    <group name=\"control\" type=\"NXmonitor\"/>"
"    <group name=\"data\" type=\"NXdata\"/>"
"</group>";

static const string file_struct = 
"<group name=\"/\" type=\"NXroot\">"
"    <group name=\"scan_1\" type=\"NXentry\"/>"
"    <group name=\"scan_2\" type=\"NXentry\"/>"
"    <group name=\"scan_3\" type=\"NXentry\"/>"
"</group>";


int main(int ,char **)
{
  //create a file and overwrite an existing file with same name
  hdf5::file::File file = nexus::create_file("count_entries.nxs",hdf5::file::AccessFlags::TRUNCATE);
  hdf5::node::Group root_group = file.root();

  nexus::xml::create_from_string(root_group,file_struct);
  nexus::xml::create_from_string(root_group.nodes["scan_1"],scan_struct);
  nexus::xml::create_from_string(root_group.nodes["scan_2"],scan_struct);
  nexus::xml::create_from_string(root_group.nodes["scan_3"],scan_struct);

  nexus::GroupList entries = nexus::search(root_group,nexus::IsEntry(),true);

  std::cout<<entries.size()<<std::endl;

  return 0;
}
