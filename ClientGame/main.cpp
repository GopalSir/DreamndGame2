#define GLEW_NO_GLU
//#include "../include/System/MyApplication.hpp"
#include "MyGame.h"
#include <EntryPoint.hpp>


/*
Entry point for the application
*/
int main()
{


	auto mygame = CreateApplication();
	mygame->run();

 return 0;
}