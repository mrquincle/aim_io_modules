/**
 * @file CSCreateSensorModuleAuth.cpp
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

#include <CSCreateSensorModuleAuth.h>

#include <csconnect/CSConnectFactory.h>
#include <csconnect/CSConnect.h>

#include <string>
#include <iostream>

using namespace rur;
using namespace cs;
using namespace std;

/**
 * The Tick() routine is overloaded.
 */
void CSCreateSensorModuleAuth::Tick() {
	CSConnectFactory* fac = CSConnectFactory::Instance(CURL_CONNECTOR);
	CSConnect *c = fac->GetNewConnector();
	c->Init();
	CSLogin * id = new CSLogin();
	id->value.push_back(oauth_token);
	id->value.push_back(oauth_secret);

	string name = "Dummyiest dummy";
	string display_name = name;
	string device_type = "int";
	string data_type = "int";
	int sensor_id = 29722;
	c->AddSensor(*id, name, display_name, device_type, data_type, sensor_id);
	cout << "Sensor created with id " << sensor_id << endl;
	delete id;
}


