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
#include "NXObjectIterator.hpp"

using namespace pni::utils;

namespace pni{
    namespace nx{

        //! \ingroup nexus_lowlevel
        //! \brief NXgroup object
        template<typename Imp> class NXGroup:public NXObject<Imp> 
        {
            public:
                typedef std::shared_ptr<NXGroup<Imp> > sptr;
                typedef
                    NXObjectIterator<NXGroup<Imp>,NXObject<MAPTYPE(Imp,ObjectImpl)>
                    > iterator;
                //===========constructors and destructor========================
                /*! \brief default constructor

                */
                explicit NXGroup():NXObject<Imp>()
                {
                }

                //--------------------------------------------------------------
                /*! \brief copy constructor

                The copy constructor is doing exactly the
                same as the assignment operator. Thus it can be used to assign
                an object directly at its construction.
                */
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
                /*! \brief create a group as nexus class

                Create a new group. The optional argument type determines the 
                Nexus object type the group represents. By default type is an
                empty string in which case the NX_class attribute will not be
                written.
                \param n group name
                \param type nexus class type
                \return a new instance of NXGroup
                */
                NXGroup<MAPTYPE(Imp,GroupImpl)> 
                    create_group(const String &n,const String &type=String()) const
                {
                    EXCEPTION_SETUP("RETTYPE(NXGRoup,Imp,NXGroupImpl) "
                            "create_group(const String &n,"
                            "const String &type=String()) const");

                    //we need to do here two things
                    //we have to check if the particular group type
                    //exists and add a check object to the class

                    typedef MAPTYPE(Imp,GroupImpl) GroupImpl;

                    NXGroup<GroupImpl> g(GroupImpl(n,this->imp()));

                    //if the type string is not empty we write the 
                    //appropriate attribute.
                    if(!type.empty())
                        g.template attr<String>("NX_class").write(type);

                    return g;
                }

                //--------------------------------------------------------------
                /*! \brief create a field without filter

                */
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)>
                    create_field(const String &n,const Shape &shape=Shape(),
                                 const Shape &chunk=Shape()) const
                {
                    typedef NXField<MAPTYPE(Imp,FieldImpl)> FieldType;
                    typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                    Shape s,cs;

                    if(shape.rank() == 0){
                        //here we create a field for scalar data
                        s = Shape({1});
                        cs = s;
                    }else{
                        //a multidimensional field shall be created
                        s = shape;
                        if(chunk.rank() == 0){
                            //no explicit chunk-size by the use
                            cs = s;
                            cs.dim(0,1);
                        }else{
                            //the user requested for a particular chunk size
                            cs = chunk;
                        }
                    }

                    FieldType field(FieldImp::template create<T>(n,this->imp(),s,cs));
                    return field;
                }
                

                //--------------------------------------------------------------
                /*! \brief Creates a multidimensional field with a filter.

                */
                template<typename T,typename FilterImp> NXField<MAPTYPE(Imp,FieldImpl)>
                    create_field(const String &n,const Shape &s,
                           const NXFilter<FilterImp> &filter) const
                {
                    typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                    typedef NXField<FieldImp> FieldType;

                    //in the first place the chunk shape will be a copy 
                    //of the original shape
                    Shape cs(s);
                    //set per default the first index to 1 - so that 
                    //all other dimension vary fastest
                    cs.dim(0,1);

                    FieldType field(FieldImp::template
                            create<T>(n,this->imp(),s,cs,filter.imp()));
                    return field;
                }

               
                //--------------------------------------------------------------
                /*! \brief create a multidimensional field (explicit chunk) with filter

                */
                template<typename T,typename FilterImp> NXField<MAPTYPE(Imp,FieldImpl)>
                    create_field(const String &n,const Shape &s,const Shape &cs,
                            const NXFilter<FilterImp> &filter)
                    const
                {
                    typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                    typedef NXField<FieldImp> FieldType;

                    return FieldType(FieldImp::template
                            create<T>(n,this->imp(),s,cs,filter.imp()));
                }


                //============methods to open objects===========================
                /*! \brief open an arbitrary object

                Returns an object by name. The name can be either an absolute or 
                relative path.
                \param n path or name of the object to open
                \return object
                */
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

                //-------------------------------------------------------------
                /*! \brief open an object

                Opens an object using the [] operator. 
                \param n name or path of the object
                \return object
                */
                NXObject<MAPTYPE(Imp,ObjectImpl)> operator[](const String &n)
                    const
                {
                    return this->open(n);
                }

                //-------------------------------------------------------------
                /*! \brief number of childs

                Returns the total number of childs linke below this group.
                \return number of childs
                */
                size_t nchilds() const
                {
                    return this->imp().nchilds();
                }

                //-------------------------------------------------------------
                /*! \brief open object by index

                Unlike open(const String &n) here the object is addressed by 
                its index. Thus only objects directly linked below this group 
                can be accessed.
                \throws IndexError if the index exceeds number of childs
                \param i index of the object
                \return object
                */
                NXObject<MAPTYPE(Imp,ObjectImpl)> open(size_t i) const
                {
                    return
                        NXObject<MAPTYPE(Imp,ObjectImpl)>(this->imp().open(i));
                }

                //-------------------------------------------------------------
                /*! \brief open object by index

                Opens an object by index using the [] operator. 
                \throws IndexError if the index exceeds number of childs
                \param i index of the object
                \return object
                */
                NXObject<MAPTYPE(Imp,ObjectImpl)> operator[](size_t i) const
                {
                    return this->open(i);
                }

                //-------------------------------------------------------------
                /*! \brief check if a particular object exists

                */
                bool exists(const String &n) const{
                    return this->imp().exists(n);
                }

                //-------------------------------------------------------------
                /*! \brief remove an object from the file

                */
                void remove(const String &n) const{
                    //this->imp().remove(n);
                }

                //-------------------------------------------------------------
                /*! \brief create link

                */
                void link(const String &n) const
                {
                    this->imp().link(n);
                }

                //--------------------------------------------------------------
                /*! \brief create link

                */
                void link(const NXGroup &ref,const String &n) const
                {
                    this->imp().link(ref.imp(),n);
                }

                //--------------------------------------------------------------
                /*! create link

                */
                void link(const String &p,const String &n) const
                {
                    this->imp().link(p,n);
                }

                //--------------------------------------------------------------
                /*! \brief iterator on first element

                */
                NXObjectIterator<NXGroup<Imp>,
                    NXObject<MAPTYPE(Imp,ObjectImpl)> > begin() const
                {
                    return NXObjectIterator<NXGroup<Imp>,
                           NXObject<MAPTYPE(Imp,ObjectImpl)> >(*this);
                }
               
                /*! \brief iterator on last element

                */
                NXObjectIterator<NXGroup<Imp>,
                    NXObject<MAPTYPE(Imp,ObjectImpl)> > end() const
                {
                    return NXObjectIterator<NXGroup<Imp>,
                           NXObject<MAPTYPE(Imp,ObjectImpl)> >(*this,
                                   this->nchilds());
                }

        };


//end of namespace
    }
}


#endif /* NXGROUP_HPP_ */
