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

#include "NXObject.hpp"
#include "NXImpMap.hpp"
#include "NXField.hpp"
#include "NXFilter.hpp"
#include "NXExceptions.hpp"
#include "NXObjectIterator.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

    /*! 
    \ingroup nexus_lowlevel
    \brief NXgroup object
    */
    template<typename Imp> class NXGroup:public NXObject<Imp> 
    {
        public:
            //! shared pointer type to a NXGroup type
            typedef std::shared_ptr<NXGroup<Imp> > shared_ptr; 
            typedef NXObjectIterator<NXGroup<Imp>,
                                     NXObject<MAPTYPE(Imp,ObjectImpl)> > 
                    iterator; //!< iterator type
            //! field type
            typedef NXField<MAPTYPE(Imp,FieldImpl)> field_type; 
            //==============constructors and destructor========================
            //! default constructor
            explicit NXGroup():NXObject<Imp>() { }

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            The copy constructor is doing exactly the same as the assignment
            operator. Thus it can be used to assign
            an object directly at its construction.
            */
            NXGroup(const NXGroup<Imp> &o):NXObject<Imp>(o) { }
            
            //-----------------------------------------------------------------
            //! move constructor
            NXGroup(NXGroup<Imp> &&o):NXObject<Imp>(std::move(o)) { }
           
            //-----------------------------------------------------------------
            //!copy construct from implementation object
            NXGroup(const Imp &imp):NXObject<Imp>(imp) { }

            //-----------------------------------------------------------------
            //! move construct from implementation object
            NXGroup(Imp &&imp):NXObject<Imp>(std::move(imp)) { }


            //-----------------------------------------------------------------
            //! copy conversion constructor
            template<typename ObjImp>
            NXGroup(const NXObject<ObjImp> &o):NXObject<Imp>(o)
            { }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~NXGroup(){ } 

            //=====================assignment operators========================
            //! copy assignment operator
            NXGroup<Imp> &operator=(const NXGroup<Imp> &o)
            {
                if(this == &o) return *this;
                NXObject<Imp>::operator=(o);
                return *this;
            }

            //-----------------------------------------------------------------
            //! copy assignment conversion operator
            template<typename ObjImp>
            NXGroup<Imp> &operator=(const NXObject<ObjImp> &o)
            {
                NXObject<Imp>::operator=(o);
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            NXGroup<Imp> &operator=(NXGroup<Imp> &&o)
            {
                if(this == &o) return *this;
                NXObject<Imp>::operator=(std::move(o));
                return *this;
            }


            //====================group creation methods=======================
            /*! 
            \brief create a group as nexus class

            Create a new group. The optional argument type determines the Nexus
            object type the group represents. By default type is an empty string
            in which case the NX_class attribute will not be written.
            \param n group name
            \param type nexus class type
            \return a new instance of NXGroup
            */
            NXGroup<MAPTYPE(Imp,GroupImpl)> 
                create_group(const String &n,const String &type=String()) const
            {
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

            //-----------------------------------------------------------------
            /*! 
            \brief create a field without filter

            \throws ShapeMissmatchError if chunk and field shape do not have the
            same rank
            \throws NXGroupError in all other cases
            \tparam T data type of the field
            \tparam CTYPES container type for the shape and chunk shape
            \param n name (path) of the field
            \param shape shape of the field
            \param chunk chunk shape of the field
            \return instane of an NXFIeld object
            */
            template<typename T, 
                     typename CTYPES=shape_t, 
                     typename CTYPEC=shape_t > 
            NXField<MAPTYPE(Imp,FieldImpl)>
                create_field(const String &n,const CTYPES &shape=CTYPES(),
                             const CTYPES &chunk=CTYPES()) const
            {
                typedef NXField<MAPTYPE(Imp,FieldImpl)> FieldType;
                typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                shape_t s,cs;

                if(shape.size() == 0)
                {
                    //here we create a field for scalar data
                    s = shape_t({1});
                    cs = s;
                }
                else
                {
                    //a multidimensional field shall be created
                    s = shape_t(shape.size());
                    std::copy(shape.begin(),shape.end(),s.begin());
                    cs = s;
                    
                    if(chunk.size() == 0)
                        //no chunk size from user
                        cs[0] = 1;
                    else
                        //chunk size provided by the user
                        std::copy(chunk.begin(),chunk.end(),cs.begin());
                }

                FieldType field;
                try
                {
                    field = FieldType(FieldImp::template 
                                      create<T>(n,this->imp(),s,cs));
                }
                catch(ShapeMissmatchError &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(...)
                {
                    throw NXGroupError(EXCEPTION_RECORD,
                                       "Something went wrong!");
                }
                return field;
            }
            

            //------------------------------------------------------------------
            /*! 
            \brief Creates a multidimensional field with a filter.

            Create a multidimensional field with a filter for data compression.
            With this method the chunk shape for the field is determined
            automatically.
            \tparam T data type for the filed
            \tparam FilterImp filter implementation (implicit)
            \tparam CTYPES container type for the field shape
            \param n name of the field
            \param s shape of the field
            \param filter implementation
            */
            template<typename T,typename FilterImp,typename CTYPES> 
                NXField<MAPTYPE(Imp,FieldImpl)>
                create_field(const String &n,const CTYPES &s,
                             const NXFilter<FilterImp> &filter) const
            {
                typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                typedef NXField<FieldImp> FieldType;

                //create a vector with the number of elements of the 
                //shape and set the first dimension to 1
                shape_t cs(s.size());
                std::copy(s.begin(),s.end(),cs.begin());
                cs[0] = 1;

                FieldType field(FieldImp::template
                        create<T>(n,this->imp(),s,cs,filter.imp()));
                return field;
            }

           
            //-----------------------------------------------------------------
            /*! 
            \brief create a multidimensional field (explicit chunk) with filter

            Create a field with filter and adjustable chunk shape.
            \tparam T data type of the field
            \tparam FilterImp filter implementation type
            \tparam CTYPES container type for the shape
            \tparam CTYPEC container type for the chunk shape
            \param n name or path of the field
            \param s shape of the field
            \param cs chunk shape of the field
            \param filter filter instance to use
            */
            template<typename T,
                     typename FilterImp,
                     typename CTYPES,
                     typename CTYPEC
                    > 
            NXField<MAPTYPE(Imp,FieldImpl)>
                create_field(const String &n,const CTYPES &s,const CTYPEC &cs,
                        const NXFilter<FilterImp> &filter) const
            {
                typedef MAPTYPE(Imp,FieldImpl) FieldImp;
                typedef NXField<FieldImp> FieldType;

                return FieldType(FieldImp::template
                        create<T>(n,this->imp(),s,cs,filter.imp()));
            }


            //===============methods to open objects===========================
            /*! 
            \brief open an arbitrary object

            Returns an object by name. The name can be either an absolute or
            relative path.
            \param n path or name of the object to open
            \return object
            */
            virtual NXObject<MAPTYPE(Imp,ObjectImpl)> open(const String &n)
                const
            {
                typedef MAPTYPE(Imp,ObjectImpl) ObjectImp;
                NXObject<ObjectImp> object;
               
                try
                {
                   object = NXObject<ObjectImp>(this->imp().open(n));
                }
                catch(...)
                {
                    throw NXGroupError(EXCEPTION_RECORD,
                          "Error opening ["+n+"] below group ["+this->path()+
                          "]!");
                }

                return object;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open an object

            Opens an object using the [] operator. 
            \param n name or path of the object
            \return object
            */
            NXObject<MAPTYPE(Imp,ObjectImpl)> operator[](const String &n) const
            {
                return this->open(n);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief number of childs

            Returns the total number of childs linke below this group.
            \return number of childs
            */
            size_t nchilds() const { return this->imp().nchilds(); }

            //-----------------------------------------------------------------
            /*! 
            \brief open object by index

            Unlike open(const String &n) here the object is addressed by its
            index. Thus only objects directly linked below this group can be
            accessed.
            \throws IndexError if the index exceeds number of childs
            \param i index of the object
            \return object
            */
            NXObject<MAPTYPE(Imp,ObjectImpl)> open(size_t i) const
            {
                return
                    NXObject<MAPTYPE(Imp,ObjectImpl)>(this->imp().open(i));
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open object by index

            Opens an object by index using the [] operator. 
            \throws IndexError if the index exceeds number of childs
            \param i index of the object
            \return object
            */
            NXObject<MAPTYPE(Imp,ObjectImpl)> operator[](size_t i) const
            {
                return this->open(i);
            }

            //-----------------------------------------------------------------
            /*! \brief check if a particular object exists

            */
            bool exists(const String &n) const{ return this->imp().exists(n); }

            //-----------------------------------------------------------------
            /*! \brief remove an object from the file

            */
            void remove(const String &n) const{ this->imp().remove(n); }

            //-----------------------------------------------------------------
            /*! \brief create link

            */
            void link(const String &n) const { this->imp().link(n); }

            //-----------------------------------------------------------------
            /*! \brief create link

            */
            void link(const NXGroup &ref,const String &n) const
            {
                this->imp().link(ref.imp(),n);
            }

            //-----------------------------------------------------------------
            /*! create link

            */
            void link(const String &p,const String &n) const
            {
                this->imp().link(p,n);
            }

            //-----------------------------------------------------------------
            /*! \brief iterator on first child

            */
            NXObjectIterator<NXGroup<Imp>,
                NXObject<MAPTYPE(Imp,ObjectImpl)> > begin() const
            {
                return NXObjectIterator<NXGroup<Imp>,
                       NXObject<MAPTYPE(Imp,ObjectImpl)> >(*this);
            }
          
            //-----------------------------------------------------------------
            /*! \brief iterator on last child

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
