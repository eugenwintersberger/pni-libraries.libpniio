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
 * Definition of the NXConfiguration class.
 *
 * Created on: Apr 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXCONFIGURATION_HPP__
#define __NXCONFIGURATION_HPP__

#include<vector>
#include<map>
#include<pni/utils/Types.hpp>

using namespace pni::utils;

namespace pni{
    namespace nx{

        class NXConfiguration{
            private:
                String __config_dir_root; //!< root directory of the library
                                          //!< configuration
                String __global_nxdl_dir; //!< global NXDL 
                std::vector<String> __base_classes;
                std::vector<String> __
                std::vector<String> __app_classes;
            public:
                NXConfiguration();
                ~NXConfiguration();

                String global_config_dir() const;
                String global_nxdl_dir() const;

                const std::vector<String> &base_classes() const;
                cosnt std::vector<String> &app_classes() const;





        };

    //end of namespace
    }
}


#endif
