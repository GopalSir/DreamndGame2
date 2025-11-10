#pragma 
#include <cmath>

class MountainGenerator
{
private:
	
public:
	static float SampleHeight(float _x, float _y, float _xMax, float _ymax, float _xFreq, float y_freq,float _maxHeight);
	static float SampleRidgeHeight(float x, float y, float max_x, float max_y, float freq, float max_height);
};

