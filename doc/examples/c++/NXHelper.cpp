#include "NXHelper.hpp"

//-----------------------------------------------------------------------------------------------
NXGroup NXHelper::createNXpositioner(NXGroup &parent,const String &n,const String
        &unit,const String &name,const String &desc){
    
    NXGroup g = parent.create_group(n,"NXpositioner");
    g.create_field<String>("name").write(name);
    g.create_field<String>("description").write(desc);

    NXField f = g.create_field<Float32>("value");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("position"));

    f = g.create_field<Float32>("raw_value");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("raw data value"));

    f = g.create_field<Float32>("soft_limit_min");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("lower software limit"));

    f = g.create_field<String>("soft_limit_max");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("upper software limit"));

    return g;
}

//------------------------------------------------------------------------------------------------
NXGroup NXHelper::createNXslit(NXGroup &parent,const String &n,const String
        &unit,const String &desc){

    NXGroup g = parent.create_group(n,"NXslit");
    NXField f = g.create_field<Float32>("center_hor");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("center horizontal"));

    f = g.create_field<Float32>("center_ver");
    f.attr<Float32>("unit").write(unit);
    f.attr<Float32>("description").write(String("center vertical"));

    f = g.create_field<Float32>("gap_hor");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("gap horizontal"));

    f = g.create_field<Float32>("gap_ver");
    f.attr<String>("unit").write(unit);
    f.attr<String>("description").write(String("gap vertical"));

    NXHelper::createNXpositioner(g,"top_blade",unit,"top_blade","top blade motor");
    NXHelper::createNXpositioner(g,"bottom_blade",unit,"bottom_blade","bottom blade motor");
    NXHelper::createNXpositioner(g,"left_blade",unit,"left_blade","left blade motor");
    NXHelper::createNXpositioner(g,"right_blade",unit,"right_blade","right blade motor");

    g.create_field<String>("description").write(desc);

    return g;
}

//-------------------------------------------------------------------------------------------------
NXGroup NXHelper::createNXmirror(NXGroup &parent,const String &n){
    NXGroup g = parent.create_group(n,"NXmirror");

    g.create_field<String>("type").write(String("single"));
    g.create_field<String>("description").write(String("mirror after first slit"));
    g.create_field<String>("interior_atmosphere").write(String("vacuum"));
    g.create_field<String>("substrate_material").write(String("glass"));
    g.create_field<String>("coating_material").write(String("Rhodium"));

    return g;
}
