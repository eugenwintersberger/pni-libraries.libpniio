//File: count_entries.cpp
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>  
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/flat_group.hpp>
#include <algorithm>

using namespace pni::core;
using namespace pni::io::nx; 

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


int main(int argc,char **argv)
{
    //create a file and overwrite an existing file with same name
    h5::nxfile file = h5::nxfile::create_file("count_entries.nxs",true);
    auto root = file.root();

    //add structore to the file
    xml::xml_to_nexus(xml::create_from_string(file_struct),root);
    xml::xml_to_nexus(xml::create_from_string(scan_struct),
                      get_object(root,"/scan_1"));
    xml::xml_to_nexus(xml::create_from_string(scan_struct),
                      get_object(root,"/scan_2"));
    xml::xml_to_nexus(xml::create_from_string(scan_struct),
                      get_object(root,"/scan_3"));

    auto all = make_flat(root);
    auto cnt = std::count_if(all.begin(),all.end(),
               [](const h5::nxobject &o)
               { return match(get_path(o),"/:NXentry");});

    std::cout<<cnt<<std::endl;


    file.close(); //close the file
    return 0;
}
