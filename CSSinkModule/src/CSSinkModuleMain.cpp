/**
 * @file CSSinkModuleMain.cpp
 * @brief ...
 *
 * This file is created at Almende B.V. It is open-Sink software and part of the Common
 * Hybrid Agent Platform (CHAP). A toolbox with a lot of open-Sink tools, ranging from
 * thread pools and TCP/IP components to control architectures and learning algorithms. 
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-Sink license. Nevertheless,
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
#include <CSSinkModule.h>

#include <stdlib.h>
#include <iostream>

using namespace rur;
using namespace std;

/**
 * Every module is a separate binary and hence has its own main method.
 */
int main(int argc, char *argv[])  {
	CSSinkModule *m = new CSSinkModule();

	if (argc < 7) {
		std::cout << "Arguments: [module id, token, secret, sensor id, sample freq, start time]" << endl;
		return EXIT_FAILURE;
	}

	Param * param = m->GetParam();

	// the module id is to be able to run different CSSinkModules for different users
	param->module_id = argv[1];

	// the oauth is to identify to users
	param->oauth_token = argv[2];
	param->oauth_secret = argv[3];

	// the sensor that we want to put our data into
	param->sensor_id = atoi(argv[4]);

	// expect sample frequency in seconds
	param->sample_freq = atoi(argv[5]);
	if (param->sample_freq == 0) param->sample_freq = 1;

	// starting time, we can rerun the past using this parameter
	param->start_time = atoi(argv[6]);

	m->Init(param->module_id);

	do {
		m->Tick();
		//sleep(param->sample_freq);

	} while (true); // (!m->Finished());

	delete m;

	return EXIT_SUCCESS;
}
