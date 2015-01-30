/**
 * @file CSSourceModule.cpp
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
 * Copyright © 2012 Anne van Rossum <anne@almende.com>
 *
 * @author  ...
 * @date    ...
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#include <csconnect/CSConnectFactory.h>
#include <csconnect/CSConnect.h>

#include <CSSourceModule.h>
#include <CSSensorData.h>
#include <CSFilter.h>

#include <iostream>

using namespace rur;
using namespace cs;
using namespace std;

//using namespace json_spirit;

//	HTTP-reply: {"data":[{"id":"246507068","sensor_id":"270","value":"42.54","date":"1329417065.647","week":"7","month":"2","year":"2012"}]}
//CSSensorData<float> & CSSourceModuleAuth::Parse(string json) {
//	}

/*
 * initialize a counter
 */
int counter = 0;


void CSSourceModule::Tick() {
	CSConnectFactory* fac = CSConnectFactory::Instance(CURL_CONNECTOR);
	CSConnect *c = fac->GetNewConnector();
	c->Init();
	CSLogin * id = new CSLogin();
	id->value.push_back(cliParam->oauth_token);
	id->value.push_back(cliParam->oauth_secret);

	//string json = c->GetData(*id, cliParam->sensor_id);
	string json = c->GetData(*id, cliParam->sensor_id,cliParam->start_time+counter*cliParam->sample_freq);

	//cout << "date:" <<cliParam->start_time+counter*cliParam->sample_freq <<endl;
	if (json.empty()) {
		cerr << "Data not obtained!" << endl;
		return;
	}

	// parse json result, data type should be "int"
	CSSensorData * data = new CSSensorData(json);
	data->sensor_name = cliParam->sensor_name;
	cout << "Sensor Name: "<< data->sensor_name<<endl;

	// should actually have been a float...
	if (!data->valid) {
		cerr << "Parsing error!" << endl;
		return;
	}

	/*
	* a test of CSSensor data format, normally, commented out.
	*/
	//string test = data->value.get_str();
	//cout << "I guess it is {???"<<test[0] << endl;

	/*
	 * Apply CSFilter to CSSensor data
	 */

	CSFilter * cs_filter = new CSFilter();
	cs_filter->filterJSON(data);

	free(cs_filter);

	//CSSensorData *filter_data = data;

	//int val;
	long_seq val;
	// data-> value EXAMPLE: {"bearing":-1,"longitude":4.47870534,"provider":"network","latitude":51.90969378,"accuracy":60,"speed":-1,"altitude":-1}
	// cout << "I guess it is: " << data->value.get_str()<<endl;
	// parse data.value json string here
	//cout << "????" << (filter_data->value).type()<<endl;

	cout<<"The values are: "<<endl;
	for (int i=0;i<data->vector_values.size();i++){
		cout<< data->vector_values[i]<<" ";
		val.push_back(data->vector_values[i]);
		//val.push_back((long)vector_values[i]);
	}

//	for (int i = 0; i<val.size();i++){
//		cout<< " val"<<i<<": "<<val[i];
//	}
	cout<<endl;

	/*
	istringstream buffer(data->value.get_str());
	buffer >> val;
	cout << "float: " << val << endl;
	*/

	//int r = (int)val * 100; // we just communicate the float as int*100
	writeResult(val);

	counter ++;

	delete data;
}
