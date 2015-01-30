/*
 * CSSensorDataType.h
 *
 *  Created on: Apr 5, 2012
 *      Author: scot
 */

#ifndef CSSENSORDATATYPE_H_
#define CSSENSORDATATYPE_H_

#include <vector>
#include <string>
#include <map>
//#include <json_spirit_value.h>


/**
 * The CSSensorDataType is different from CSSensorData because the latter is
 * used for parsing the json information and not the "value" of the sensor.
 * The value however, also needs to be parsed. And this is done by information
 * from CSSensorDataType(s).
 */
class CSSensorDataType {
public:
	/*
	 * we create a map between parameters and integers
	 * if the parameters are from json value, the integers annotate json_spirit value type
	 * if the parameters are enumerated per sensor type, the integers are the enumeration number from 0 upwards
	 * if the parameters are only boolean, then the integers can be 0 or 1
	 */
	std::map<std::string, int> parameters;
	//std::vector<std::string> parameters;
	std::string sensor_name;
	bool json_flag;

	std::map<std::string, int> predefined_hashmap;
};

class CSSensorDataTypes {
public:
	int find(std::string sensor_name);

	void add(CSSensorDataType* type);

	CSSensorDataType* get_sensorType(int index);
private:
	std::vector<CSSensorDataType*> types;
};



#endif /* CSSENSORDATATYPE_H_ */
