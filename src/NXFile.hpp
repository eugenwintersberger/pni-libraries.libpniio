/*
 * Declaration of the NXFile template
 *
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
 * Declaration of the NXFile template
 *
 * Created on: Jun 30, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/utils/Types.hpp>
#include <pni/utils/service.hpp>

#include "NXObject.hpp"
#include "NXGroup.hpp"
#include "NXDateTime.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

    /*! 
    \ingroup nexus_lowlevel
    \brief File object

    NXFile represents a file for reading and writing data too. It is the basic
    data holding entity. You can use NXField to read from or write data to a
    file.
    */
    template<typename Imp> class NXFile:public NXGroup<Imp> 
    {
        public:
            //! shared pointer type for a file object
            typedef std::shared_ptr<NXFile > shared_ptr; 
            //===============constructors and destructor========================
            //! default constructor
            explicit NXFile():NXGroup<Imp>() { }

            //-----------------------------------------------------------------
            //! copy constrcutor
            NXFile(const NXFile<Imp> &file):NXGroup<Imp>(file) { }

            //-----------------------------------------------------------------
            //! implemenetation move constructor
            explicit NXFile(Imp &&imp):NXGroup<Imp>(std::move(imp)){ }

            //-----------------------------------------------------------------
            //! move constructor
            NXFile(NXFile<Imp> &&f):NXGroup<Imp>(std::move(f)) { }

            //-----------------------------------------------------------------
            //! destructor
            ~NXFile()
            {
                if((this->is_valid())&&(!this->is_readonly()))
                {
                    this->template attr<String>("file_update_time",true)
                        .write(NXDateTime::get_date_time_str());
                }
            }

            //====================assignment operators=========================
            //! move assignment operator
            NXFile<Imp> &operator=(NXFile<Imp> &&o)
            {
                if(this == &o) return *this;
                NXGroup<Imp>::operator=(std::move(o));
                return *this;
            }

            //-----------------------------------------------------------------
            //! copy assignment operator
            NXFile<Imp> &operator=(const NXFile<Imp> &o)
            {
                if(this != &o) NXGroup<Imp>::operator=(o);
                return *this;
            }

            //================factory methods==================================
            /*! 
            \brief open file

            Static method opening an existing file.
            \throws NXFileError in case of errors
            \param n name of the file
            \param ro open read only if true
            \return an instance of NXFile
            */
            static NXFile<Imp> open_file(const String &n,bool ro=true)
            {
                NXFile<Imp> file;

                try
                {
                    file = NXFile<Imp>(Imp::open_file(n,ro));
                }
                catch(...)
                {
                    throw NXFileError(EXCEPTION_RECORD,"Error opening file!");
                }


                return file;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief create file
            
            Static method to create a file. 
            \throws NXFileError in case of errors
            \param n name of the file to create
            \param ow overwrite existing file if true
            \param ssize split size (not implemented yet)
            \return instance of NXFile
            */
            static NXFile<Imp> 
                create_file(const String &n,bool ow=false, ssize_t ssize = 0)
            {
                NXFile<Imp> file;

                try
                {
                    file = NXFile<Imp>(Imp::create_file(n,ow,ssize));
                }
                catch(...)
                {
                    throw NXFileError(EXCEPTION_RECORD,"Error creating file!");
                }
                
                //set file specific attributes
                file.template
                    attr<String>("NX_class").write(String("NXroot"));
                file.template 
                    attr<String>("file_time").write(NXDateTime::get_date_time_str());
                file.template 
                    attr<String>("file_update_time").write(NXDateTime::get_date_time_str());
                file.template attr<String>("file_name").write(n);

                //this should be taken from a configuration
                file.template
                    attr<String>("NeXus_version").write(String("4.3.0"));

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
                    this->template attr<String>("file_update_time",true)
                        .write(NXDateTime::get_date_time_str());
                }
                
                this->imp().close();
                NXObject<Imp>::close();
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
    };


//end of namespace
}
}
