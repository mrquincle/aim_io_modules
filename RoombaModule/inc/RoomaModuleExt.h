#include <RoombaModule.h>

public class RoombaModuleExt: public RoombaModule {


public:
	inline void setAlpha(int alpha) { this->alpha = alpha; }

	void setBeta(float beta);

	void Tick();
private:

	int alpha;

};
