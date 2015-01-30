/**
 * @file CSFilter.h
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
 * @author  Scott Guo
 * @date    April 2, 2012
 * @project Seam4US FP7
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#ifndef CSFILTER_H_
#define CSFILTER_H_

#include <CSSensorData.h>
#include <CSSensorDataType.h>
#include <json_spirit_value.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

namespace rur {

/**
 * CSSensorData is still very complex for processing, we need to parse it and output a vector
 */
class CSFilter {
public:
	CSFilter();

	~CSFilter();

	void filterJSON(CSSensorData * cssensorData);

	double parse_jsonvalue(const json_spirit::Value& value, int index);

	std::vector<double> parse_jsonstring(CSSensorDataType *, const std::string& specific_data_name, const std::string& specific_data_value);

private:
	CSSensorDataTypes defined_types;

};


}


#endif /* CSFILTER_H_ */
