/*
 * Declaration of the NXGroup template
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of the NXGroup template
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXGROUP_HPP_
#define NXGROUP_HPP_

#include <pni/utils/Types.hpp>
#include <pni/utils/Shape.hpp>

#include "NXObject.hpp"
#include "NXImpMap.hpp"
#include "NXField.hpp"
#include "NXFilter.hpp"
#include "NXExceptions.hpp"

using namespace pni::utils;

namespace pni{
    namespace nx{

        //! \ingroup nexus_lowlevel
        //! \brief NXgroup object
        template<typename Imp> class NXGroup:public NXObject<Imp> 
        {
            public:
                typedef std::shared_ptr<NXGroup<Imp> > sptr;
                //===========constructors and destructor========================
                //! default constructor
                explicit NXGroup():NXObject<Imp>()
                {
                }

                //--------------------------------------------------------------
                //! copy constructor

                //! The copy constructor is doing exactly the
                //! same as the assignment operator. Thus it can be used to assign
                //! an object directly at its construction.
                NXGroup(const NXGroup<Imp> &o):NXObject<Imp>(o)
                {
                }
                
                //--------------------------------------------------------------
                //! move constructor
                NXGroup(NXGroup<Imp> &&o):NXObject<Imp>(std::move(o))
                {
                }
               
                //--------------------------------------------------------------
                //!copy construct from implementation object
                NXGroup(const Imp &imp):NXObject<Imp>(imp)
                {
                }

                //--------------------------------------------------------------
                //! move construct from implementation object
                NXGroup(Imp &&imp):NXObject<Imp>(std::move(imp))
                {
                }


                //--------------------------------------------------------------
                //! copy conversion constructor
                template<typename ObjImp>
                NXGroup(const NXObject<ObjImp> &o):NXObject<Imp>(o)
                {
                }



                //--------------------------------------------------------------
                //! destructor
                virtual ~NXGroup(){
                }

                //==================assignment operators========================
                //! copy assignment operator
                NXGroup<Imp> &operator=(const NXGroup<Imp> &o)
                {
                    if(this == &o) return *this;
                    NXObject<Imp>::operator=(o);
                    return *this;
                }

                //--------------------------------------------------------------
                //! copy assignment conversion operator
                template<typename ObjImp>
                NXGroup<Imp> &operator=(const NXObject<ObjImp> &o)
                {
                    NXObject<Imp>::operator=(o);
                    return *this;
                }

                //--------------------------------------------------------------
                //! move assignment operator
                NXGroup<Imp> &operator=(NXGroup<Imp> &&o)
                {
                    if(this == &o) return *this;
                    NXObject<Imp>::operator=(std::move(o));
                    return *this;
                }


                //=================group creation methods=======================
                //! create a simple group

                //! Creates a simple group in the Nexus data tree. No class
                //! attribute is attached to this kind of group.
                //! \param n name of the group
                NXGroup<MAPTYPE(Imp,GroupImpl)> create_group(const String &n) const
                {
                    EXCEPTION_SETUP("RETTYPE(NXGroup,Imp,NXGroupImpl) "
                            "create_group(const String &n) const");
                    typedef MAPTYPE(Imp,GroupImpl) GroupImpl;
                   
                    NXGroup<GroupImpl> g(GroupImpl(n,this->imp()));

                    return g;
                }
               
                //--------------------------------------------------------------
                //! create a group as nexus class

                //! Create a group that represents a Nexus class. 
                //! \param n group name
                //! \param type nexus class type
                NXGroup<MAPTYPE(Imp,GroupImpl)> 
                    create_group(const String &n,const String &type) const
                {
                    EXCEPTION_SETUP("RETTYPE(NXGRoup,Imp,NXGroupImpl) "
                            "create_group(const String &n,const String &type)"
                            "const");

                    //we need to do here two things
                    //we have to check if the particular group type
                    //exists and add a check object to the class

                    typedef MAPTYPE(Imp,GroupImpl) GroupImpl;

                    NXGroup<GroupImpl> g(GroupImpl(n,this->imp()));
                    g.template attr<String>("NX_class").write(type);

                    return g;
                }

                //--------------------------------------------------------------
                //! create a scalar field

                //! Create a field 
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)>
                    create_field(const String &n) const
                {
                    typedef NXField<MAPTYPE(Imp,FieldImpl)> FieldType;
                    typedef MAPTYPE(Imp,FieldImpl) FieldImp;


                    Shape s = {1};
                    Shape cs = {1};

                    FieldType field(FieldImp::template create<T>(n,this->imp(),s,cs));
                    return field;
                }
                
                //--------------------------------------------------------------
                //! create a multidimensional field

                //! Create a multidimensional field of shape s. The field 
                //! can be extended in any direction. 
                //! \param n name of the field
                //! \param s shape of the field
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)>
                    create_field(const String &n,const Shape &s) const
                {
                    typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                    typedef NXField<FieldImp> FieldType;

                    //in the first place the chunk shape will be a copy 
                    //of the original shape
                    Shape cs(s);
                    //set per default the first index to 1 - so that 
                    //all other dimension vary fastest
                    cs.dim(0,1);

                    FieldType field(FieldImp::template create<T>(n,this->imp(),s,cs));
                    return field;
                }

                //! create a multidimensional field (explicit chunk)
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)>
                    create_field(const String &n,const Shape &s,const Shape &cs)
                    const
                {
                    typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                    typedef NXField<FieldImp> FieldType;

                    return FieldType(FieldImp::template create<T>(n,this->imp(),s,cs));
                }

                //! create a multidi

                //============methods to open objects===========================
                //! open an arbitrary object
                virtual NXObject<MAPTYPE(Imp,ObjectImpl)> open(const String &n)
                    const
                {
                    EXCEPTION_SETUP("virtual NXObject<MAPTYPE(Imp,ObjectImpl)>"
                            " open(const String &n) const");

                    typedef MAPTYPE(Imp,ObjectImpl) ObjectImp;
                    NXObject<ObjectImp> object;
                   
                    try{
                       object = NXObject<ObjectImp>(this->imp().open(n));
                    }catch(...){
                        EXCEPTION_INIT(NXGroupError,"Error opening object!");
                        EXCEPTION_THROW();
                    }

                    return object;
                }

                //! check if a particular object exists
                bool exists(const String &n) const{
                    return this->imp().exists(n);
                }

                //! remove an object from the file
                void remove(const String &n) const{
                    //this->imp().remove(n);
                }

                //! create link

                void link(const String &n) const
                {
                    this->imp().link(n);
                }

                //! create link
                void link(const NXGroup &ref,const String &n) const
                {
                    this->imp().link(ref.imp(),n);
                }

                //! create link
                void link(const String &p,const String &n) const
                {
                    this->imp().link(p,n);
                }



        };


//end of namespace
    }
}


#endif /* NXGROUP_HPP_ */
