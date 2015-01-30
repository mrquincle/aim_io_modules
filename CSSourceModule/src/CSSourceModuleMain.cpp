/**
 * @file CSSourceModuleMain.cpp
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
#include <CSSourceModule.h>

#include <stdlib.h>
#include <iostream>

using namespace rur;
using namespace std;

/**
 * Every module is a separate binary and hence has its own main method.
 */
int main(int argc, char *argv[])  {
	CSSourceModule *m = new CSSourceModule();

	Param * param = m->GetParam();
	// can we define a function in idl file's struct Param and return the length of Param?? Then, we can forget the hard number 8:)

	if (argc < 8) {
		free(param);
		free(m);
		std::cout << "Please use Arguments: [module_id, token, secret, sensor_id, sample_freq, start_time(UnixTimeStamp), sensor_name]" << endl;
		return EXIT_FAILURE;
	}



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
	// sensor name
	param->sensor_name = argv[7];

	m->Init(param->module_id);

	std::cout << "Will get last data until the supplied UnixTimeStamp from sensor " << param->sensor_name << "" << std::endl;

	do {
		m->Tick();
		//sleep(param->sample_freq);

	} while (true); // (!m->Finished());

	delete m;

	return EXIT_SUCCESS;
}
