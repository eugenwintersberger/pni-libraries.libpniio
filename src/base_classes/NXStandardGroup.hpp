/*
 * NXStandardGroup.hpp
 *
 *  Created on: Oct 18, 2011
 *      Author: eugen
 */

#ifndef NXSTANDARDGROUP_HPP_
#define NXSTANDARDGROUP_HPP_

#include <set>

#include "../NXGroup.hpp"
#include "../NXField.hpp"
#include "BaseClassExceptions.hpp"

#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;

namespace pni{
namespace nx{

template<typename Base> class NXStandardGroup:public Base{
protected:
	std::set<String> _standard_fields;
public:
	typedef NXGroup<typename Base::GImp> GroupType;
	typedef NXField<typename Base::FImp> FieldType;
	NXStandardGroup():Base(){}
	NXStandardGroup(const NXStandardGroup<Base> &o):Base(o){}
	NXStandardGroup(const Base &o):Base(o){}
	virtual ~NXStandardGroup(){}

	virtual FieldType createStringField(const String &name) const;
	virtual FieldType createScalarField(const String &name,const PNITypeID &tid,const String &unit,const String &desc) const;
	virtual FieldType createScalarField(const ScalarObject &o) const;
	virtual GroupType createGroup(const String &n) const;

	FieldType createArrayField(const String &n, PNITypeID tid,
			 	 	 	 	 	   const ArrayShape &s,const String &unit,
			 	 	 	 	 	   const String &desc) const;
	template<typename Filter>
	FieldType createArrayField(const String &n, PNITypeID tid,
				                       const ArrayShape &s,const String &unit,
				                       const String &desc,
				                       NXFilter<Filter> &f) const;

	FieldType createArrayField(const ArrayObject &a) const;
	template<typename Filter>
	FieldType createArrayField(const ArrayObject &a,NXFilter<Filter> &f) const;

};

template<typename Base>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createStringField(const String &name) const{
	EXCEPTION_SETUP("template<typename Base> NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createStringField(const String &name"
					") const");

	if(_standard_fields.count(name)){
		//raise an exception here

	}

	return Base::createStringField(name);
}

template<typename Base>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createScalarField(const String &name,const PNITypeID &tid,
										 const String &unit,const String &desc)
										 const{
	EXCEPTION_SETUP("template<typename Base> NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createScalarField(const String &name,"
					"const PNITypeID &tid,const String &unit,const String &desc) "
					"const");

	if(_standard_fields.count(name)){
		//raise an exception here
	}

	return Base::createNumericField(name,tid,unit,desc);
}

template<typename Base>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createScalarField(const ScalarObject &o) const{
	EXCEPTION_SETUP("template<typename Base> NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createScalarField"
					"(const ScalarObject &o) const");

	if(_standard_fields.count(o.getName())){
		//raise an exception here
	}

	return Base::createNumericField(o);
}

template<typename Base>
typename NXStandardGroup<Base>::GroupType
NXStandardGroup<Base>::createGroup(const String &n) const{
	EXCEPTION_SETUP("template<typename Base> NXStandardGroup<Base>::GroupType "
					"NXStandardGroup<Base>::createGroup(const String &n) const");

	if(_standard_fields.count(n)){
		//raise an exception here
	}

	return Base::createGroup(n);
}

template<typename Base>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createArrayField(const String &n, PNITypeID tid,
		                                const ArrayShape &s,const String &unit,
		                                const String &desc) const{
	EXCEPTION_SETUP("template<typename Base> NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createArrayField(const String &n, "
					"PNITypeID tid,const ArrayShape &s,const String &unit,"
					"const String &desc) const");

	if(_standard_fields.count(n)){
		//raise an exception here
	}

	return Base::createNumericField(n,tid,s,unit,desc);
}

template<typename Base>
template<typename Filter>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createArrayField(const String &n, PNITypeID tid,
			                       	   	const ArrayShape &s,const String &unit,
			                       	   	const String &desc,NXFilter<Filter> &f)
			                       	   	const{
	EXCEPTION_SETUP("template<typename Base> template<typename Filter> "
					"NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createArrayField(const String &n, "
					"PNITypeID tid, const ArrayShape &s,const String &unit,"
					"const String &desc,NXFilter<Filter> &f) const");

	if(_standard_fields.count(n)){
		//raise an exception here
	}

	return Base::createNumericField(n,tid,s,unit,desc,f);

}

template<typename Base>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createArrayField(const ArrayObject &a) const{
	EXCEPTION_SETUP("template<typename Base> NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createArrayField"
					"(const ArrayObject &a) const");

	if(_standard_fields.count(a.getName())){
		//throw an exception here
	}

	return Base::createNumericField(a);

}

template<typename Base>
template<typename Filter>
typename NXStandardGroup<Base>::FieldType
NXStandardGroup<Base>::createArrayField(const ArrayObject &a,
										NXFilter<Filter> &f) const{
	EXCEPTION_SETUP("template<typename Base> template<typename Filter> "
					"NXStandardGroup<Base>::FieldType "
					"NXStandardGroup<Base>::createArrayField"
					"(const ArrayObject &a,NXFilter<Filter> &f) const");
	if(_standard_fields.count(a.getName())){
		//throw an exception here
	}

	return Base::createNumericField(a,f);
}


//end of namespace
}
}




#endif /* NXSTANDARDGROUP_HPP_ */
