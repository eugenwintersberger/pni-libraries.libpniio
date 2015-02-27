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
// Created on: Jun 30, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <pni/core/types.hpp>
#include <pni/core/utilities.hpp>

#include "nximp_map.hpp"
#include "nxobject_traits.hpp"
#include "nxgroup.hpp"
#include "nxdate_time.hpp"


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::string;
    using pni::core::exception;

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief File object
    //! 
    //! nxfile represents a file for reading and writing data too. It is the 
    //! basic data holding entity. You can use NXField to read from or write 
    //! data to a file.
    //! 
    //! The copy and move constructors as well as the assignment operators
    //! must be implemented as the class has a non-trivial destructor.
    //!
    template<nximp_code IMPID> class nxfile
    {
        public:
            //! implementation type 
            typedef typename nximp_map<IMPID>::file_imp imp_type;
            //! Nexus file type
            typedef nxfile<IMPID>              file_type;
        private:
            //! implementation instance
            imp_type _imp; 
        public:
            //===============constructors and destructor========================
            //!
            //! \brief default constructor
            //!
            explicit nxfile():_imp() { }

            //-----------------------------------------------------------------
            //!
            //! \brief copy constrcutor
            //!
            nxfile(const file_type &file):_imp(file._imp) { }


            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            nxfile(file_type &&f):_imp(std::move(f._imp)) { }
            
            
            //-----------------------------------------------------------------
            //!
            //! \brief implemenetation move constructor
            //!
            explicit nxfile(imp_type &&imp):_imp(std::move(imp)){ }

            //-----------------------------------------------------------------
            //!
            //! \brief destructor
            //!
            ~nxfile()
            {
                if((_imp.is_valid())&&(!_imp.is_readonly()))
                {
                    auto r = root();
                    r.attributes.template create<string>("file_update_time",true)
                        .write(nxdate_time::get_date_time_str());
                    r.close();
                }
            }

                
            //================assigment operator===============================
            //!
            //! \brief copy assignment operator
            //!
            file_type &operator=(const file_type &f)
            {
                if(this == &f) return *this;
                
                _imp = f._imp;

                return *this;
            } 

            //----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //!
            file_type &operator=(file_type &&f)
            {
                if(this == &f) return *this;

                _imp = std::move(f._imp);
                return *this;
            }

            //================factory methods==================================
            //! 
            //! \brief open file
            //!
            //! Static method opening an existing file.
            //!
            //! \throws invalid_object_error if the new file object is not 
            //! valid
            //! \throws object_error in case of any other error
            //! \throws file_error if the file is not an HDF5 file
            //!
            //! \param n name of the file
            //! \param ro open read only if true
            //! \return an instance of NXFile
            //!
            static file_type open_file(const string &n,bool ro=true)
            {
                return file_type(imp_type::open(n,ro));
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief create file family
            //! 
            //! Static method to create a set of files. In the case of the HDF5
            //! backend the family driver is used and the data is distributed 
            //! over a bunch of files.
            //!
            //! \throws invalid_object_error if the newly created file object
            //! is not valid
            //! \throws io_error if attribute writing or flush fails
            //! \throws object_error in case of any other error
            //!
            //! \param n name of the file to create
            //! \param ssize split size (not implemented yet)
            //! \param ow overwrite existing file if true
            //! \return instance of NXFile
            //!
            static file_type
            create_files(const string &n,ssize_t ssize,bool ow=false)
            {
                file_type file = file_type(imp_type::create(n,ow,ssize));

                auto root_group = file.root();
                
                //set file specific attributes
                root_group.attributes.template
                    create<string>("NX_class",true).write(string("NXroot"));
                root_group.attributes.template 
                    create<string>("file_time",true).write(nxdate_time::get_date_time_str());
                root_group.attributes.template 
                    create<string>("file_update_time",true).write(nxdate_time::get_date_time_str());
                root_group.attributes.template create<string>("file_name",true).write(n);

                //this should be taken from a configuration
                root_group.attributes.template
                    create<string>("NeXus_version",true).write(string("4.3.0"));

                //flush the files content
                file.flush();

                return file;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief create single file 
            //!
            //! Creates a single file. 
            //!
            //! \throws invalid_object_error if the newly create file object is
            //! not valid
            //! \throws io_error if attribute writing failed
            //! \throws object_error if object creation failed (in any other
            //! case)
            //! \param n name of the file
            //! \param ow overwrite flag
            //! \return file instance
            static file_type
            create_file(const string &n,bool ow=false)
            {
                return create_files(n,0,ow);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief flush the file
            //!
            //! \throws io_error if flush fails
            //! \throws object_error in case of any other error
            //!
            void flush() const{ _imp.flush(); }
            
            //-----------------------------------------------------------------
            //!
            //! \brief check read only
            //!
            //! \throws invalid_object_error if file is not valid
            //! \throws file_error if the file intent cannot be retrieved
            //! \throws object_error in case of any other error
            //! 
            //! \return true if file is read-onlye, false otherwise
            //!
            bool is_readonly() const { return _imp.is_readonly(); }


            //-----------------------------------------------------------------
            //!
            //! \brief close the file
            //! 
            //! \throws type_error if there is an issue with the internal file
            //! object
            //! \throws object_error in case of any other error
            //!
            void close()
            {
                if((this->is_valid())&&(!this->is_readonly()))
                {
                    auto r = root();
                    r.attributes.template create<string>("file_update_time",true)
                        .write(nxdate_time::get_date_time_str());
                    r.close();
                }
                
                _imp.close();
            }


            //------------------------------------------------------------------
            //!
            //! \brief get root group
            //!
            //! Return the root group of the file.
            //!
            //! \throws invalid_object_error if the file is not valid
            //! \throws type_error if the group type cannot be determined
            //! \throws object_error in case of any other error
            //!
            //! \return root group of the file
            //!
            typename nxobject_trait<IMPID>::group_type root() const
            {
                typedef typename nximp_map<IMPID>::group_imp group_imp_type;
                typedef typename nxobject_trait<IMPID>::group_type group_type;

                return group_type(group_imp_type(_imp.root()));
            }

            //----------------------------------------------------------------
            //!
            //! \brief check validity
            //!
            //! \throws object_error if validity status check fails
            //! 
            //! \return true when file is valid, false otherwise
            //!
            bool is_valid() const noexcept
            {
                return _imp.is_valid(); 
            }

    };


//end of namespace
}
}
}
