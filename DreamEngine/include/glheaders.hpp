#pragma once
#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLFW includes windows.h on Windows - clean up macro pollution
#ifdef _WIN32
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
#endif