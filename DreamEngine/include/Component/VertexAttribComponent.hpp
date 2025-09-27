#pragma once
#include <ECS_Core/Core.hpp>
#include "../glheaders.hpp"

struct VertexAttribPointer
{

	public:
	int shader_layout_index;

	/*Number of elements per vertex*/
	int count;

	GLenum type;

	/* wether normalized */
	GLboolean normalized;

	/* stride */
	GLsizei stride;

	/*position of the first element in array*/
	void* ptr;
};