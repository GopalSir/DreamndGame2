#include "../include/VertexAttribPointerGenerator.hpp"

VertexAttribPointer* VertexAttribPointerGenerator::generateVertexAttribPoinnter(STYLE _style)
{
    VertexAttribPointer* vap =  new VertexAttribPointer();
    switch (_style)
    {
    case STYLE::VERTEX:
 
        vap->shader_layout_index = 0;
        vap->count = 3;
        vap->type = GL_FLOAT;
        vap->normalized = GL_FALSE;
        vap->stride = 10*sizeof(GL_FLOAT);
        vap->ptr = (void*)0;

        break;
    case STYLE::COLOR:

        vap->shader_layout_index = 1;
        vap->count = 4;
        vap->type = GL_FLOAT;
        vap->normalized = GL_FALSE;
        vap->stride = 10 * sizeof(GL_FLOAT);
        vap->ptr = (void*)(3*sizeof(GL_FLOAT)) ;

        break;
    case STYLE::NORMALS:

        vap->shader_layout_index = 2;
        vap->count = 3;
        vap->type = GL_FLOAT;
        vap->normalized = GL_FALSE;
        vap->stride = 10 * sizeof(GL_FLOAT);
        vap->ptr = (void*)(7 * sizeof(GL_FLOAT));

        break;

    
    default:
        break;
    }
    return vap;
}