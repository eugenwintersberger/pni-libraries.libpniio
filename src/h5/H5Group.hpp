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

#include "NamedObject.hpp"

namespace pni{
    namespace nx{
        namespace h5{
            
            class H5Group:public H5NamedObject{
                public:
                    //==========constructors and destructors===================
                    H5Group();
                    H5Group(const H5NamedObject &o);
                    H5Group(H5NamedObject &&o);
                    H5Group(const String &name,const H5Group &p);
                    virtual ~H5Group();

                    //===========assignment operators==========================
                    H5Group &operator=(const H5Group &o);
                    H5Group &operator=(H5Group &&o);

                    //=============creating objects============================
                    H5Dataset create_dataset(const String &n,const TypeId &tid,
                            const Shape &s,const Shape &ChunkShape=Shape(0));
                    H5Dataset create_dataset(const String &n,const H5Datatype &tid,
                            const H5Dataspace &s,
                            const Shape &ChunkShape = Shape(0));
                    
                    //=============methods to open objects=====================
                    H5Object open(const String &n);
                    H5Object operator[](const String &n);

                    //==============misc methods===============================
                    void remove(const String &n);
                   
                    
            };
        
        //end of namespace
        }
    }
}



#endif
