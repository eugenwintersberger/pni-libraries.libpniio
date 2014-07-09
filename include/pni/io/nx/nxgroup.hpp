//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jul 1, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/utilities.hpp>

#include "nxattribute_manager.hpp"
#include "nximp_map.hpp"
#include "nxfield.hpp"
#include "nxfilter.hpp"
#include "nxexceptions.hpp"
#include "nxlink.hpp"
#include "nxattribute.hpp"
#include "algorithms.hpp"


namespace pni{
namespace io{
namespace nx{
    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief NXgroup object
    //! 
    template<nximp_code IMPID> class nxgroup
    {
            
        public:
            //===================public types==================================
            typedef typename nximp_map<IMPID>::group_imp imp_type;
            typedef nxgroup<IMPID> group_type;

            //typedef nxobject_iterator<group_type,
            //       typename nxobject_trait<IMPID>::object_type 
             //       > iterator; //!< iterator type
            typedef typename nxobject_trait<IMPID>::object_type value_type;
            typedef pni::core::container_iterator<const group_type> iterator;
            //! field type
            typedef typename nxobject_trait<IMPID>::field_type field_type; 
            typedef typename nxobject_trait<IMPID>::attribute_type
                attribute_type;
        private:
            typedef typename nximp_map<IMPID>::field_imp field_imp_type;
            typedef typename nximp_map<IMPID>::object_imp object_imp_type;
            imp_type _imp;

            //===================private functions============================

            template<typename CTYPE,typename STYPE> 
            CTYPE _create_auto_chunk(const STYPE &shape) const
            {
                auto chunk = container_utils<CTYPE>::create(shape.size());

                std::copy(shape.begin(),shape.end(),chunk.begin());
                chunk.front()=1;

                return chunk;
            }

            //----------------------------------------------------------------
            //! 
            //! \brief field creation function
            //! 
            //! This member function template is doing the real work on 
            //! creating a field. The frontend functions provided by the 
            //! public interface take only care about the shape and 
            //! chunk shape configuration. 
            //!
            //! \throws shape_mismatch_error if shape and chunk shape do 
            //! not match
            //! \throws nxgroup_error in case of other errors
            //! \tparam T data type of the field to create
            //! \tparam CTYPE container type for shape and chunk shape
            //! \param n name of the field
            //! \param shape container with shape information
            //! \param chunk container with chunk shape data
            //! \return field instance
            //!
            template<
                     typename T,
                     typename CTYPE
                    >
            field_type _create_field(const string &n,const CTYPE &shape,
                                     const CTYPE &chunk) const
            {
                field_type field;
                try
                {
                    field = field_type(field_imp_type::template 
                                       create<T>(n,_imp,shape,chunk));
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(size_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxfield_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(type_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(...)
                {
                    throw nxgroup_error(EXCEPTION_RECORD,
                                       "Something went wrong!");
                }
                return field;

            }
           
            //----------------------------------------------------------------
            template<
                      typename T,
                      typename CHUNKT,
                      typename SHAPET,
                      typename FIMP
                    > 
            field_type
            _create_field(const string &n,const SHAPET &shape,
                         const CHUNKT &chunk,
                         const nxfilter<FIMP> &filter) const
            {
                field_type field;

                try
                {
                    field =  field_type(field_imp_type::template
                              create<T>(n,_imp,shape,chunk,filter.imp()));
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(size_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxfield_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(type_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(...)
                {
                    throw nxgroup_error(EXCEPTION_RECORD,
                                       "Something went wrong!");
                }
                return field;
            }
        public:
            //==================public attributes==============================
            nxattribute_manager<group_type> attributes;
            //==============constructors and destructor========================
            //! default constructor
            explicit nxgroup():_imp(),attributes(_imp) { }

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //! 
            //! The copy constructor is doing exactly the same as the 
            //! assignment operator. Thus it can be used to assign
            //! an object directly at its construction.
            //!
            //! \param o original group object 
            //!
            nxgroup(const group_type &o):
                _imp(o._imp),
                attributes(_imp)
            { }
            
            //-----------------------------------------------------------------
            //! move constructor
            nxgroup(group_type &&o):
                _imp(std::move(o._imp)),
                attributes(_imp)
            { }
           
            //-----------------------------------------------------------------
            //!copy construct from implementation object
            explicit nxgroup(const imp_type &imp):
                _imp(imp),
                attributes(_imp)
            { }

            //-----------------------------------------------------------------
            //! move construct from implementation object
            explicit nxgroup(imp_type &&imp):
                _imp(std::move(imp)),
                attributes(_imp)
            { }

            //-----------------------------------------------------------------
            //! conversion constructor
            nxgroup(const typename nxobject_trait<IMPID>::object_type &o):
                _imp(),
                attributes(_imp)
            {
                *this = o;
            }
        

            //-----------------------------------------------------------------
            //! destructor
            ~nxgroup(){ } 

            //========================assignment operators=====================
            group_type &operator=(const group_type &g)
            {
                if(this == &g) return *this;

                _imp = g._imp;
                return *this;
            }

            group_type &operator=(group_type &&g)
            {
                if(this == &g) return *this;

                _imp = std::move(g._imp);

                return *this;
            }

            //-----------------------------------------------------------------
            group_type &operator=(const typename
                    nxobject_trait<IMPID>::object_type &o)
            {
                *this = as_group(o);
                return  *this;
            }


            //====================group creation methods=======================
            //! 
            //! \brief create a group as nexus class
            //!
            //! Create a new group. The optional argument type determines 
            //! the Nexus object type the group represents. By default type 
            //! is an empty string in which case the NX_class attribute will 
            //! not be written.
            //!
            //! \throws pni::io::nx::nxgroup_error in case of group creation 
            //! errors
            //! \throws pni::io::nx::nxattribute_error in case of attribute 
            //! problems
            //! \param n group name
            //! \param type nexus class type
            //! \return a new instance of nxgroup
            //!
            group_type create_group(const string &n,
                                    const string &type=string()) const
            {
                //we need to do here two things
                //we have to check if the particular group type
                //exists and add a check object to the class

                group_type g;
                try
                {
                    g = group_type(imp_type(n,_imp));
                }
                catch(nxgroup_error &e)
                {
                    //a known error from the underlying implementation is 
                    //forwarded 
                    e.append(EXCEPTION_RECORD);
                    throw e;
                }
                catch(...)
                {
                    //in case of an unknown error throw a new one
                    std::stringstream ss;
                    ss<<"Error creating group ["<<n<<"] below ["<<
                                  this->path()<<"]!";
                    throw nxgroup_error(EXCEPTION_RECORD,ss.str());
                }

                //if the type string is not empty we write the 
                //appropriate attribute.
                try
                {
                    if(!type.empty())
                        g.attributes.template create<string>("NX_class").write(type);
                }
                catch(nxattribute_error &e)
                {
                    e.append(EXCEPTION_RECORD);
                    throw e;
                }
                catch(...)
                {
                    std::stringstream ss;
                    ss<<"Error creating attribute [NX_class] on";
                    ss<<" group"<<this->path()<<"!";
                    throw nxattribute_error(EXCEPTION_RECORD,ss.str());
                         
                }

                return g;
            }

            //----------------------------------------------------------------
            //!
            //! \brief create a field
            //!
            //! Create a field. The shape of the field can be specified by the 
            //! optional shape argument. By default this is set to {1} which
            //! means that an expandable scalar field will be created. 
            //! The chunk size for the field is automatically derived by the 
            //! method by replacing the first element of the shape with 1. 
            //! As an example consider the following shape for the field
            //! {100,1024,3}. This would yield a chunk size of {1,1024,3}.
            //! 
            //! If the user passes a container with shape information the 
            //! container must not be empty. Otherwise an exception 
            //! will be thrown.
            //! 
            //! \throw size_mismatch_error if shape is an empty container
            //! \throw shape_mismatch_error if chunk and shape do not match
            //! \throw nxgroup_error in case of a general error
            //! \tparam T data type of the field
            //! \tparam CTYPE container type for the shape
            //! \param n name of the field
            //! \param shape optional shape argument
            //! \return instance of nxfield
            //!
            template<
                     typename T,
                     typename CTYPE = shape_t
                    >
            field_type create_field(const string &n,
                                    const CTYPE &shape={1}) const
            {
                if(!shape.size())
                    throw size_mismatch_error(EXCEPTION_RECORD,
                            "Shape container must not be empty!");

                auto chunk = _create_auto_chunk<shape_t>(shape);
    
                return this->_create_field<T>(n,shape,chunk);
                
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief create a field 
            //!
            //! Create a new data field without a filter for compression.
            /*!
            \code
            nxgroup g = f["/scan_1/instrument/detector"];

            shape_t shape{0,1024,1024};
            shape_t chunk{1,128,1024};

            nxfield field = g.create_field<uint16>("data",shape,chunk);
            \endcode
            */
            //! The chunk shape here is optional. If not given a default 
            //! value will be generated from the original shape where the 
            //! first dimension is set to one. 
            //!
            //! \throws size_mismatch_error if chunk and field shape do not 
            //! have the same rank
            //! \throws nxgroup_error in all other cases
            //! 
            //! \tparam T data type of the field
            //! \tparam CTYPE container type for the shape and chunk
            //! \param n name (path) of the field
            //! \param shape shape of the field
            //! \param chunk chunk shape of the field
            //! \return instane of an nxfield object
            //!
            template<
                     typename T, 
                     typename CTYPE=shape_t
                    > 
            field_type create_field(const string &n,
                                    const CTYPE &shape,
                                    const CTYPE &chunk) const
            {
                return _create_field<T>(n,shape,chunk);
            }

            //------------------------------------------------------------------
            /*! 
            \brief Creates a multidimensional field with a filter.

            Create a multidimensional field with a filter for data compression.
            With this method the chunk shape for the field is determined
            automatically.
            \code
            nxgruop g = file["/scan_1/instrument/detector"];

            shape_t shape{0,2048,2048};
            nxdeflate_filter filter;

            nxfield field = g.create_field<uint16>("data",shape,filter);
            \endcode
            \tparam T data type for the filed
            \tparam CTYPES container type for the field shape
            \param n name of the field
            \param s shape of the field
            \param filter implementation
            \return instance of NXField
            */
            template<
                     typename T,
                     typename CTYPES,
                     typename FIMP
                    > 
            field_type create_field(const string &n,const CTYPES &shape,
                                    const nxfilter<FIMP> &filter) const
            {
                if(!shape.size())
                    throw size_mismatch_error(EXCEPTION_RECORD,
                            "Shape must not be empty!");

                auto chunk = _create_auto_chunk<shape_t>(shape);

                return _create_field<T>(n,shape,chunk,filter);

            }

           
            //-----------------------------------------------------------------
            /*! 
            \brief create a multidimensional field (explicit chunk) with filter

            Create a field with filter and adjustable chunk shape.
            \code
            nxgroup g = file.create_group("scan_1/instrument/detector");

            shape_t shape{0,1024,1024};
            shape_t chunk{100,1024,0};
            nxdeflate_filter filter;

            nxfield field = g.create_field<uint16>("data",shape,chunk,filter);

            \endcode
            \throws shape_mismatch_error if the rank of chunk and field shape do
            not share the same rank
            \tparam T data type of the field
            \tparam CTYPES container type for the shape
            \tparam CTYPEC container type for the chunk shape
            \param n name or path of the field
            \param s shape of the field
            \param cs chunk shape of the field
            \param filter filter instance to use
            \return instance of NXField
            */
            template<typename T,
                     typename CTYPES,
                     typename CTYPEC,
                     typename FIMP
                    > 
            field_type create_field(const string &n,const CTYPES &s,
                                    const CTYPEC &cs,
                                    const nxfilter<FIMP> &filter) const
            {
                return _create_field<T>(n,s,cs,filter);
            }


            //===============methods to open objects===========================
            /*! 
            \brief open an arbitrary object

            Returns an object by name. The name can be either an absolute or
            relative path.
            \param n path or name of the object to open
            \return object
            */
            virtual 
            typename nxobject_trait<IMPID>::object_type open(const string &n) const
            {
                object_imp_type object; 
                try
                {
                   object = _imp.open(n);
                }
                catch(...)
                {
                    throw nxgroup_error(EXCEPTION_RECORD,
                          "Error opening ["+n+"] below group ["+this->path()+
                          "]!");
                }

                if(object.nxobject_type() == nxobject_type::NXFIELD)
                    return field_type(field_imp_type(object));
                else if(object.nxobject_type() == nxobject_type::NXGROUP)
                    return group_type(imp_type(object));
                else
                    throw type_error(EXCEPTION_RECORD,
                                     "Unknown Nexus object type!");

            }

            //-----------------------------------------------------------------
            /*! 
            \brief open an object

            Opens an object using the [] operator. 
            \param n name or path of the object
            \return object
            */
            typename nxobject_trait<IMPID>::object_type 
            operator[](const string &n) const
            {
                return this->open(n);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief number of childs

            Returns the total number of childs linke below this group.
            \return number of childs
            */
            size_t nchildren() const { return _imp.nchildren(); }
            size_t size() const { return _imp.nchildren(); }

            //-----------------------------------------------------------------
            /*!
            \brief return parent object

            Return the parent object of the gruop.
            \return parent object
            */
            group_type parent() const
            {
                group_type g(imp_type(_imp.parent()));
                return g;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open object by index

            Unlike open(const string &n) here the object is addressed by its
            index. Thus only objects directly linked below this group can be
            accessed.
            \throws index_error if the index exceeds number of childs
            \param i index of the object
            \return object
            */
            typename nxobject_trait<IMPID>::object_type open(size_t i) const
            {
                object_imp_type obj_imp; 
                obj_imp = _imp.open(i);

                if(obj_imp.nxobject_type() == nxobject_type::NXFIELD)
                    return field_type(field_imp_type(obj_imp));
                else if(obj_imp.nxobject_type() == nxobject_type::NXGROUP)
                    return group_type(imp_type(obj_imp));
                else 
                    throw type_error(EXCEPTION_RECORD,
                                     "Unkown NEXUS object type!");
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open object by index

            Opens an object by index using the [] operator. 
            \throws index_error if the index exceeds number of childs
            \param i index of the object
            \return object
            */
            typename nxobject_trait<IMPID>::object_type operator[](size_t i) const
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
            bool exists(const string &n) const{ return _imp.exists(n); }

            //-----------------------------------------------------------------
            /*! \brief remove an object from the file

            Remove the link with name n to an object. As objects are not really
            delted this will only remove a particular link to an object. If this
            was the only link the object is no longer accessible. However, the
            object still exists. You have to use h5repack in order to physically
            delete the object from the file.
            \param n name of the link to delete
            */
            void remove(const string &n) const{ _imp.remove(n); }

            //-----------------------------------------------------------------
            /*! \brief create link

            Create a new link to this very group. The link will be available
            under the new name n. 
            \code
            //create the original group
            nxgroup g1 = file.create_group("/scan_1/detector/module_01")
            
            //create a new link to this group
            g1.link("/scan_1/modules/m01");

            nxgroup g2 = file["/scan_1/modules/m01"];
            \endcode
            This method can only be used to create file local links. 
            \param n name of the new link to this object
            */
            void link(const string &n) const { _imp.link(n); }

            //-----------------------------------------------------------------
            /*! \brief create link

            Another method to create a link. The method creates a new link to
            this object which will be available by the name n below group ref. 
            \code
            string ipath = "/scan_1/instrument/";
            string spath = "/scan_1/sample/";
            nxgroup cont = file.create_group(ipath+"motors","NXcontainer");
            nxgroup piezo = file.create_group(spath+"piezo","NXpositioner");

            piezo.link(cont,"piezo_stage");
            //get piezo under its new name
            nxgroup stage = cont["piezo_stage"];
            \endcode
            This method can only be used to create file local links.
            \param ref reference group below which the link shall be created
            \param n new name of the link
            */
            void link(const nxgroup &ref,const string &n) const
            {
                _imp.link(ref.imp(),n);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief create link

            Create a new link to an object determined by the path p under the
            new path n. With this method it is possible to even create external
            links. 
            Creating an internal link
            \code
            nxgroup g1 = file.create_group("/test1/data");
            nxgroup g2 = file.create_group("/test2/data");
            //create a link from g2 to /test1/data_2
            g1.link("/test2/data","/test1/data_2");
            \endcode
            Create an external link
            \code
            nxgroup g1 = file.create_group("/scan_1/instrument/detector");
            g1.link("detectordata.nx:/detector/data",g1.path()+"/data");
            \endcode
            \param p path to the object to which the link refers to
            \param n name of the link
            */
            void link(const string &p,const string &n) const
            {
                _imp.link(p,n);
            }

            //-----------------------------------------------------------------
            /*! \brief iterator on first child

            Return an iterator on the first child stored in below the group.
            \return iterator
            */
            iterator begin() const
            {
                return iterator(this);
            }
          
            //-----------------------------------------------------------------
            /*! \brief iterator on last child

            Returns an iterator on the last+1 obejct stored in the group.
            \return iterator
            */
            iterator end() const
            {
                return iterator(this, this->size());
            }

            //----------------------------------------------------------------
            string path() const { return _imp.path(); }

            //----------------------------------------------------------------
            string base() const { return _imp.base(); }

            //---------------------------------------------------------------
            string name() const { return _imp.name(); }

            //---------------------------------------------------------------
            void close() { _imp.close(); }

            //---------------------------------------------------------------
            bool is_valid() const noexcept { return _imp.is_valid(); }

            //---------------------------------------------------------------
            const imp_type &imp() const { return _imp; }

            //---------------------------------------------------------------
            nxobject_type object_type() const { return _imp.nxobject_type(); }

    };

    //=============comparison operators====================================
    template<nximp_code IMPID>
    bool operator==(const nxgroup<IMPID> &a,const nxgroup<IMPID> &b)
    {
        if(a.imp() == b.imp()) return true;
        return false;
    }

    template<nximp_code IMPID>
    bool operator!=(const nxgroup<IMPID> &a,const nxgroup<IMPID> &b)
    {
        if(a == b) return false;
        return true;
    }


//end of namespace
}
}
}
