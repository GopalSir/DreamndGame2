#pragma once
#include "./Component/VertexAttribComponent.hpp"

class VertexAttribPointerGenerator
{
    public:
    enum STYLE
    {
        DEFAULT
    };

    static VertexAttribComponent* generateVertexAttribPoinnter(STYLE _style);
};