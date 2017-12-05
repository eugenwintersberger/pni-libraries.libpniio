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

#include <pni/io/nx/nxattribute_manager.hpp>
#include <pni/io/nx/nximp_map.hpp>
#include <pni/io/nx/nxobject_traits.hpp>
#include <pni/io/nx/nxfilter.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/algorithms/as_group.hpp>


namespace pni{
namespace io{
namespace nx{

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief NXgroup object
    //! 
    //! nxgroup is the basic container in Nexus. It can hold other grous, fields
    //! and of course attributes. The attributes can be accessed via the public
    //! nxattribute_manager attribute.  The field and group children of a group 
    //! can be accessed via the container interface.
    //! nxgroup exposes an STL compliant interface and thus can be used like 
    //! many other STL containers. The value_type of nxgroup is nxobject which 
    //! is a generic object that can be converted into an attribute, field, or 
    //! group (provided it represents such an object). 
    //! As an example we use here nxgroup in a for each loop separating the 
    //! group and field children into vectors
    /*!
    nxgroup g = ....;
    std::vector<nxfield> field_vector;
    std::vector<nxgroup> group_vector;

    for(auto child: g)
    {
        if(is_field(child)) 
            field_vector.push_back(as_field(child));
        else if(is_group(child)) 
            group_vector.push_back(as_group(child));
        else 
            throw type_error(...);
    }
    */
    //! In addition we can use lambda functions along with STL lambda 
    //! functions. Consider the case where we would like to determine the 
    //! number of fields and groups in a group. This could be easily done with
    /*!
    nxgroup g = ....;
    size_t number_of_fields = std::count_if(g.begin(),g.end(),
                                            [](const nxobject &child)
                                            {return is_field(child);});
    size_t number_of_groups = std::count_if(g.begin(),g.end(),
                                            [](const nxobject &child)
                                            {return is_group(child);});
    */
    //! For a more detailed explanation about groups and field see the 
    //! user reference manual. 
    //! 
    //! \tparam IMPID implementation ID for the group
    //! \sa nxattribute_manager
    //!
    template<nximp_code IMPID> class nxgroup
    {
            
        public:
            //===================public types==================================
            //! group implementation type
            using imp_type  = typename nximp_map<IMPID>::group_imp;
            //! type implementation
            using type_type = typename nximp_map<IMPID>::type_imp;
            //! the group type
            using group_type = nxgroup<IMPID>;

            //! nxobject as container value_type
            using value_type = typename nxobject_trait<IMPID>::object_type;
            //! iterator type
            using iterator = pni::core::container_iterator<const group_type>;
            //! field type
            using field_type = typename nxobject_trait<IMPID>::field_type; 
            //! attribute type
            using attribute_type = typename nxobject_trait<IMPID>::attribute_type;
            //! link type
            using link_type = typename nxobject_trait<IMPID>::link_type;

        private:
            //! field implementation type
            using field_imp_type = typename nximp_map<IMPID>::field_imp;
            //! object implementation type
            using object_imp_type = typename nximp_map<IMPID>::object_imp;
            //! 
            //! \brief the implementation instance of nxgroup
            //!
            imp_type _imp;

            //===================private functions============================

            //!
            //! \brief automatic chunk creation
            //! 
            //! This utility function creates auomatically a chunk shape for 
            //! a given field shape. Basically, what it does is to copy the 
            //! shape and than replace the first element with a 1.
            //! 
            //! \tparam CTYPE container type for the chunk
            //! \tparam STYPE container type for the shape
            //! \param shape reference to STYPE with shape data
            //! \return instance of CTYPE with chunk data
            //! 
            template<
                     typename CTYPE,
                     typename STYPE
                    > 
            CTYPE _create_auto_chunk(const STYPE &shape) const
            {
                auto chunk = pni::core::container_utils<CTYPE>::create(shape.size());

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
            //! chunk shape configuration. This function creates a field 
            //! without a filter.
            //!
            //! \throws size_mismatch_error if chunk and shape have different 
            //! size
            //! \throws type_error if data type is not supported
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
            //!
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
            field_type _create_field(const pni::core::string &n,
                                     const CTYPE &shape,
                                     const CTYPE &chunk) const
            {
                return field_type(field_imp_type(_imp,n,
                                  pni::core::type_id_map<T>::type_id,
                                  type_type::to_index_vector(shape),
                                  type_type::to_index_vector(chunk)));

            }
           
            //----------------------------------------------------------------
            //! 
            //! \brief field creation function
            //! 
            //! This member function template is doing the real work on 
            //! creating a field. The frontend functions provided by the 
            //! public interface take only care about the shape and 
            //! chunk shape configuration. This function creates a field 
            //! with filter.
            //!
            //! \throws size_mismatch_error if chunk and shape have different 
            //! size
            //! \throws type_error if data type is not supported
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \tparam T data type of the field to create
            //! \tparam CTYPE container type for shape and chunk shape
            //! \tparam FIMP filter implementation type
            //! 
            //! \param n name of the field
            //! \param shape container with shape information
            //! \param chunk container with chunk shape data
            //! \param filter reference to a filter instance
            //! \return field instance
            //!
            template<
                      typename T,
                      typename CTYPE,
                      typename FIMP
                    > 
            field_type
            _create_field(const pni::core::string &n,const CTYPE &shape,
                         const CTYPE &chunk,
                         const nxfilter<FIMP> &filter) const
            {
                return field_type(field_imp_type(_imp,n,
                                    pni::core::type_id_map<T>::type_id,
                                    type_type::to_index_vector(shape),
                                    type_type::to_index_vector(chunk),
                                    filter.imp()));
            }
        public:
            //==================public attributes==============================
            //!
            //! \brief attribute manager
            //! 
            //! This public attribute provides access to the groups 
            //! attribute manager.
            //! \sa nxattribute_manager
            //!
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
            //!
            //! \brief move constructor
            //! 
            nxgroup(group_type &&o):
                _imp(std::move(o._imp)),
                attributes(_imp)
            { }
           
            //-----------------------------------------------------------------
            //! 
            //! \brief move construct from implementation object
            //!
            //! Construction from an implementation instance has to be done via
            //! an rvalue reference. This ensures that ownership of the 
            //! implementation object is passed over to the new nxgroup 
            //! instance.
            //! 
            //! \param imp rvalue reference to the implementation instance
            //!
            explicit nxgroup(imp_type &&imp):
                _imp(std::move(imp)),
                attributes(_imp)
            { }

            //-----------------------------------------------------------------
            //!
            //! \brief conversion constructor
            //!
            nxgroup(const typename nxobject_trait<IMPID>::object_type &o):
                _imp(),
                attributes(_imp)
            {
                *this = o;
            }

            //========================assignment operators=====================
            //!
            //! \brief copy assignment
            //!
            group_type &operator=(const group_type &g)
            {
                if(this == &g) return *this;

                _imp = g._imp;
                return *this;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief move assignment
            //!
            group_type &operator=(group_type &&g)
            {
                if(this == &g) return *this;

                _imp = std::move(g._imp);

                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief conversion assignment
            //!
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
            //! \throws invalid_object_error if parent is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param n group name
            //! \param type nexus class type
            //! \return a new instance of nxgroup
            //!
            group_type create_group(const pni::core::string &n,
                                    const pni::core::string &type=pni::core::string()) const
            {
                //we need to do here two things
                //we have to check if the particular group type
                //exists and add a check object to the class

                group_type g = group_type(imp_type(_imp,n));

                //if the type string is not empty we write the 
                //appropriate attribute.
                if(!type.empty())
                    g.attributes.template create<pni::core::string>("NX_class").write(type);

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
            //! \throws size_mismatch_error if chunk and shape have different 
            //! size
            //! \throws type_error if data type is not supported
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \tparam T data type of the field
            //! \tparam CTYPE container type for the shape
            //! \param n name of the field
            //! \param shape optional shape argument
            //! \return instance of nxfield
            //!
            template<
                     typename T,
                     typename CTYPE = pni::core::shape_t
                    >
            field_type create_field(const pni::core::string &n,
                                    const CTYPE &shape={1}) const
            {
                using namespace pni::core;
                
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
            //! \throws size_mismatch_error if chunk and shape have different 
            //! size
            //! \throws type_error if data type is not supported
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
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
                     typename CTYPE=pni::core::shape_t
                    > 
            field_type create_field(const pni::core::string &n,
                                    const CTYPE &shape,
                                    const CTYPE &chunk) const
            {
                return _create_field<T>(n,shape,chunk);
            }

            //------------------------------------------------------------------
            //! 
            //! \brief Creates a multidimensional field with a filter.
            //!
            //! Create a multidimensional field with a filter for data 
            //! compression.  With this method the chunk shape for the field 
            //! is determined automatically.
            /*!
            \code
            nxgruop g = file["/scan_1/instrument/detector"];

            shape_t shape{0,2048,2048};
            nxdeflate_filter filter;

            nxfield field = g.create_field<uint16>("data",shape,filter);
            \endcode
            */
            //!
            //! \throws size_mismatch_error if chunk and shape have different 
            //! size
            //! \throws type_error if data type is not supported
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \tparam T data type for the filed
            //! \tparam CTYPES container type for the field shape
            //!
            //! \param n name of the field
            //! \param shape shape of the field
            //! \param filter implementation
            //! \return instance of NXField
            //!
            template<
                     typename T,
                     typename CTYPES,
                     typename FIMP
                    > 
            field_type create_field(const pni::core::string &n,
                                    const CTYPES &shape,
                                    const nxfilter<FIMP> &filter) const
            {
                using namespace pni::core;
                
                if(!shape.size())
                    throw size_mismatch_error(EXCEPTION_RECORD,
                            "Shape must not be empty!");

                auto chunk = _create_auto_chunk<shape_t>(shape);

                return _create_field<T>(n,shape,chunk,filter);

            }

           
            //-----------------------------------------------------------------
            //! 
            //! \brief create a multidimensional field (explicit chunk) with filter
            //!
            //! Create a field with filter and adjustable chunk shape.
            /*!
            \code
            nxgroup g = file.create_group("scan_1/instrument/detector");

            shape_t shape{0,1024,1024};
            shape_t chunk{100,1024,0};
            nxdeflate_filter filter;

            nxfield field = g.create_field<uint16>("data",shape,chunk,filter);

            \endcode
            */
            //!
            //! \throws size_mismatch_error if chunk and shape have different 
            //! size
            //! \throws type_error if data type is not supported
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
            //! 
            //! \tparam T data type of the field
            //! \tparam CTYPES container type for the shape
            //! \tparam CTYPEC container type for the chunk shape
            //! \param n name or path of the field
            //! \param s shape of the field
            //! \param cs chunk shape of the field
            //! \param filter filter instance to use
            //! \return instance of NXField
            //!
            template<typename T,
                     typename CTYPES,
                     typename CTYPEC,
                     typename FIMP
                    > 
            field_type create_field(const pni::core::string &n,
                                    const CTYPES &s,
                                    const CTYPEC &cs,
                                    const nxfilter<FIMP> &filter) const
            {
                return _create_field<T>(n,s,cs,filter);
            }


            //===============methods to open objects===========================
            //! 
            //! \brief open an arbitrary object
            //!
            //! Returns an object by name. The name can be either an absolute 
            //! or relative path.
            //! 
            //! \throws invalid_object_error if group is not valid
            //! \throws key_error if child does not exist
            //! \throws type_error if child type is not supported
            //! \throws value_error if name contains a '/' character
            //! \throws object_error in case of any other error
            //!
            //! \param n path or name of the object to open
            //! \return object
            //!
            typename nxobject_trait<IMPID>::object_type 
            at(const pni::core::string &n) const
            {
                using namespace pni::core;
                
                if(find(n.begin(),n.end(),'/')!=n.end())
                    throw value_error(EXCEPTION_RECORD,
                            "Invalid character in object name!");

                //need to check the status of the link for the requested 
                //object - if the link is invalid we return a link
                //object.
                if(link_status(*this,n)==nxlink_status::INVALID)
                    return link_type(*this,n);


                object_imp_type object =  _imp.at(n);

                if(object.nxobject_type() == nxobject_type::NXFIELD)
                    return field_type(field_imp_type(std::move(object)));
                else if(object.nxobject_type() == nxobject_type::NXGROUP)
                    return group_type(imp_type(std::move(object)));
                else
                    throw type_error(EXCEPTION_RECORD,
                                     "Unknown Nexus object type!");

            }

            //-----------------------------------------------------------------
            //! 
            //! \brief open an object
            //! 
            //! Opens an object using the [] operator. w
            //! 
            //! \throws invalid_object_error if group is not valid
            //! \throws key_error if child does not exist
            //! \throws type_error if child type is not supported
            //! \throws value_error if name contains a '/' value error
            //! \throws object_error in case of any other error
            //!
            //! \param n name or path of the object
            //! \return object
            //!
            typename nxobject_trait<IMPID>::object_type 
            operator[](const pni::core::string &n) const
            {
                return at(n);
            }

            //----------------------------------------------------------------
            //!
            //! \brief return number of children
            //!
            //! Returns the number of children attached to this group.
            //! 
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \return number of children
            //!
            size_t size() const { return _imp.size(); }

            //-----------------------------------------------------------------
            //!
            //! \brief return parent object
            //!
            //! Return the parent object of the gruop.
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws type_error if the parents object type is unkown
            //! \throws object_error in case of any other error
            //!
            //! \return parent object
            //!
            typename nxobject_trait<IMPID>::object_type parent() const
            {
                group_type g(imp_type(_imp.parent()));
                return g;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief open object by index
            //! 
            //! Unlike open(const string &n) here the object is addressed by 
            //! its index. Thus only objects directly linked below this group 
            //! can be accessed.
            //!
            //! \throws index_error if the index exceeds number of childs
            //! \throws invalid_object_error if the group is not valid
            //! \throws type_error if the child type is not supported
            //! \throws object_error in case of any other error
            //!
            //! \param i index of the object
            //! \return object
            //!
            typename nxobject_trait<IMPID>::object_type 
            at(size_t i) const
            {
                return this->at(link_name(*this,i));
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief open object by index
            //!
            //! Opens an object by index using the [] operator. 
            //!
            //! \throws index_error if the index exceeds number of childs
            //! \throws invalid_object_error if the group is not valid
            //! \throws type_error if the child type is not supported
            //! \throws object_error in case of any other error
            //!
            //! \param i index of the object
            //! \return object
            //!
            typename nxobject_trait<IMPID>::object_type 
            operator[](size_t i) const
            {
                return this->at(i);
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief check if a particular object exists
            //!
            //! Check if a link with name n to an object can be found below 
            //! this group. 
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param n name of the link (object) to look for
            //! \return true if the object exist, false otherwise
            //!
            bool has_child(const pni::core::string &n) const
            { 
                if(n.find('/')==pni::core::string::npos)
                    return _imp.has_child(n); 
                else
                    return false;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief remove an object from the file
            //! 
            //! Remove the link with name n to an object. As objects are not 
            //! really delted this will only remove a particular link to an 
            //! object. If this was the only link the object is no longer 
            //! accessible. However, the object still exists. You have to 
            //! use h5repack in order to physically delete the object from 
            //! the file.
            //!
            //! \throws key_error if the child does not exist
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param n name of the link to delete
            //!
            void remove(const pni::core::string &n) const{ _imp.remove(n); }

            //-----------------------------------------------------------------
            //! 
            //! \brief iterator on first child
            //!
            //! Return an iterator on the first child stored in below the 
            //! group.
            //!
            //! \return iterator
            //!
            iterator begin() const noexcept { return iterator(this); }
          
            //-----------------------------------------------------------------
            //!
            //! \brief iterator on last child
            //!
            //! Returns an iterator on the last+1 obejct stored in the group.
            //! 
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \return iterator
            //!
            iterator end() const
            {
                return iterator(this, this->size());
            }

            //---------------------------------------------------------------
            //!
            //! \brief name of the group
            //! 
            //! Returns the name of the group
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws type_error if the internals object type cannot be 
            //! determined
            //! \throws io_error in case of errors during reading data
            //! \throws object_error in case of any other error
            //! 
            //! \return group name
            //!
            pni::core::string name() const { return _imp.name(); }

            //---------------------------------------------------------------
            //!
            //! \brief return filename
            //! 
            //! Returns the name of the file the group belongs too.
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if the filename information retrieval fails
            //! \throws type_error if the internal object type does not 
            //! support filename retrieval
            //! \throws object_error in case of any other error
            //!
            //! \return name of the file
            //!
            pni::core::string filename() const 
            {
                return _imp.filename();
            }

            //---------------------------------------------------------------
            //!
            //! \brief close the group
            //! 
            //! \throws type_error if the internal type could not be 
            //! determined
            //! \throws object_error in case of other errors
            //!
            void close() { _imp.close(); }

            //---------------------------------------------------------------
            //! 
            //! \brief check group validity
            //! 
            //! Returns true if the group is valid, false otherwise.
            //!
            //! \throws object_error if validity check fails
            //!
            //! \return group validity
            //!
            bool is_valid() const { return _imp.is_valid(); }

            //---------------------------------------------------------------
            //!
            //! \brief get constant reference to the implementation
            //!
            const imp_type &imp() const noexcept{ return _imp; }


    };

    //=============comparison operators====================================
    //!
    //! \ingroup nexus_lowlevel
    //! \brief group equality check
    //!
    //! Checks the equality of two groups. 
    //!
    //! \throws type_error if internal types could not be determined
    //! \throws object_error in case of any other error
    //!
    //! \param a group instance on the LHS of the operator
    //! \param b group instance on the RHS of the operator
    //! \return true if group are equal, false otherwise
    //!
    template<nximp_code IMPID>
    bool operator==(const nxgroup<IMPID> &a,const nxgroup<IMPID> &b)
    {
        if(a.imp().object() == b.imp().object()) return true;
        return false;
    }

    //-----------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief group inequality check
    //!
    //! Checks the inequality of two groups.
    //!
    //! \throws type_error if the internal types could not be determined
    //! \throws object_error in case of any other error
    //!
    //! \param a group instance on the LHS of the operator
    //! \param b group instance on the RHS of the operator
    //! \return true if not equal, false otherwise
    //!
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
