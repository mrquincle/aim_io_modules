/**
 * @file CSLoginModuleMain.cpp
 * @brief ...
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
 * Copyright © 2011 Anne van Rossum <anne@almende.com>
 *
 * @author  ...
 * @date    ...
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */
#include <CSLoginModuleAuth.h>

#include <stdlib.h>
#include <iostream>

using namespace rur;
using namespace std;

/**
 * Every module is a separate binary and hence has its own main method.
 */
int main(int argc, char *argv[])  {
	CSLoginModuleAuth *m = new CSLoginModuleAuth();

	if (argc < 2) {
		std::cerr << "Error: Use a login step as argument for this instance" << endl;
		return EXIT_FAILURE;
	}

	//! Set class variables to oauth data
	m->oauth_step = argv[1];

	if (m->oauth_step != "oauth0") {
		if (argc < 5) {
			std::cerr << "Error: Use token, secret, and identifier as argument for this instance (# args = " << argc << ")" << endl;
			return EXIT_FAILURE;
		}
		m->oauth_token = argv[2];
		m->oauth_secret = argv[3];
		m->oauth_verifier = argv[4];
	}

	// identifier same as token here...
	std::string identifier = argv[2];
	m->Init(identifier);


//	do {
		m->Tick();
//	} while (true); // (!m->Finished());

	delete m;

	return EXIT_SUCCESS;
}
