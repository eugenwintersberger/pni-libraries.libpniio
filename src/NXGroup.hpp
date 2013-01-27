/*
 * Declaration of the NXGroup template
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of the NXGroup template
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>

#include "NXObject.hpp"
#include "NXImpMap.hpp"
#include "NXField.hpp"
#include "NXFilter.hpp"
#include "NXExceptions.hpp"
#include "NXObjectIterator.hpp"

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{

    /*! 
    \ingroup nexus_lowlevel
    \brief NXgroup object
    */
    template<typename Imp> class NXGroup:public NXObject<Imp> 
    {
        public:
            //===================public types==================================
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
            \param o original group object 
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
                create_group(const string &n,const string &type=string()) const
            {
                //we need to do here two things
                //we have to check if the particular group type
                //exists and add a check object to the class

                typedef MAPTYPE(Imp,GroupImpl) GroupImpl;

                NXGroup<GroupImpl> g(GroupImpl(n,this->imp()));

                //if the type string is not empty we write the 
                //appropriate attribute.
                if(!type.empty())
                    g.template attr<string>("NX_class").write(type);

                return g;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief create a field without filter

            Create a new data field without a filter for compression.
            \code
            NXGroup g = f["/scan_1/instrument/detector"];

            shape_t shape{0,1024,1024};
            shape_t chunk{0,128,1024};

            NField field = g.create_field<UInt16>("data",shape,chunk);
            \endcode
            The chunk shape here is optional. If not given a default value will
            be generated from the original shape where the first dimension is
            set to one. 
            \throws shape_missmatch_error if chunk and field shape do not have the
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
                create_field(const string &n,const CTYPES &shape=CTYPES(),
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
                    {
                        //chunk size provided by the user
                        cs = shape_t(chunk.size());
                        std::copy(chunk.begin(),chunk.end(),cs.begin());
                    }
                }

                FieldType field;
                try
                {
                    field = FieldType(FieldImp::template 
                                      create<T>(n,this->imp(),s,cs));
                }
                catch(shape_missmatch_error &error)
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
            \code
            NXGroup g = file["/scan_1/instrument/detector"];

            shape_t shape{0,2048,2048};
            NXDeflateFilter filter;

            NXField field = g.create_field<UInt16>("data",shape,filter);
            \endcode
            \tparam T data type for the filed
            \tparam FilterImp filter implementation (implicit)
            \tparam CTYPES container type for the field shape
            \param n name of the field
            \param s shape of the field
            \param filter implementation
            \return instance of NXField
            */
            template<typename T,typename FilterImp,typename CTYPES> 
                NXField<MAPTYPE(Imp,FieldImpl)>
                create_field(const string &n,const CTYPES &s,
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
            \code
            NXGroup g = file.create_group("scan_1/instrument/detector");

            shape_t shape{0,1024,1024};
            shape_t chunk{100,1024,0};
            NXDeflateFilter filter;

            NXField field = g.create_field<UInt16>("data",shape,chunk,filter);

            \endcode
            \throws shape_missmatch_error if the rank of chunk and field shape do
            not share the same rank
            \tparam T data type of the field
            \tparam FilterImp filter implementation type
            \tparam CTYPES container type for the shape
            \tparam CTYPEC container type for the chunk shape
            \param n name or path of the field
            \param s shape of the field
            \param cs chunk shape of the field
            \param filter filter instance to use
            \return instance of NXField
            */
            template<typename T,
                     typename FilterImp,
                     typename CTYPES,
                     typename CTYPEC
                    > 
            NXField<MAPTYPE(Imp,FieldImpl)>
                create_field(const string &n,const CTYPES &s,const CTYPEC &cs,
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
            virtual NXObject<MAPTYPE(Imp,ObjectImpl)> open(const string &n)
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
            NXObject<MAPTYPE(Imp,ObjectImpl)> operator[](const string &n) const
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
            \brief return parent object

            Return the parent object of the gruop.
            \return parent object
            */
            NXObject<MAPTYPE(Imp,ObjectImpl)> parent() const
            {
                NXObject<MAPTYPE(Imp,ObjectImpl)> g(this->imp().parent());
                return g;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open object by index

            Unlike open(const string &n) here the object is addressed by its
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

            Check if a link with name n to an object can be found below this
            group. 
            \param n name of the link (object) to look for
            \return true if the object exist, false otherwise
            */
            bool exists(const string &n) const{ return this->imp().exists(n); }

            //-----------------------------------------------------------------
            /*! \brief remove an object from the file

            Remove the link with name n to an object. As objects are not really
            delted this will only remove a particular link to an object. If this
            was the only link the object is no longer accessible. However, the
            object still exists. You have to use h5repack in order to physically
            delete the object from the file.
            \param n name of the link to delete
            */
            void remove(const string &n) const{ this->imp().remove(n); }

            //-----------------------------------------------------------------
            /*! \brief create link

            Create a new link to this very group. The link will be available
            under the new name n. 
            \code
            //create the original group
            NXGroup g1 = file.create_group("/scan_1/detector/module_01")
            
            //create a new link to this group
            g1.link("/scan_1/modules/m01");

            NXGroup g2 = file["/scan_1/modules/m01"];
            \endcode
            This method can only be used to create file local links. 
            \param n name of the new link to this object
            */
            void link(const string &n) const { this->imp().link(n); }

            //-----------------------------------------------------------------
            /*! \brief create link

            Another method to create a link. The method creates a new link to
            this object which will be available by the name n below group ref. 
            \code
            string ipath = "/scan_1/instrument/";
            string spath = "/scan_1/sample/";
            NXGroup cont = file.create_group(ipath+"motors","NXcontainer");
            NXGroup piezo = file.create_group(spath+"piezo","NXpositioner");

            piezo.link(cont,"piezo_stage");
            //get piezo under its new name
            NXGroup stage = cont["piezo_stage"];
            \endcode
            This method can only be used to create file local links.
            \param ref reference group below which the link shall be created
            \param n new name of the link
            */
            void link(const NXGroup &ref,const string &n) const
            {
                this->imp().link(ref.imp(),n);
            }

            //-----------------------------------------------------------------
            /*! create link

            Create a new link to an object determined by the path p under the
            new path n. With this method it is possible to even create external
            links. 
            Creating an internal link
            \code
            NXGroup g1 = file.create_group("/test1/data");
            NXGroup g2 = file.create_group("/test2/data");
            //create a link from g2 to /test1/data_2
            g1.link("/test2/data","/test1/data_2");
            \endcode
            Create an external link
            \code
            NXGroup g1 = file.create_group("/scan_1/instrument/detector");
            g1.link("detectordata.nx:/detector/data",g1.path()+"/data");
            \endcode
            \param p path to the object to which the link refers to
            \param n name of the link
            */
            void link(const string &p,const string &n) const
            {
                this->imp().link(p,n);
            }

            //-----------------------------------------------------------------
            /*! \brief iterator on first child

            Return an iterator on the first child stored in below the group.
            \return iterator
            */
            NXObjectIterator<NXGroup<Imp>,
                NXObject<MAPTYPE(Imp,ObjectImpl)> > begin() const
            {
                return NXObjectIterator<NXGroup<Imp>,
                       NXObject<MAPTYPE(Imp,ObjectImpl)> >(*this);
            }
          
            //-----------------------------------------------------------------
            /*! \brief iterator on last child

            Returns an iterator on the last+1 obejct stored in the group.
            \return iterator
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
}
