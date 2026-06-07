#pragma once
#include "./Component/VertexAttribComponent.hpp"

class VertexAttribPointerGenerator
{
    public:
    enum STYLE
    {
        VERTEX,
        COLOR,
        NORMALS
    };

    static VertexAttribPointer* generateVertexAttribPoinnter(STYLE _style);
};