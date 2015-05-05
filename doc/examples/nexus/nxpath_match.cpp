#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/flat_group.hpp>

#include <vector>
#include <iterator>

using namespace pni::core;
using namespace pni::io::nx;

//-----------------------------------------------------------------------------
void search_for_detectors(const h5::nxgroup &parent)
{
    typedef std::vector<h5::nxobject> object_vector;    
    
    nxpath pref = nxpath::from_string("/:NXentry/:NXinstrument/:NXdetector");
    
    auto flat_parent = make_flat(parent);
    object_vector det_vector;    
    std::copy_if(flat_parent.begin(),flat_parent.end(),
                 std::back_inserter(det_vector),
                 [&pref](const h5::nxobject &o)
                 { return match(nxpath::from_string(get_path(o)),pref);});
                 
    for(auto det: det_vector)
        std::cout<<get_path(det)<<std::endl;

}

//-----------------------------------------------------------------------------
void count_entries(const h5::nxgroup &parent)
{
    nxpath pref = nxpath::from_string("/:NXentry");
    
    size_t n = std::count_if(parent.begin(),parent.end(),
                             [&pref](const h5::nxobject &o)
                             { return match(nxpath::from_string(get_path(o)),
                                            pref);});
    
    std::cout<<"Found "<<n<<" entries in the file"<<std::endl;
      
}

//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    xml::node file_template = xml::create_from_file("nxpath_match.xml");
    
    h5::nxfile f = h5::nxfile::create_file("nxpath_match.nxs",true);
    h5::nxgroup root = f.root();    
    
    xml::xml_to_nexus(file_template,root);
    
    search_for_detectors(root);
    count_entries(root);
}

