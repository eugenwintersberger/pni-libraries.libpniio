#include "NXHelper.hpp"

//-----------------------------------------------------------------------------------------------
NXGroup NXHelper::createNXpositioner(NXGroup &parent,const String &n,const String
        &unit,const String &name,const String &desc){
    NXStringField sf;
    NXNumericField nf;
    
    NXGroup g = parent.createGroup(n,"NXpositioner");
    sf = g.createStringField("name"); sf<<name;
    sf = g.createStringField("description"); sf<<desc;

    nf = g.createNumericField("value",PNITypeID::FLOAT32,unit,"position");
    nf = g.createNumericField("raw_value",PNITypeID::FLOAT32,unit,"raw position");
    nf = g.createNumericField("soft_limit_min",PNITypeID::FLOAT32,unit,"lower software limit");
    nf = g.createNumericField("soft_limit_max",PNITypeID::FLOAT32,unit,"upper software limit");

    return g;
}

//------------------------------------------------------------------------------------------------
NXGroup NXHelper::createNXslit(NXGroup &parent,const String &n,const String
        &unit,const String &desc){
    NXNumericField nf;

    NXGroup g = parent.createGroup(n,"NXslit");
    g.createNumericField("center_hor",PNITypeID::FLOAT32,
                         unit,"center horizontal");
    g.createNumericField("center_ver",PNITypeID::FLOAT32,
                         unit,"center vertical");

    g.createNumericField("gap_hor",PNITypeID::FLOAT32,unit,"gap horizontal");
    g.createNumericField("gap_ver",PNITypeID::FLOAT32,unit,"gap vertical");

    NXHelper::createNXpositioner(g,"top_blade",unit,"top_blade","top blade motor");
    NXHelper::createNXpositioner(g,"bottom_blade",unit,"bottom_blade",
            "bottom blade motor");
    NXHelper::createNXpositioner(g,"left_blade",unit,"left_blade","left blade motor");
    NXHelper::createNXpositioner(g,"right_blade",unit,"right_blade","right blade motor");

    NXStringField sf = g.createStringField("description"); sf<<desc;

    return g;
}

//-------------------------------------------------------------------------------------------------
NXGroup NXHelper::createNXmirror(NXGroup &parent,const String &n){
    NXGroup g = parent.createGroup(n,"NXmirror");
    NXStringField sf;

    sf = g.createStringField("type"); sf<<"single";
    sf = g.createStringField("description"); sf<<"mirror after first slit";
    sf = g.createStringField("interior_atmosphere"); sf<<"vacuum";
    sf = g.createStringField("substrate_material"); sf<<"glass";
    sf = g.createStringField("coating_material"); sf<<"Rhodium";

    return g;
}
