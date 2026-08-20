#define GLEW_NO_GLU
#include "../include/MyGame.h"




/*
Entry point for the application
*/
int main()
{

	auto myGame = new MyGame();
	myGame->run();
	
	//int a;
	//scanf_s("%i", &a);

	return 0;
}