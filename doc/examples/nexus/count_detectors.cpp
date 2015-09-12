#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/flat_group.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;

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
    h5::nxfile f = h5::nxfile::create_file("count_detectors.nxs",true);
    auto root = f.root();

    xml::xml_to_nexus(xml::create_from_string(file_struct),root);
    auto entry = get_object(root,"/:NXentry");
    auto all = make_flat(entry);

    auto cnt = std::count_if(all.begin(),all.end(),
                             [&entry](const h5::nxobject &o)
                             {
                                return
                                match(nxpath::to_string(make_relative("/:NXentry/",get_path(o))),":NXinstrument/:NXdetector");
                                });

    std::cout<<cnt<<std::endl;

    f.close();
    return 0;
}
