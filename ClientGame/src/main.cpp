#define GLEW_NO_GLU
//#include "../include/System/MyApplication.hpp"
#include "../include/LuaIntegration.h"




/*
Entry point for the application
*/
int main()
{
	LuaIntegration::run();

	int a;
	scanf_s("%i", &a);

	return 0;
}