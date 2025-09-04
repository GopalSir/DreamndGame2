#pragma once
#include <ECS_Core/Core.hpp>
#include "../glheaders.hpp"
#include "../Colors.h"


class DrawableComponent: public Component
{
    public:
    GLuint VBO;
    GLuint VAO;
	COLOR color;
	

	//Type of the drawable object
	enum DRAWABLE_TYPE
	{
		LINE = GL_LINES,
		TRIANGLE = GL_TRIANGLES,
		POINT = GL_POINTS
	};

	DRAWABLE_TYPE drawable_type;

	DrawableComponent(DRAWABLE_TYPE _type)
		: drawable_type(_type)
	{
		VBO = 0;
		VAO = 0;
		color = COLOR();
	}
	~DrawableComponent()
	{
		if (VBO != 0) glDeleteBuffers(1, &VBO);
		if (VAO != 0) glDeleteVertexArrays(1, &VAO);
	}


};