/*
 * NXConfig.hpp
 *
 *  Created on: Sep 29, 2011
 *      Author: eugen
 */

#ifndef NXCONFIG_HPP_
#define NXCONFIG_HPP_

namespace pni {
namespace nx {

#define SYSTEM_CONFIG_PATH "/etc/pninx"
#define USER_CONFIG_PATH ".pninx"

//basic configuration class - should be implemented as singleton and
//will be instantiated during library initialization.
class NXConfig {
public:
	NXConfig();
	virtual ~NXConfig();
};

} /* namespace nx */
} /* namespace pni */
#endif /* NXCONFIG_HPP_ */
