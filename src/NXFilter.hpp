/*
 * Declaration of the basic NXFilter template
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
 * Declaration of the NXFilter template
 *
 * Created on: Aug 8, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXFILTER_HPP_
#define NXFILTER_HPP_

#include <pni/utils/Types.hpp>

#include "NXObject.hpp"

using namespace pni::utils;

namespace pni{
    namespace nx{

        //! \ingroup util_classes
        //! \brief Filter object
        template<typename Imp> class NXFilter{
            private:
                Imp _imp; //!< filter implementation object
            protected:

                //! get non-const ref

                //! This returns a non constant refernce to the implementation.
                //! This is necessary for derived classes that want to 
                //! export some functionality of the implementation object
                //! to derived clases.
                //! This makes perfectly sense since the class hierachrchy 
                //! is not directly for encapsulation but only for avoiding 
                //! writing work.
                Imp &imp(){
                    return _imp;
                }
            public:
                //================constructors  and destructor==================
                //! default constructor
                explicit NXFilter():_imp()
                {
                }

                //--------------------------------------------------------------
                //! copy constructor
                NXFilter(const NXFilter<Imp> &f):_imp(f._imp)
                {
                }
                
                //--------------------------------------------------------------
                //! conversion copy constructor
                template<typename FImp>
                    NXFilter(const NXFilter<FImp> &f):_imp(f.imp())
                {
                }

                //--------------------------------------------------------------
                //! copy implementation constructor 
                NXFilter(const Imp &i):_imp(i)
                {
                }


                //--------------------------------------------------------------
                //! copy conversion implementation constructor
                template<typename FImp>
                    NXFilter(const FImp &i):_imp(i.imp())
                {
                }

                //--------------------------------------------------------------
                //! move constructor
                NXFilter(NXFilter<Imp> &&f):_imp(std::move(f._imp))
                {
                }
                
                //--------------------------------------------------------------
                //! move constructor from implementation
                NXFilter(Imp &&i):_imp(std::move(i))
                {
                }

                //--------------------------------------------------------------
                //! destructor
                virtual ~NXFilter()
                {
                }

                //================assignment operators==========================
                //! copy assignment operator
                NXFilter<Imp> &operator=(const NXFilter<Imp> &f)
                {
                    if(this != &f) _imp = f._imp;
                    return *this;
                }

                //--------------------------------------------------------------
                //! move assignment operator
                NXFilter<Imp> &operator=(NXFilter<Imp> &&f)
                {
                    if(this != &f) _imp = std::move(f._imp);
                    return *this;
                }


                //! return const ref to implementation

                //! This method returns a const reference to the implementation 
                //! of the filter object. 
                //! \return const ref. to implementation
                const Imp imp() const
                {
                    return _imp;
                }

        };

    //end of namespace
    }
}


#endif /* NXFILTER_HPP_ */
