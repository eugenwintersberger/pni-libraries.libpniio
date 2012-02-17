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
                protected:
                    //! constructor from id value
                    H5File(hid_t id);
                    hid_t _create_plist; //!< property list for file creation
                    hid_t _acc_plist;    //!< property list for file access
                public:
                    //============constructors and destructors===============
                    //! default constructor
                    explicit H5File();
                    //! copy construction
                    H5File(const H5File &f);
                    //! move constructor
                    H5File(H5File &&o);
                    //! destructor
                    ~H5File();

                    //============assignment operators=======================
                    //! move assignment
                    H5File &operator=(H5File &&o);

                    //! copy assignment
                    H5File &operator=(const H5File &o);
               
                    //===========factory methods=============================
                    //! open an existing file
                    static H5File open_file(const String &n,bool ro=true);

                    //! create a new file
                    static H5File create_file(const String &n,bool ow=false,
                            ssize_t ssize=0);

                    //=============misc methods==============================
                    //! close the file
                    virtual void close();

                    //! flush the file
                    void flush() const;

                    //! obtain the path of the file
                    virtual String path() const;
            };


//end of namespace
        }
    }
}

#endif /* NXFILEH5IMPLEMENTATION_HPP_ */
