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
 * Implementation of an HDF5 Path object
 *
 * Created on: Feb 15, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5Path.hpp"

namespace pni{
    namespace nx{
        namespace h5{
            //================implementation of private methods=================
            void H5Path::__fill_path(const String &p)
            {
                String::const_iterator iter;
                String name = "";
                String ps = p;

                //check if the string contains / charachter
                if(p.find('/') == String::npos){
                    //in this case we have only a single element in the path
                    _path.push_back(p);
                    return;
                }

                //if the first charachter is not a / we have to add one
                if(p[0] != '/') ps = "/"+p;

                for(auto iter = ps.begin(); iter != ps.end(); iter++)
                {
                    if(*iter == '/'){
                        if(!name.empty()) _path.push_back(name);

                        name.clear();
                    }else{
                        name += *iter;
                    }
                }
                if(!name.empty()) _path.push_back(name);
            }

            //------------------------------------------------------------------
            //implementation of the default constructor
            H5Path::H5Path():_path(){} 

            //------------------------------------------------------------------
            //implementation of the copy constructor
            H5Path::H5Path(const H5Path &p):_path(p._path){}

            //------------------------------------------------------------------
            //implementation of the move constructor
            H5Path::H5Path(H5Path &&p):_path(std::move(p._path)){}

            //------------------------------------------------------------------
            //implementation of the string constructor
            H5Path::H5Path(const String &p):_path(0)
            {
                _path.clear();
                __fill_path(p);
            }

            //------------------------------------------------------------------
            //implementation of the destructor
            H5Path::~H5Path()
            {
                _path.clear();
            }


            //=============assignment operators=================================
            //implementation of copy assignment
            H5Path &H5Path::operator=(const H5Path &p)
            {
                if(this != &p)  _path = p._path; 
                return *this;
            }

            //------------------------------------------------------------------
            //implementation of move assignment
            H5Path &H5Path::operator=(H5Path &&p)
            {
                if(this != &p) _path = std::move(p._path);

                return *this;
            }

            //------------------------------------------------------------------
            //implementation of string conversion assignment
            H5Path &H5Path::operator=(const String &s)
            {
                _path.clear();
                __fill_path(s);
                return *this; 
            }


            //====================iterator methods==============================
            H5Path::const_iterator H5Path::begin() const
            {
                return _path.begin();
            }

            H5Path::iterator H5Path::begin()
            {
                return _path.begin();
            }

            H5Path::const_iterator H5Path::end() const
            {
                return _path.end();
            }

            H5Path::iterator H5Path::end()
            {
                return _path.end();
            }

            //=================inquery methods==================================
            size_t H5Path::size() const
            {
                return _path.size();
            }

            String H5Path::operator[](size_t i) const
            {
                return _path.at(i);
            }


            //===================output operator================================
            std::ostream &operator<<(std::ostream &o,const H5Path &p)
            {
#ifdef NOFOREACH
                for(auto iter = p.begin(); iter != p.end();iter++){
                    const String &name = *iter;
#else
                for(const String &name: p){
#endif
                    o<<name<<std::endl;
                }

                return o;
            }

            //=====================comparison operators=========================
            bool operator==(const H5Path &p1,const H5Path &p2)
            {
                if(p1.size() != p2.size()) return false;

                for(size_t i=0;i<p1.size();i++){
                    if(p1[i] != p2[i]) return false;
                }
                return true; 
            }

            bool operator!=(const H5Path &p1,const H5Path &p2)
            {
                if(p1 == p2) return false;
                return true;
            }


        }
    }
}
