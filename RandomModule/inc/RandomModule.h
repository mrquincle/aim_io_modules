/**
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
 * Copyright (c) 2010 Anne van Rossum <anne@almende.com>
 *
 * @author  Anne C. van Rossum
 * @company Almende B.V.
 */

// general C/C++ headers
#include <vector>
#include <string>
#include <sstream>

// middleware specific headers
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>
#include <yarp/os/Bottle.h>

// namespaces and typedefs
using namespace yarp::os;

// recommended namespace: "Rur"
// add "using namespace Rur;" to your .cpp file
namespace rur {

// The generated class. Do not modify or add class members
// Either derive from this class and implement Tick() or
// use a separate helper class to store state information.
// All information for the operation of the module should 
// be obtained over the defined ports
class RandomModule {
private:
  Network yarp;
  std::string module_id;
  
  std::vector< BufferedPort <Bottle>* > portRes;

public:
  // The constructor needs to be called, also when you derive from this class
  RandomModule() {
    
    for (int i = 0; i < 1; ++i) {
      portRes.push_back(new BufferedPort <Bottle>() );
    }
  }
  
  ~RandomModule() { }
  
  // This is the function you will need to implement.
  void Tick(); 
  
  // After construction you will need to call this function first
  // it opens the YARP ports
  void Init(std::string module_id) {
    this->module_id = module_id;
    
    
    std::vector< BufferedPort <Bottle>* >::iterator iRes;
    int iResIndex = 0;
    for (iRes = portRes.begin(); iRes != portRes.end(); ++iRes) {
      std::stringstream portName; portName.str(); portName.clear();
      portName << "/randommodule" << module_id << "/res" << iResIndex;
      (*iRes)->open(portName.str().c_str());
      ++iResIndex;
    }
  }
  
protected:
  // All subsequent functions should be called from "within" this module
  // From either the Tick() routine itself, or Tick() in a derived class
  
  inline void writeRes(const int output, int index = 0) {
    Bottle &outputPrepare = portRes[index]->prepare();
    outputPrepare.clear();
    outputPrepare.addInt(output);
    portRes[index]->write();
  }
  
};
}

