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
 * H5LibrarySetup.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef H5LIBRARYSETUP_HPP_
#define H5LIBRARYSETUP_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Types.hpp>

using namespace pni::utils;

namespace pni {
    namespace nx {
        namespace h5 {

            /*! \ingroup nxh5_classes
            \brief HDF5 library setup

            This class holds information about the linked HDF5 library used for
            linking the project.
            */
            class H5LibrarySetup 
            {
            private:
                UInt32 _major_version_number; //!< major version number of the HDF5 library
                UInt32 _minor_version_number; //!< minor version number of the HDF5 library
                UInt32 _release_number;       //!< release version of the HDF5 library

                bool _verbose;   //!< verbose flag

            public:
                //================constructors and destructor==================
                //! default constructor
                H5LibrarySetup();
                //! destructor
                virtual ~H5LibrarySetup();

                //===================class methods=============================
                /*! \brief get version string

                Returns the full HDF5 library version as a string of the form
                \<major number\>.\<minor number\>.\<release number\>.
                \return version string
                */
                String version_string() const;

                //-------------------------------------------------------------
                /*! \brief get major number

                Returns the major version number of the HDF5 library as 
                unsigned integer.
                \return major version number
                */
                UInt32 major_number() const;

                //-------------------------------------------------------------
                /*! \brief get minor number

                Returns the minor version number of the HDF5 library as 
                unsigned integer
                \return minor version number
                */
                UInt32 minor_number() const;

                //-------------------------------------------------------------
                /*! \brief get release number

                Returns the release version of the HDF5 library as unsigned 
                integer.
                \return release version number
                */
                UInt32 release_number() const;

                //-------------------------------------------------------------
                /*! \brief set verbosity flag

                Use this method to set on and off the verbosity flag.
                \param f flag value
                */
                void verbose(bool f) { _verbose = f; }

                //-------------------------------------------------------------
                /*! \brief check verbosity

                Check whether or not the verbosity flag is set. Actually 
                the flag has no particular meaning. This is for future
                implementations.
                \return value of the verbosity flag
                */
                bool is_verbose() const { return _verbose; }
            };

            //global setup of the library - should be implemented as a singleton in future
            static H5LibrarySetup H5Setup;


        //end of namespace
        }
    }
}


#endif /* H5LIBRARYSETUP_HPP_ */
