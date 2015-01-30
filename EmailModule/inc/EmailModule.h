namespace rur {

class EmailModule {
private:
  
  int dummyInput;
  

public:
  EmailModule() {
  }
  
  ~EmailModule() { }
  
  void Tick();
  
  void Init() { }
  
  inline int *readInput(int index = 0) {
    return &dummyInput;
  }
  
  inline void writeOutput(const int output, int index = 0) {
  }
  
};
}

