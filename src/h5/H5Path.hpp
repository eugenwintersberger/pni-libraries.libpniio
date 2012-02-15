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
 * Definition of an HDF5 Path object
 *
 * Created on: Feb 15, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5PATH_HPP__
#define __H5PATH_HPP__

#include <string>
#include <vector>
#include <iostream>

#include <pni/utils/Types.hpp>

using namespace pni::utils;

namespace pni{
    namespace nx{
        namespace h5{
            
            class H5Path{
                private:
                    std::vector<String> _path;

                    void __fill_path(const String &n);
                public:
                    //================tpedefs==================================
                    typedef std::vector<String>::iterator iterator;
                    typedef std::vector<String>::const_iterator const_iterator;
                    //===========constructors and destructor===================
                    //! default constructor
                    explicit H5Path();
                    //! copy constructor
                    H5Path(const H5Path &p);
                    //! move constructor
                    H5Path(H5Path &&p);
                    //! copy string constructor
                    H5Path(const String &s);

                    //! destructor
                    ~H5Path();

                    //==============assignment operators=======================
                    //! copy assignment
                    H5Path &operator=(const H5Path &p);

                    //! move assignment
                    H5Path &operator=(H5Path &&p);

                    //! copy conversion assignment
                    H5Path &operator=(const String &s);

                    //===============iterators methods=========================
                    //! const first element

                    //! Returns a constant iterator on  the first element in the 
                    //! path.
                    //! \return constant iterator
                    const_iterator begin() const;

                    //! first element

                    //! Returns an iterator on the first element in the path.
                    //! \return iterator
                    iterator begin();

                    //! const last element

                    //! Returns a constant iterator on the last element in the 
                    //! path.
                    //! \return constant iterator
                    const_iterator end() const;
                    
                    //! last element

                    //! Returns an interator on the last element in the path.
                    //! \return iterator
                    iterator end();

                    //================inquery methods==========================
                    //! number of elements

                    //! Returns the number of elements in the path.
                    //! \return number of elements
                    size_t size() const;

                    //=================element access methods===================
                    String operator[](size_t i) const;
                    

            };

            std::ostream &operator<<(std::ostream &os,const H5Path &p);
            bool operator==(const H5Path &p1,const H5Path &p2);
            bool operator!=(const H5Path &p1,const H5Path &p2);

        }
    }
}

#endif

