#include <string>

namespace rur {

class CSCreateSensorModule {
private:
  
  int dummyInput;
  

public:
  CSCreateSensorModule() {
  }
  
  ~CSCreateSensorModule() { }
  
  void Tick();
  
  void Init(std::string & name) { }
  
  inline int *readInput(int index = 0) {
    return &dummyInput;
  }
  
  inline void writeOutput(const int output, int index = 0) {
  }
  
};
}

