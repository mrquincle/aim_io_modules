/**
 * @file CSLoginModuleAuth.cpp
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
 * Copyright © 2010 Anne van Rossum <anne@almende.com>
 *
 * @author  Anne C. van Rossum
 * @date    Feb 12, 2012
 * @project Replicator FP7
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */

#include <CSLoginModuleAuth.h>
#include <csconnect/CSConnectFactory.h>
#include <csconnect/CSConnect.h>

#include <string>
#include <iostream>

using namespace rur;
using namespace cs;
using namespace std;

/**
 * The Tick() routine is overloaded.
 */
void CSLoginModuleAuth::Tick() {
	CSConnectFactory* fac = CSConnectFactory::Instance(CURL_CONNECTOR);
	CSConnect *c = fac->GetNewConnector();
	c->Init();
	if (oauth_step == "oauth0") {
		cout << "Execute first step of authorisation" << endl;
		CSLogin * id = new CSLogin();
		id->value.push_back(oauth_step);
		c->Login(*id);
		if (id->value.size() != 2) {
			delete id;
			return;
		}
		string key = id->value[0];
		string secret = id->value[1];
		cout << "key: " << key << endl;
		cout << "secret: " << secret << endl;
		delete id;
	} else if (oauth_step == "oauth1") {
		cout << "Execute second step of authorisation" << endl;
		CSLogin * id = new CSLogin();
		id->value.push_back(oauth_token);
		id->value.push_back(oauth_secret);
		id->value.push_back(oauth_verifier);
		id->value.push_back(oauth_step);
		c->Login(*id);
		if (id->value.size() != 2) {
			delete id;
			return;
		}
		string key = id->value[0];
		string secret = id->value[1];
		cout << "key: " << key << endl;
		cout << "secret: " << secret << endl;
		delete id;
	}
}


