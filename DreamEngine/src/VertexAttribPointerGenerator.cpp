#include "../include/VertexAttribPointerGenerator.hpp"

VertexAttribComponent* VertexAttribPointerGenerator::generateVertexAttribPoinnter(STYLE _style)
{
    VertexAttribComponent* vap =  new VertexAttribComponent();
    switch (_style)
    {
    case STYLE::DEFAULT:
 
        vap->shader_layout_index = 0;
        vap->count = 3;
        vap->type = GL_FLOAT;
        vap->normalized = GL_FALSE;
        vap->stride = 3*sizeof(GL_FLOAT);
        vap->ptr = (void*)0;

        break;
    
    default:
        break;
    }
    return vap;
}