/*
 * Declaration of the NXFile template
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
 * Declaration of the NXFile template
 *
 * Created on: Jun 30, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>
#include <pni/core/service.hpp>

#include "nxobject.hpp"
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
    template<typename Imp> class nxfile:public nxgroup<Imp> 
    {
        public:
            //! shared pointer type for a file object
            typedef std::shared_ptr<nxfile > shared_ptr; 
            //===============constructors and destructor========================
            //! default constructor
            explicit nxfile():nxgroup<Imp>() { }

            //-----------------------------------------------------------------
            //! copy constrcutor
            nxfile(const nxfile<Imp> &file):nxgroup<Imp>(file) { }

            //-----------------------------------------------------------------
            //! implemenetation move constructor
            explicit nxfile(Imp &&imp):nxgroup<Imp>(std::move(imp)){ }

            //-----------------------------------------------------------------
            //! move constructor
            nxfile(nxfile<Imp> &&f):nxgroup<Imp>(std::move(f)) { }

            //-----------------------------------------------------------------
            //! destructor
            ~nxfile()
            {
                if((this->is_valid())&&(!this->is_readonly()))
                {
                    this->template attr<string>("file_update_time",true)
                        .write(nxdate_time::get_date_time_str());
                }
            }

            //====================assignment operators=========================
            //! move assignment operator
            nxfile<Imp> &operator=(nxfile<Imp> &&o)
            {
                if(this == &o) return *this;
                nxgroup<Imp>::operator=(std::move(o));
                return *this;
            }

            //-----------------------------------------------------------------
            //! copy assignment operator
            nxfile<Imp> &operator=(const nxfile<Imp> &o)
            {
                if(this != &o) nxgroup<Imp>::operator=(o);
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
            static nxfile<Imp> open_file(const string &n,bool ro=true)
            {
                nxfile<Imp> file;

                try
                {
                    file = nxfile<Imp>(Imp::open_file(n,ro));
                }
                catch(...)
                {
                    throw nxfile_error(EXCEPTION_RECORD,"Error opening file!");
                }


                return file;
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
            static nxfile<Imp> 
                create_file(const string &n,bool ow=false, ssize_t ssize = 0)
            {
                nxfile<Imp> file;

                try
                {
                    file = nxfile<Imp>(Imp::create_file(n,ow,ssize));
                }
                catch(...)
                {
                    throw nxfile_error(EXCEPTION_RECORD,"Error creating file!");
                }
                
                //set file specific attributes
                file.template
                    attr<string>("NX_class").write(string("NXroot"));
                file.template 
                    attr<string>("file_time").write(nxdate_time::get_date_time_str());
                file.template 
                    attr<string>("file_update_time").write(nxdate_time::get_date_time_str());
                file.template attr<string>("file_name").write(n);

                //this should be taken from a configuration
                file.template
                    attr<string>("NeXus_version").write(string("4.3.0"));

                //flush the files content
                file.flush();

                return file;
            }


            //-----------------------------------------------------------------
            //! flush the file
            void flush() const{ this->imp().flush(); }
            
            //-----------------------------------------------------------------
            //! check read only
            bool is_readonly() const { return this->imp().is_readonly(); }


            //-----------------------------------------------------------------
            //! close the file
            virtual void close()
            {
                if((this->is_valid())&&(!this->is_readonly()))
                {
                    this->template attr<string>("file_update_time",true)
                        .write(nxdate_time::get_date_time_str());
                }
                
                this->imp().close();
                nxobject<Imp>::close();
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
            typename nxobject_traits<nximp_code_map<nxfile<Imp>>::icode>::group_type
            root_group() const
            {
                typedef nximp_code_map<nxfile<Imp>> imp_code_map;
                typedef typename nxobject_traits<imp_code_map::icode>::group_type group_type;

                return group_type(this->open("/"));
            }


    };


//end of namespace
}
}
}
