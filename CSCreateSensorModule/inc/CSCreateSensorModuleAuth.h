/**
 * @file CSCreateSensorModuleAuth.h
 * @brief 
 *
 * This file is created at Almende B.V. It is open-source software and part of the Common 
 * Hybrid Agent Platform (CHAP). A toolbox with a lot of open-source tools, ranging from 
 * thread pools and TCP/IP components to control architectures and learning algorithms. 
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless,
 * we personally strongly object against this software being used by the military, in the
 * bio-industry, for animal experimentation, or anything that violates the Universal
 * Declaration of Human Rights.
 *
 * Copyright © 2010 Anne van Rossum <anne@almende.com>
 *
 * @author  Anne C. van Rossum
 * @date    Feb 12, 2012
 * @project Replicator FP7
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#ifndef CSCreateSensorModuleAuth_H_
#define CSCreateSensorModuleAuth_H_

#include <CSCreateSensorModule.h>
#include <string>

namespace rur {

class CSCreateSensorModuleAuth: public CSCreateSensorModule {
public:
	void Tick();
//protected:
	//! Mode/step
	std::string oauth_step;

	//! Token
	std::string oauth_token;
	//! Verifier
	std::string oauth_verifier;
	//! Secret
	std::string oauth_secret;
};

}


#endif /* CSCreateSensorModuleAuth_H_ */
