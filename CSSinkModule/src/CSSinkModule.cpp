/**
 * @file CSSinkModule.cpp
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
 * Copyright © 2012 Anne van Rossum <anne@almende.com>
 *
 * @author  ...
 * @date    ...
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#include <csconnect/CSConnectFactory.h>
#include <csconnect/CSConnect.h>

#include <CSSinkModule.h>

//#include <json_spirit_reader.h>

#include <iostream>

using namespace rur;
using namespace cs;
using namespace std;

/*
 * initialize a counter
 */
int counter = 0;

void CSSinkModule::Tick() {
	CSConnectFactory* fac = CSConnectFactory::Instance(CURL_CONNECTOR);
	CSConnect *c = fac->GetNewConnector();
	c->Init();
	CSLogin * id = new CSLogin();
	id->value.push_back(cliParam->oauth_token);
	id->value.push_back(cliParam->oauth_secret);

	int d = 0;
	d = *readDataIn();

	CSData data;
	CSDataField * sdf = new CSDataField();
	sdf->label = "value";
	stringstream msg; msg.clear(); msg.str("");
	msg << d;
	sdf->value = msg.str();
	data.fields.push_back(sdf);

	cout << "Data fields: " << data.fields.size() << endl;
	//c->AddData(*id, cliParam->sensor_id, data);
	c->AddData(*id, cliParam->sensor_id, data, cliParam->start_time+counter*cliParam->sample_freq);

	for (int i = 0; i < data.fields.size(); ++i) {
		sdf = data.fields.back();
		delete sdf;
		data.fields.pop_back();
	}
	
	counter++;

	delete id;

}
