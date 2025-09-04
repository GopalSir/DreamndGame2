#include "ShapeCreator.hpp"

int ShapeCreator::handleEvent(DREAM::EventInfo* _eventInfo)
{
    static int first_point_planted = false;

    Log::LogMessage("Shape Creator handler activated\n");

    if (_eventInfo->getEventTypeCode() == DREAM::MouseClickEvent::GetEventTypeCode())
    {
        DREAM::MouseClickEvent* _mouseClickEvent = dynamic_cast<DREAM::MouseClickEvent*>(_eventInfo);

        std::cout << _mouseClickEvent->x << " " << _mouseClickEvent->y<<"\n";

        COLOR defaultColor = COLOR();


        Vec4<float> stw = DREAM::RenderSystem::ScreenToWorldCoordinate(Vec4<float>(_mouseClickEvent->x, _mouseClickEvent->y, 0,1), cameraComponent );
       Entity* point =  Shape::GetPointShape(stw.x, stw.y, stw.z, defaultColor);

       current_stw = stw;


       

       std::cout << stw.x<<" " << stw.y<<" " << stw.z <<" " <<stw.w<< "\n";
       std::cout << "Camera Position" << cameraPhysicsComponent->position.x << " " << cameraPhysicsComponent->position.y << " " << cameraPhysicsComponent->position.z << " " << cameraPhysicsComponent->position.w << "\n";

       int current_point = renderSystem->addEntity(point);

  

       renderSystem->initEntityBuffers(current_point);


       //draw a line between current and previous point.
       if (first_point_planted == true)
       {
           Entity* temp_line_entity = Shape::GetLineShape(previous_stw.x, previous_stw.y, previous_stw.z, current_stw.x, current_stw.y, current_stw.z, COLOR::COLOR(100, 100, 100, 1));
           int temp_lint_entity_index = renderSystem->addEntity(temp_line_entity);
           renderSystem->initEntityBuffers(temp_lint_entity_index);
       }

       previous_stw = current_stw;

       if (first_point_planted == false)
       {
           first_point_planted = true;
       }


       ////Debug
       //Entity* tempLine = Shape::GetLineShape(0, 0, 0,500, 500, 500, defaultColor);
       //int tempID = renderSystem->addEntity(tempLine);
       //renderSystem->initEntityBuffers(tempID);

       

    }

    return 0;
}

ShapeCreator::ShapeCreator(PhysicsComponent* _physicsComponent, DREAM::RenderSystem* _renderSystem, DREAM::CameraComponent* _cameraComponent)
{
    cameraPhysicsComponent = _physicsComponent;
    renderSystem = _renderSystem;
    cameraComponent = _cameraComponent;
}
