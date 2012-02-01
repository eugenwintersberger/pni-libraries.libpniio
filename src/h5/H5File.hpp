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
 * Declaration of a HDF5 File object.
 *
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5FILE_HPP__
#define __H5FILE_HPP__

extern "C"{
#include <hdf5.h>
}

#include "H5Group.hpp"
namespace pni{
    namespace nx{
        namespace h5{
            
            //! \ingroup nxh5_classes
            //! \brief HDF5 file class
            class H5File:public H5Group {
                private:
                    H5File(const H5File &){}
                    H5File &operator=(const H5File &){
                        return *this;
                    }
                protected:
                    hid_t _create_plist; //!< property list for file creation
                    hid_t _acc_plist;    //!< property list for file access
                public:
                    //! default constructor
                    H5File();
                    //! move constructor
                    H5File(H5File &&o);
                    //! destructor
                    virtual ~H5File();

                    //! move assignment
                    H5File &operator=(H5File &&o);
                
                    virtual H5Object open(const String &n){
                        return H5Group::open(n);
                    }
                    virtual void open(const String &n,bool overwrite);
                    virtual void create(const String &n,bool overwrite,ssize_t ssize);
                    virtual void close();
                    virtual void flush() const;
                    virtual String path() const;
            };


//end of namespace
        }
    }
}

#endif /* NXFILEH5IMPLEMENTATION_HPP_ */
