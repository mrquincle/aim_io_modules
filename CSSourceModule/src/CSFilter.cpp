/*
 * CSFilter.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: scott
 */
#include <CSFilter.h>
#include <CSSensorData.h>

#include <json_spirit_reader.h>
//#include <json_spirit_value.h>
#include <iostream>

#include <CSSensorDataType.h>

#include <string>
#include <stdlib.h>

using namespace rur;
using namespace std;

/**
 * Assume we get also a sensor name
 */
CSFilter::CSFilter()
{
	/*
	 * initialize the known sensor types and parameters (a map of key(string), value: json_spirit Values)
	 * enum Value_type{ obj_type, array_type, str_type, bool_type, int_type, real_type, null_type };
	 * should consider writing a configuration (json) file, and read info into the constructor later
	 */

	/*
	 * noise
	 */
	CSSensorDataType *type_noise = new CSSensorDataType();
	type_noise->sensor_name = "noise";
	type_noise->json_flag = false;
	defined_types.add(type_noise);

	/*
	 * Availability
	 */
	CSSensorDataType *type_availability = new CSSensorDataType();
	type_availability->sensor_name = "Availability";
	type_availability->predefined_hashmap["unavailable"] = 0; // 0 means unavailable
	type_availability->predefined_hashmap["available"] = 1; // 1 means available
	type_noise->json_flag = false;
	defined_types.add(type_availability);

	/*
	 * bluetooth scan
	 */
	CSSensorDataType *type_bluetooth_scan = new CSSensorDataType();
	type_bluetooth_scan->sensor_name = "bluetooth_scan";
	type_bluetooth_scan->json_flag = true;
	type_bluetooth_scan->parameters["address"] = json_spirit::Value_type(2);
	type_bluetooth_scan->parameters["rssi"]=json_spirit::Value_type(4);
	defined_types.add(type_bluetooth_scan);

	/*
	 * wifi scan
	 */
	CSSensorDataType *type_wifi = new CSSensorDataType();
	type_wifi->sensor_name = "wifi";
	type_wifi->json_flag = true;
	type_wifi->parameters["frequency"] = json_spirit::Value_type(4);
	type_wifi->parameters["rssi"]=json_spirit::Value_type(4);
	type_wifi->parameters["bssid"]=json_spirit::Value_type(2);
	defined_types.add(type_wifi);

	/*
	 * position
	 */
	CSSensorDataType *type_position = new CSSensorDataType();
	type_position->sensor_name = "position";
	type_position->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_position->parameters["longitude"] = json_spirit::Value_type(5);
	type_position->parameters["latitude"]=json_spirit::Value_type(5);
	defined_types.add(type_position);

	/*
	 * acceleration
	 */
	CSSensorDataType *type_acceleration = new CSSensorDataType();
	type_acceleration->sensor_name = "acceleration";
	type_acceleration->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_acceleration->parameters["x-axis"] = json_spirit::Value_type(5);
	type_acceleration->parameters["y-axis"]=json_spirit::Value_type(5);
	type_acceleration->parameters["z-axis"]=json_spirit::Value_type(5);
	defined_types.add(type_acceleration);

	/*
	 * linear acceleration
	 */
	CSSensorDataType *type_linear_acceleration = new CSSensorDataType();
	type_linear_acceleration->sensor_name = "linear_acceleration";
	type_linear_acceleration->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_linear_acceleration->parameters["x-axis"] = json_spirit::Value_type(5);
	type_linear_acceleration->parameters["y-axis"]=json_spirit::Value_type(5);
	type_linear_acceleration->parameters["z-axis"]=json_spirit::Value_type(5);
	defined_types.add(type_linear_acceleration);

	/*
	 * orientation
	 */
	CSSensorDataType *type_orientation = new CSSensorDataType();
	type_orientation->sensor_name = "orientation";
	type_orientation->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_orientation->parameters["pitch"] = json_spirit::Value_type(5);
	type_orientation->parameters["roll"]=json_spirit::Value_type(5);
	type_orientation->parameters["azimuth"]=json_spirit::Value_type(5);
	defined_types.add(type_orientation);

	/*
	 * battery state
	 */
	CSSensorDataType *type_battery_state = new CSSensorDataType();
	type_battery_state->sensor_name = "battery_state";
	type_battery_state->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_battery_state->parameters["status"] = json_spirit::Value_type(2); // there is only discharging, charging AC, full, charging USB???
	type_battery_state->parameters["level"]=json_spirit::Value_type(2); // a number which we need to transform to integer

	type_battery_state->predefined_hashmap["discharging"] = 0;
	type_battery_state->predefined_hashmap["charging USB"] = 1;
	type_battery_state->predefined_hashmap["charging AC"] = 2;
	type_battery_state->predefined_hashmap["full"] = 3;
	defined_types.add(type_battery_state);

	/*
	 * screen activity
	 */
	CSSensorDataType *type_screen_activity = new CSSensorDataType();
	type_screen_activity->sensor_name = "screen_activity";
	type_screen_activity->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_screen_activity->parameters["screen"] = json_spirit::Value_type(2); // there is only on and off !
	type_screen_activity->predefined_hashmap["off"] = 0;
	type_screen_activity->predefined_hashmap["on"] = 1;
	defined_types.add(type_screen_activity);

	/*
	 * proximity
	 */
	CSSensorDataType *type_proximity = new CSSensorDataType();
	type_proximity->sensor_name = "proximity";
	type_proximity->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_proximity->parameters["distance"] = json_spirit::Value_type(4); // there is only 0 and 1??????
	defined_types.add(type_proximity);

	/*
	 * call state
	 */
	CSSensorDataType *type_call_state = new CSSensorDataType();
	type_call_state->sensor_name = "call_state";
	type_call_state->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_call_state->parameters["state"] = json_spirit::Value_type(2);
	type_call_state->parameters["incomingNumber"] = json_spirit::Value_type(2); // telephone number +31619928120...
	type_call_state->parameters["outgoingNumber"] = json_spirit::Value_type(2); // telephone number +31619928120...
	type_call_state->predefined_hashmap["idle"] = 0;
	type_call_state->predefined_hashmap["calling"] = 1;
	type_call_state->predefined_hashmap["ringing"] = 2;
	type_call_state->predefined_hashmap["dialing"] = 3;
	defined_types.add(type_call_state);

	/*
	 * Reachability
	 */
	CSSensorDataType *type_reachability = new CSSensorDataType();
	type_reachability->sensor_name = "Reachability";
	type_reachability->predefined_hashmap["unreachable"] = 0; // 0 means unreachable
	type_reachability->predefined_hashmap["reachable"] = 1; // 1 means reachable
	type_reachability->json_flag = false;
	defined_types.add(type_reachability);

	/*
	 * network type
	 */
	CSSensorDataType *type_network_type = new CSSensorDataType();
	type_network_type->sensor_name = "network_type";
	type_network_type->json_flag = false;
	type_network_type->predefined_hashmap["none"] = 0; // 0 means none
	type_network_type->predefined_hashmap["mobile"] = 1; // 1 means mobile
	type_network_type->predefined_hashmap["WIFI"] = 2; // 2 means WIFI
	defined_types.add(type_network_type);

	/*
	 * message waiting
	 */
	CSSensorDataType *type_message_waiting = new CSSensorDataType();
	type_message_waiting->sensor_name = "message_waiting";
	type_message_waiting->json_flag = false;
	type_message_waiting->predefined_hashmap["false"] = 0; // 0 means false
	type_message_waiting->predefined_hashmap["true"] = 1; // 1 means true
	defined_types.add(type_message_waiting);

	/*
	 * data connection
	 */
	CSSensorDataType *type_data_connection = new CSSensorDataType();
	type_data_connection->sensor_name = "data_connection";
	type_data_connection->json_flag = false;
	type_data_connection->predefined_hashmap["disconnected"] = 0; // 0 means disconnected
	type_data_connection->predefined_hashmap["connected"] = 1; // 1 means connected
	defined_types.add(type_data_connection);

	/*
	 * service state
	 */
	CSSensorDataType *type_service_state = new CSSensorDataType();
	type_service_state->sensor_name = "service_state";
	type_service_state->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_service_state->parameters["state"] = json_spirit::Value_type(2);  // in Service
	type_service_state->parameters["manualSet"] = json_spirit::Value_type(3); // boolean: false
	type_service_state->parameters["phone number"] = json_spirit::Value_type(2); // telephone number +31619928120...
	type_service_state->predefined_hashmap["in service"] = 0;
	defined_types.add(type_service_state);

	/*
	 * signal strength
	 */
	CSSensorDataType *type_signal_strength = new CSSensorDataType();
	type_signal_strength->sensor_name = "signal_strength";
	type_signal_strength->json_flag = true;
	//json_spirit:: Value_type is in fact an enumerated integer
	type_signal_strength->parameters["GSM signal strength"] = json_spirit::Value_type(4);  // integer
	defined_types.add(type_signal_strength);
}



