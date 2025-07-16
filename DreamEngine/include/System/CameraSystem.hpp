#pragma once
#include <ECS_Core/Core.hpp>
#include <math.h>
#include "../Vec3.hpp"
#include "../EVENTS.hpp"
#include "../System/EventSystem.hpp"
#include "../Entity/CameraEntity.hpp"
#include "../IEventHandler.hpp"
#include "../Shader.hpp"
#include "../KeyStates.h"

namespace DREAM {
    class CameraSystem :public System, public IEventHandler
    {
        Shader* shader;
        float cam_x, cam_y;
        float cam_x_velocity, cam_y_velocity;
    public:
        CameraSystem(Shader* _shader);
        void update() override;
        // template<typename T>
        // static PositionComponent<T> TranslatePoint(PositionComponent<T>*, CameraEntity*);

        // template<typename T>
        // void TranslatePoints(std::vector<PositionComponent<T>>);

        int PrintCamera(EventInfo* _eventInfo);
        int handleEvent(EventInfo* _eventInfo) override;


    };

    // template <typename T>
    // PositionComponent<T> CameraSystem::TranslatePoint(PositionComponent<T>* _positionComponenet,CameraEntity* _cameraEntity)
    // {
    //     PositionComponent<T> result;
    //     result.x = _positionComponenet->x - _cameraEntity->getComponent<PositionComponent<T>>()->x;
    //     result.y = _positionComponenet->y - _cameraEntity->getComponent<PositionComponent<T>>()->y;
    //     result.z = _positionComponenet->z - _cameraEntity->getComponent<PositionComponent<T>>()->z;
    //     return result;
    // }
}