#pragma once

struct COLOR
{
	float r, g, b, a;
	COLOR()
	{
		r = 1;
		g = 0;
		b = 0.5;
		a = 1;

	};
	COLOR(float _r,float _g,float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;

	};
};