CSFilter::~CSFilter()
{
}


void rur::CSFilter::filterJSON(CSSensorData * cssensorData){
	// to show what cssensorData has been sent here for filtering
	string str = (cssensorData->value).get_str();
	cout << "String: "  << str <<endl;
	/*
	 * find if we know the sensor name from CSFilter.defined_types
	 */
	int sensor_index = defined_types.find(cssensorData->sensor_name);

	if(sensor_index!= -1) {
		cout<<"I find you: "<< cssensorData->sensor_name <<endl;
		/*
		 * get the cssensordatatype for further filtering, for example, it is 'position'
		 * the json_flag is true, we read in json value and parse the latitude and longitude
		 * according to parameter values
		 * if the sensor is 'Reachability', the json_flag is false, we DONOT read in the json value, but we do
		 * a get_str(), and parse it according to Parameter values (reachable is 1, and unreachable is 0)
		 */
		CSSensorDataType * cssensordatatype = defined_types.get_sensorType(sensor_index);
		/*
		 * if sensor name is noise, Availability, Location, Activity, Reachability, connection type, ip address, unread msg
		 * we don't convert them to json_spirit Value type!
		 */
		//cout << "Parameter Size: "<<(int)cssensordatatype->parameters.size()<<endl;
		if (cssensordatatype->json_flag){
			/*
			 * convert the cssensordata->value into json format
			 */
			json_spirit::Value value;
			if (!read(str, value)) {
				cout << "Value (wrong) type:" << value.type()<<endl;
				return;
			}

			/*
			 * dataobj is an array of json pairs.
			 * For example {"bearing":-1};{"longitude":4.47870534};{"provider":"network"};{"latitude":51.90969378}
			 */
			json_spirit::Object dataobj = value.get_obj();
			/*
			 * we iterate through the json pairs and filter out the useful information
			 * according to cssensorDataType.paramters
			 */
			for( json_spirit::Object::size_type i = 0; i != dataobj.size(); i++ ) {
				// we get the pair name and pair value (called value2 because we have a variable called value)
				const json_spirit::Pair& pair = dataobj[i];
				const string& name  = pair.name_;
				const json_spirit::Value&  value2 = pair.value_;


				if(cssensordatatype->parameters.count(name) >0) {
					/*
					 * cssensordatatype.parameters contains name, then we switch the data type
					 * to do further filtering. Whatever datatype it is, we output a double value
					 */
					//cssensordatatype->parameters[name]
					cout <<"Type is: "<<cssensordatatype->parameters[name]<<endl;

					if (cssensordatatype->parameters[name] != 2){
						double result = parse_jsonvalue(value2, cssensordatatype->parameters[name]);
						cssensorData->vector_values.push_back(result);
					}
					else {
						string rawdata = value2.get_str();
						vector <double> result = parse_jsonstring(cssensordatatype, name, rawdata);
						for (int i = 0; i<result.size();i++){
							cssensorData->vector_values.push_back(result[i]);
						}

					}

				}
			}
		}
		else {
			/*
			 * do sensor specific processing/filtering
			 */
			string sensor_str = cssensorData->value.get_str();
			cout << "The retrieved string content from Common Sense:" << sensor_str << endl;
			if (cssensorData->sensor_name == "noise"){
				double result = atof(sensor_str.c_str()); // sensor_str.c_str() will return a const char* which is the para for atof in stdlib.h
				//cout << "Result: "<<result<<endl;
				cssensorData->vector_values.push_back(result);
			}
			else if(cssensordatatype->predefined_hashmap.count(sensor_str)>0){
				double result = (double)cssensordatatype->predefined_hashmap[sensor_str];
				cout << cssensordatatype->sensor_name<<": "<<sensor_str<<" And it is encoded as: "<<result<<endl;
				cssensorData->vector_values.push_back(result);
			}

		}

	}
}

