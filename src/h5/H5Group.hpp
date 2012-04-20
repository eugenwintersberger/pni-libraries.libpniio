/*
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
 * Declaration of an HDF5 group object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5GROUP_HPP__
#define __H5GROUP_HPP__

#include <pni/utils/Types.hpp>

using namespace pni::utils;

#include "H5AttributeObject.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //class forward declarations            
            class H5Dataset;
            
            /*! \ingroup nxh5_classes
            \brief HDF5 group object
            
            Group objects are the fundamental structuring objects in the HDF5
            world. They can be identified by a path within the file and
            attributes can be attached to them. 
            */
            class H5Group:public H5AttributeObject{
                protected:
                    //! construct from object ID
                    explicit H5Group(const hid_t &oid);
                public:
                    //==========constructors and destructors===================
                    //! default constructor
                    explicit H5Group();
                    //! copy constructor
                    H5Group(const H5Group &o);
                    //! copy conversion constructor
                    H5Group(const H5Object &o);
                    //! move constructor
                    H5Group(H5Group &&o);
                    //! move conversion constructor
                    H5Group(H5Object &&o);
                    //! standard constructor
                    explicit H5Group(const String &name,const H5Group &p);
                    //! destructor
                    virtual ~H5Group();


                    //===========assignment operators==========================
                    //! copy assignment
                    H5Group &operator=(const H5Group &o);
                    //! copy conversion assignment
                    H5Group &operator=(const H5Object &o);
                    //! move assignment
                    H5Group &operator=(H5Group &&o);
                    //! move conversion assignment
                    H5Group &operator=(H5Object &&o);

                    //=============methods to open objects=====================
                    /*! open an arbitrary object

                    Opens an arbitrary object. The method takes a path to the 
                    object and returns an H5Object. As all classes derived from 
                    H5Object every other object can be constructed from such 
                    an general H5Object. 

                    The path can be either an absolute path or relative to 
                    the group instance calling this method. Both methods work as
                    expected.
                    \param n object path
                    \return HDF5 object 
                    */
                    H5Object open(const String &n) const;

                    /*! open an arbitrary object

                    Basically this does the same as the open() method.
                    \param n object path
                    \return H5Object addressed by n
                    \sa H5Object open(const String &n) const
                    */
                    H5Object operator[](const String &n) const;

                    /*! open by index
                    
                    Opens a child object below this group by its index. Unlike
                    open(const String &n) only objects linked to this group can
                    be opened with this method.
                    \throws IndexError if index exceeds number of childs
                    \param i object index
                    \return child object
                    */
                    H5Object open(size_t i) const;

                    /*! open by index

                    [] operator to obtain a child node by index;
                    \throws IndexError if index exceeds number of childs
                    \param i object index
                    \return child node
                    \sa open(size_t i)
                    */
                    H5Object operator[](size_t i) const;

                    //==============misc methods===============================
                    //! remove an object

                    //! This method removes an object attached to this 
                    void remove(const String &n);

                    /*! check for the existance of an object

                    Checks whether or not an object determined by n exists.
                    n can be either a path relative to this object or 
                    an absolute path. 
                    \param n path to the object 
                    */
                    bool exists(const String &n) const;

    
                    //! close the object
                    virtual void close();

                    /*! \brief return the parent group 

                    Returns the parent group und which this group object is 
                    linked.
                    \return parent group 
                    */
                    virtual H5Group parent() const{
                        return open(base());
                    }

                    /*! \brief create a link to this group

                    Creates a file local link pointing to this group. The new
                    path under which this group can be accessed is given by
                    path. This may either be an absolute or relative path (with
                    respect to this group).
                    \param path new link path
                    */
                    void link(const String &path) const;

                    /*! \brief create a link to this group

                    Creates a file local link to this group. The location 
                    of the link is given by path which is relative
                    to the group object ref.
                    \param ref reference group
                    \param path new link path
                    */
                    void link(const H5Group &ref,const String &path) const;

                    /*! \brief creates a local or external link

                    This method creates a link below this group from an 
                    object determined by path. The name of the link is
                    given by name. With this method also external 
                    links are possible.
                    \param path path to the object from which to link
                    \param name name of the link with respect to this group
                    */
                    void link(const String &path,const String &name) const;

                    /*! \brief number of child nodes

                    Returns the number of child nodes (groups and datasets)
                    linked below this group.
                    \return number of child nodes
                    */
                    size_t nchilds() const;

                    
                    friend class H5Dataset;                   
                    
            };


        
        //end of namespace
        }
    }
}

#endif
