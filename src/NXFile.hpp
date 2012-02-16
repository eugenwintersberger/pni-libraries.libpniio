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


#include <pni/utils/Types.hpp>


#ifndef NXFILE_HPP_
#define NXFILE_HPP_

#include "NXObject.hpp"
#include "NXGroup.hpp"
#include "NXDateTime.hpp"

using namespace pni::utils;

namespace pni{
    namespace nx{

        //! \ingroup nexus_lowlevel
        //! \brief File object

        //! NXFile represents a file for reading and writing data too. It is
        //! the basic data holding entity. You can use NXField to read from or write
        //! data to a file.
        template<typename Imp> class NXFile:public NXGroup<Imp> {
            private:
                // a file object can neither be copied
                NXFile(const NXFile &o);
                // nor can it be assigned
                NXFile &operator=(const NXFile &);
                

            public:
                typedef std::shared_ptr<NXFile > sptr; //! shared pointer to a file object
                //============constructors and destructor=======================
                //! default constructor
                explicit NXFile():NXGroup<Imp>()
                {
                }

                explicit NXFile(Imp &&imp):NXGroup<Imp>(std::move(imp)){
                    
                }

                NXFile(NXFile<Imp> &&f):NXGroup<Imp>(std::move(f))
                {
                }



                //--------------------------------------------------------------
                //! destructor
                ~NXFile(){
                    if(this->is_valid())
                    {
                        try{
                            this->template attr<String>("file_update_time").write(NXDateTime::getDateTimeStr());
                        }catch(...){
                            //do nothing if write fails - most probably 
                            //the file is in read only mode
                        }
                    }
                }

                //====================assignment operators======================
                NXFile<Imp> &operator=(NXFile<Imp> &&o){
                    if(this == &o) return *this;
                    NXGroup<Imp>::operator=(std::move(o));
                    return *this;
                }

                //=============factory methods==================================
                static NXFile<Imp> open_file(const String &n,bool ro=true){
                    EXCEPTION_SETUP("static NXFile<Imp> "
                            "open_file(const String &n,bool ro=true)");

                    NXFile<Imp> file;

                    try{
                        file = NXFile<Imp>(Imp::open_file(n,ro));
                    }catch(...){
                        EXCEPTION_INIT(NXFileError,"Error opening file!");
                        EXCEPTION_THROW();
                    }


                    return file;
                }

                //--------------------------------------------------------------
                static NXFile<Imp> create_file(const String &n,bool ow=false,
                        ssize_t ssize = 0)
                {
                    EXCEPTION_SETUP("static NXFile<Imp> create_file("
                            "const String &n,bool ow=false, ssize_t ssize = 0)");

                    NXFile<Imp> file;

                    try{
                        file = NXFile<Imp>(Imp::create_file(n,ow,ssize));
                    }catch(...){
                        EXCEPTION_INIT(NXFileError,"Error creating file!");
                        EXCEPTION_THROW();
                    }
                    
                    //set file specific attributes
                    file.template
                        attr<String>("NX_class").write(String("NXroot"));
                    file.template 
                        attr<String>("file_time").write(NXDateTime::getDateTimeStr());
                    file.template 
                        attr<String>("file_update_time").write(NXDateTime::getDateTimeStr());
                    file.template attr<String>("file_name").write(n);

                    //this should be taken from a configuration
                    file.template
                        attr<String>("NeXus_version").write(String("4.3.0"));

                    //flush the files content
                    file.flush();

                    return file;
                }

                //============methods for setting up the file object============


                //--------------------------------------------------------------
                //! flush the file
                void flush() const{
                    this->imp().flush();
                }

                virtual void close(){
                    try{
                        this->template attr<String>("file_update_time").write(NXDateTime::getDateTimeStr());
                    }catch(...){
                        //do nothing if write fails - most probably 
                        //the file is in read only mode
                    }

                    NXObject<Imp>::close();
                }





};


    //end of namespace
    }
}

#endif /* NXFILE_HPP_ */
