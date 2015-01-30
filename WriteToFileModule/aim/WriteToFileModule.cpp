/**
 * @file WriteToFileModule.cpp
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
 * Copyright © 2011 scott guo <scott@almende.org>
 *
 * @author  Scott Guo
 * @date    Jan 4, 2012
 * @project 
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#include <WriteToFileModule.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace rur;
using namespace std;

void WriteToFileModule::Tick() {
	double input1 = *readInp1();
	
	double input2 = *readInp2();
	
	ofstream myfile(cliParam->filename.c_str(), ios::app);
	myfile << input1 << '\t' << input2 << '\n';
	myfile.close();
}