double rur::CSFilter::parse_jsonvalue(const json_spirit::Value & value, int index){
	double result = 0.0;
	switch (index)
	{
	case 3:{
		bool flag = value.get_bool();
		if (flag) result = 1;
		else result = 0;
		break;
	}
	case 4:{
		int rawdata = value.get_int();
		result = (double)rawdata;
		break;
	}
	case 5:{
		double rawdata = value.get_real();
		result = rawdata;
		break;
	}
	case 2:{
			string rawdata = value.get_str();
			cout << rawdata << endl;
			result = 77.77777;
			break;
		}
	default:
		result = 88.88888;
		break;
	}
	return result;
}


std::vector<double> rur::CSFilter::parse_jsonstring(CSSensorDataType * cssensordatatype,
		const std::string & specific_data_name,
		const std::string & specific_data_value){
	vector<double> result;
	if (cssensordatatype->sensor_name == "bluetooth_scan" && specific_data_name == "address"){
		std::vector<std::string> address;
		boost::split(address, specific_data_value, boost::is_any_of(":"));
		//cout <<"Hom many elements??" <<address.size()<<endl;
		for (int i = 0;i<address.size();i++){
			//cout << address[i]<<endl;
			char *pEnd;
			const char * c = address[i].c_str();
			long converted_address = strtol(c,&pEnd,16);
			cout << "Address: "<<address[i]<<" Converted Value: "<<converted_address <<endl;
			result.push_back((double)converted_address);
		}
	}
	else if (cssensordatatype->sensor_name == "wifi" && specific_data_name == "bssid"){
		std::vector<std::string> bssid;
		boost::split(bssid, specific_data_value, boost::is_any_of(":"));
		//cout <<"How many elements??" <<address.size()<<endl;
		for (int i = 0;i<bssid.size();i++){
			//cout << address[i]<<endl;
			char *pEnd;
			const char * c = bssid[i].c_str();
			long converted_bssid = strtol(c,&pEnd,16);
			cout << "bssid: "<<bssid[i]<<" Converted Value: "<<converted_bssid <<endl;
			result.push_back((double)converted_bssid);
		}
	}
	else if (cssensordatatype->sensor_name == "battery_state" && specific_data_name == "level"){
		//const char * c = specific_data_value.c_str();
		int level = atoi(specific_data_value.c_str());
		cout << "Battery Level: "<<level<<endl;
		result.push_back((double)level);
	}
	else if (cssensordatatype->sensor_name == "battery_state" && specific_data_name == "status"){
		//const char * c = specific_data_value.c_str();
		if (cssensordatatype->predefined_hashmap.count(specific_data_value) >0){
			int status = cssensordatatype->predefined_hashmap[specific_data_value];
			cout << "Battery Status: "<<specific_data_value<<" And it is encoded as: "<<status<<endl;
			result.push_back((double)status);
		}
		else{
			cout << "Error: can't find the hashmap for "<<cssensordatatype->sensor_name<<endl;
		}
	}
	else if (cssensordatatype->sensor_name == "screen_activity" && specific_data_name == "screen"){
		if (cssensordatatype->predefined_hashmap.count(specific_data_value) >0){
			int screen = cssensordatatype->predefined_hashmap[specific_data_value];
			cout << "Screen Value: "<<specific_data_value<<" And it is encoded as: "<<screen<<endl;
			result.push_back((double)screen);
		}
		else{
			cout << "Error: can't find the hashmap for "<<cssensordatatype->sensor_name<<endl;
		}
	}
	else if (cssensordatatype->sensor_name == "call_state" && specific_data_name == "state"){
		if (cssensordatatype->predefined_hashmap.count(specific_data_value) >0){
			int call_state = cssensordatatype->predefined_hashmap[specific_data_value];
			cout << "Call State: "<<specific_data_value<<" And it is encoded as: "<<call_state<<endl;
			result.push_back((double)call_state);
		}
		else{
			cout << "Error: can't find the hashmap for "<<cssensordatatype->sensor_name<<endl;
		}
	}
	else if (cssensordatatype->sensor_name == "service_state" && specific_data_name == "state"){
		if (cssensordatatype->predefined_hashmap.count(specific_data_value) >0){
			int service_state = cssensordatatype->predefined_hashmap[specific_data_value];
			cout << "Call State: "<<specific_data_value<<" And it is encoded as: "<<service_state<<endl;
			result.push_back((double)service_state);
		}
		else{
			cout << "Error: can't find the hashmap for "<<cssensordatatype->sensor_name<<endl;
		}
	}
	return result;
}

