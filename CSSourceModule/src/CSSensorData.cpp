/*
 * CSSensorData.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: scott
 */

#include <iostream>
#include <json_spirit_reader.h>

#include "CSSensorData.h"

using namespace rur;
using namespace std;

/*
 * structure the retrieved sensor data
 */
CSSensorData::CSSensorData(std::string json) {
	cout << "Parse json string: " << json << endl;
	//A json value holds JSON array, JSON object, string, integer, double, bool or null
	json_spirit::Value value;
	if (!read(json, value)) {
		valid = false;
		return;
	}
	// an json_spirit Object is, by default, a vector of JSON Pairs
	json_spirit::Object dataobj = value.get_obj();
	const json_spirit::Pair& pair = dataobj[0];
	const string& name  = pair.name_;
	//cout << "Name: (I guess it is data!!) "<<name << endl;
	// value 2 is also a json value
	const json_spirit::Value&  value2 = pair.value_;
	// arr is a JSON array
	const json_spirit::Array& arr = value2.get_array();
	// obj is a JSON object
	json_spirit::Object obj = arr[0].get_obj();

	for( json_spirit::Object::size_type i = 0; i != obj.size(); ++i ) {
		const json_spirit::Pair& pair = obj[i];
		const string& name  = pair.name_;
		const json_spirit::Value&  value = pair.value_;

		if (name == "id") {
			istringstream buffer(value.get_str());
			buffer >> id;
		} else if (name == "sensor_id") {
			istringstream buffer(value.get_str());
			buffer >> sensor_id;
		} else if (name == "value") {
			cout << value.type() << endl;
			this->value = value;
		} else if (name == "date") {
			istringstream buffer(value.get_str());
			buffer >> date;
		} else if (name == "week") {
			istringstream buffer(value.get_str());
			buffer >> week;
		} else if (name == "month") {
//			cout << "json_spirit::Value: " << value.type() << endl;
			istringstream buffer(value.get_str());
			buffer >> month;
		} else if (name == "year") {
			istringstream buffer(value.get_str());
			buffer >> year;
		}
	}
	valid = true;
}

