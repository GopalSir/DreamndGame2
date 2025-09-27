#include "../include/Entity/RectangleEntity.hpp"

RectangleEntity::RectangleEntity(float _x, float _y, float _length,float _breadth)
{
    this->addComponent(
        new PhysicsComponent(
            Vec4<float>(0,0,0,0),Vec4<float>(0,0,0,0),Vec4<float>(0,0,0,0),Vec4<float>(0,0,0,0)
        )
    );


    std::vector<PositionComponent<float>> pc;
    pc.push_back( PositionComponent<float>(_x,_y,0));
    pc.push_back( PositionComponent<float>(_x,_y+_length,0));
    pc.push_back( PositionComponent<float>(_x+_breadth,_y+_length ,0));

    pc.push_back( PositionComponent<float>(_x,_y,0));
    pc.push_back( PositionComponent<float>(_x+_breadth,_y + _length,0));
    pc.push_back( PositionComponent<float>(_x + _breadth,_y,0));

    VerticesComponent<float>* vc = new VerticesComponent<float>;
    vc->vertices = pc;
    
    this->addComponent(vc);

    //VertexAttribComponent* rectangleVertexAttribComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(
    //    VertexAttribPointerGenerator::STYLE::DEFAULT);


    //this->addComponent(rectangleVertexAttribComponent);
    //this->addComponent(new DrawableComponent());
    
};
