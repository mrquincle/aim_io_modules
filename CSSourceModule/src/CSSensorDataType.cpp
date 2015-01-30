/*
 * CSSensorDataType.cpp
 *
 *  Created on: Apr 5, 2012
 *      Author: scot
 */
#include <CSSensorDataType.h>

using namespace std;

int CSSensorDataTypes::find(string sensor_name) {
	bool flag = false;
	int i =0;
	for (i = 0;i<types.size();i++){
		if (types[i]->sensor_name == sensor_name){
			flag = true;
			break;
		}
	}
	if (flag){
		return i;
	}
	else{
		return -1;
	}
}



void CSSensorDataTypes::add(CSSensorDataType* type) {
	types.push_back(type);
}

CSSensorDataType *CSSensorDataTypes::get_sensorType(int index){
	// index>=0 &&  index< length of types
	if (index >= 0 && index< types.size()){
		return types[index];
	}
	return NULL;
}


