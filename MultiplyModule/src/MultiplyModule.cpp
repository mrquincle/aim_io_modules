/**
 * @file MultiplyModule.cpp
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
 * Copyright © 2011 scott guo <scott@almende.com>
 *
 * @author  Scott Guo
 * @date    Jan 4, 2012
 * @project 
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#include <MultiplyModule.h>
#include <stdlib.h>
#include <iostream>

using namespace rur;
using namespace std;



void MultiplyModule::Tick() {
	double input1 = *readIn1();
	
        double input2 = *readIn2();	
	//cout << "Write value: " << current_value << endl;
	writeRes(input1*input2);

}
