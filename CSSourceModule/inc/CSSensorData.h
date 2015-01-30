/**
 * @file CSSensorData.h
 * @brief Default CommonSense sensor data structure
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

#ifndef CSSensorData_H_
#define CSSensorData_H_

#include <string>
#include <vector>

#include <json_spirit_value.h>

namespace rur {

/**
 * The default data item from CommonSense is something like this, where the actual value can
 * be a float, int or json string.
 */
class CSSensorData {
public:
	CSSensorData(std::string json);

	int id;
	int sensor_id;
	json_spirit::Value value;
	time_t date;
	int week;
	int month;
	int year;


	// sensor_name
	std::string sensor_name;
	// output port??
	std::vector<double> vector_values;

	//! Status value to indicate that parsing went okay
	bool valid;
};

}

#endif /* CSSensorData_H_ */
