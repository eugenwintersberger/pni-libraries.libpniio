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
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    /*! 
    \ingroup nexus_lowlevel
    \brief File object

    NXFile represents a file for reading and writing data too. It is the basic
    data holding entity. You can use NXField to read from or write data to a
    file.
    */
    template<nximp_code IMPID> class nxfile
    {
        public:
            typedef typename nximp_map<IMPID>::file_imp imp_type;
            typedef nxfile<IMPID>              file_type;
        private:
            //! implementation instance
            imp_type _imp; 
        public:
            //===============constructors and destructor========================
            //! default constructor
            explicit nxfile():_imp() { }

            //-----------------------------------------------------------------
            //! copy constrcutor
            nxfile(const file_type &file):_imp(file._imp) { }

            //-----------------------------------------------------------------
            //! implemenetation move constructor
            explicit nxfile(imp_type &&imp):_imp(std::move(imp)){ }

            //-----------------------------------------------------------------
            //! move constructor
            nxfile(file_type &&f):_imp(std::move(f._imp)) { }

            //-----------------------------------------------------------------
            //! destructor
            ~nxfile()
            {
                if((_imp.is_valid())&&(!_imp.is_readonly()))
                {
                    auto r = root();
                    r.template attr<string>("file_update_time",true)
                        .write(nxdate_time::get_date_time_str());
                    r.close();
                }
            }

            //================assigment operator===============================
            file_type &operator=(const file_type &f)
            {
                if(this == &f) return *this;
                
                _imp = f._imp;

                return *this;
            }

            file_type &operator=(file_type &&f)
            {
                if(this == &f) return *this;

                _imp = std::move(f._imp);
                return *this;
            }
                

            //================factory methods==================================
            /*! 
            \brief open file

            Static method opening an existing file.
            \throws nxfile_error in case of errors
            \param n name of the file
            \param ro open read only if true
            \return an instance of NXFile
            */
            static file_type open_file(const string &n,bool ro=true)
            {
                try
                {
                    return file_type(imp_type::open_file(n,ro));
                }
                catch(...)
                {
                    throw nxfile_error(EXCEPTION_RECORD,"Error opening file!");
                }

            }

            //-----------------------------------------------------------------
            /*! 
            \brief create file
            
            Static method to create a file. 
            \throws nxfile_error in case of errors
            \param n name of the file to create
            \param ow overwrite existing file if true
            \param ssize split size (not implemented yet)
            \return instance of NXFile
            */
            static file_type
            create_file(const string &n,bool ow=false, ssize_t ssize = 0)
            {
                file_type file;

                try
                {
                    file = file_type(imp_type::create_file(n,ow,ssize));
                }
                catch(...)
                {
                    throw nxfile_error(EXCEPTION_RECORD,"Error creating file!");
                }

                auto root_group = file.root();
                
                //set file specific attributes
                root_group.template
                    attr<string>("NX_class",true).write(string("NXroot"));
                root_group.template 
                    attr<string>("file_time",true).write(nxdate_time::get_date_time_str());
                root_group.template 
                    attr<string>("file_update_time",true).write(nxdate_time::get_date_time_str());
                root_group.template attr<string>("file_name",true).write(n);

                //this should be taken from a configuration
                root_group.template
                    attr<string>("NeXus_version",true).write(string("4.3.0"));

                //flush the files content
                file.flush();

                return file;
            }


            //-----------------------------------------------------------------
            //! flush the file
            void flush() const{ _imp.flush(); }
            
            //-----------------------------------------------------------------
            //! check read only
            bool is_readonly() const { return _imp.is_readonly(); }


            //-----------------------------------------------------------------
            //! close the file
            virtual void close()
            {
                if((this->is_valid())&&(!this->is_readonly()))
                {
                    auto r = root();
                    r.template attr<string>("file_update_time",true)
                        .write(nxdate_time::get_date_time_str());
                    r.close();
                }
                
                _imp.close();
                //nxobject<Imp>::close();
            }

            //-----------------------------------------------------------------
            /*!
            \brief get number of open groups
            \return number ofopen groups
            */
            size_t open_groups() const { return this->imp().open_groups(); }

            //------------------------------------------------------------------
            /*!
            \brief get number of open fields
            \return number of open fields
            */
            size_t open_fields() const { return this->imp().open_fields(); }

            //------------------------------------------------------------------
            /*!
            \brief get root group

            Return the root group of the file.
            \return root group of the file
            */
            typename nxobject_trait<IMPID>::group_type
            root() const
            {
                typedef typename nximp_map<IMPID>::group_imp group_imp_type;
                typedef typename nxobject_trait<IMPID>::group_type group_type;

                return group_type(group_imp_type(_imp.open("/")));
            }

            //----------------------------------------------------------------
            bool is_valid() const noexcept
            {
                return _imp.is_valid(); 
            }

            //----------------------------------------------------------------
            string path() const { return _imp.path(); }

            //----------------------------------------------------------------
            string base() const { return _imp.base(); }

            //---------------------------------------------------------------
            string name() const { return _imp.name(); }

    };


//end of namespace
}
}
}
