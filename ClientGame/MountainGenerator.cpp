#include "MountainGenerator.h"

float MountainGenerator::SampleHeight(float _x, float _y, float _xMax, float _yMax, float _xFreq, float _yFreq, float _maxHeight)
{
	return  (std::sin(_xFreq * 2*3.14* _x / _xMax) * std::sin(_yFreq * 2 * 3.14 * _y / _yMax) * _maxHeight);
}

float Hash(int x, int y)
{
    int h = x * 374761393 + y * 668265263;
    h = (h ^ (h >> 13)) * 1274126177;
    return (h & 0x7fffffff) / float(0x7fffffff);
}

float ValueNoise(float x, float y)
{
    int xi = int(x);
    int yi = int(y);

    float tx = x - xi;
    float ty = y - yi;

    float c00 = Hash(xi, yi);
    float c10 = Hash(xi + 1, yi);
    float c01 = Hash(xi, yi + 1);
    float c11 = Hash(xi + 1, yi + 1);

    float cx0 = c00 + (c10 - c00) * tx;
    float cx1 = c01 + (c11 - c01) * tx;

    return cx0 + (cx1 - cx0) * ty;
}



float MountainGenerator::SampleRidgeHeight(float x, float y, float max_x, float max_y, float freq, float max_height)
{
    float nx = (x / max_x) * freq;
    float ny = (y / max_y) * freq;

    float n = ValueNoise(nx, ny); // base noise
    float r = 1.0f - fabs(n);     // ridge shape
    r = r * r;                    // sharpen

    return r * max_height;
}