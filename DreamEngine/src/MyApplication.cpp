#include "../include/System/MyApplication.hpp"
//#include <unistd>

namespace DREAM
{

    MyApplication::MyApplication()
    {



        Log::Initialize();
        Log::LogMessage("Log Initialized", LogLevel::INFO_LEVEL);

        int glfwInitResult = glfwInit();

        if (!glfwInitResult)
        {
            Log::LogMessage("Initializing GLFW failed with message code: " + std::to_string(glfwInitResult));
        }

        window_width = 1080;
        window_height = 720;
        glfwWindow = glfwCreateWindow(window_width, window_height, "Game Window", nullptr, nullptr);
        glfwMakeContextCurrent(glfwWindow);
        int glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK) {
            Log::LogMessage("Initializing GLEW failed with message code: " + std::to_string(glewInitResult));


        }
        glEnable(GL_DEPTH_TEST);


        initializeShaders();
        setUpCameraSystem();
        /*Render System is expecting a camera active already. It won't search again once construcor is done. Will fix it later*/
        renderSystem = new RenderSystem(glfwWindow,programShader);
		physicsSystem = new PhysicsSystem(&dt_fixed_timestep);




        DREAM::EventSystem::registerEvent(DREAM::WindowCloseEvent::GetEventTypeCode(), renderSystem);
        glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window) {

            DREAM::WindowCloseEvent* windowCloseEvent = new DREAM::WindowCloseEvent();
            DREAM::EventSystem::handleEvent(windowCloseEvent);
            delete windowCloseEvent;


            });



        gameFPS = 120;
        requiredFrameTime = calculateRequiredFrameTime(gameFPS);
        Log::LogMessage("Required frame time" + std::to_string(requiredFrameTime.count()));

        
        //setTriangleEntity();
      

        glfwSetFramebufferSizeCallback(glfwWindow, GLFW_WindowResize_Callback_Handler);
        glfwSetScrollCallback(glfwWindow, GLFW_Scroll_Callback_Handler);
        glfwSetCursorPosCallback(glfwWindow, GLFW_CursorPosCallback_Handler);
        glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* _window, int _button, int _action, int mods) {
            MouseClickEvent* mouseClickEvent = new MouseClickEvent();
            mouseClickEvent->action = _action;
            mouseClickEvent->key = _button;
            mouseClickEvent->mods = mods;

			glfwGetCursorPos(_window, &mouseClickEvent->x, &mouseClickEvent->y);

            EventSystem::handleEvent(mouseClickEvent);
            });
            
        EventSystem::registerEvent(MouseClickEvent::GetEventTypeCode(), cameraSystem);
        glEnable(GL_PROGRAM_POINT_SIZE);

        gamestate = true;

        //setupGizmo();
        
        world = new World(renderSystem, physicsSystem, cameraSystem);
        
        backGroundColor = COLOR(0, 0, 0, 1);
    }


    MyApplication::~MyApplication()
    {
        log.~Log();
    }

    void MyApplication::fixedUpdate()
    {

        //All systems update will happen once per physics tick. 

        //Once user registers a system, it will be auto updated every physics tick. 
        for (auto i : gameSystems)
        {
            i->update();
        }

        physicsSystem->update();
    }

    
    void MyApplication::updateSystems()
    {
        cameraSystem->update();
        renderSystem->update();
    }

    bool MyApplication::getGameState()
    {
        return gamestate;
    }

    void MyApplication::addGameSystem(System* _system)
    {
        _system->setWorld(world);
        gameSystems.push_back(_system);
    }

    void MyApplication::setGameState(bool _gamestate)
    {
        gamestate = _gamestate;
    }

    void MyApplication::run()
    {
        completePostConstruct();
        bridgeSystems();
        frameStart = std::chrono::high_resolution_clock::now();
        accumulator = 0.0f;
        while (gamestate)
        {
            auto frameEnd = std::chrono::high_resolution_clock::now();
            actualFrameTime = frameEnd - frameStart;
            frameStart = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float>(actualFrameTime).count();


            glClearColor(backGroundColor.r,backGroundColor.g,backGroundColor.b,backGroundColor.a); // or your background color

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (glfwWindowShouldClose(glfwWindow))
            {

                gamestate = false;
            }

            accumulator += deltaTime;
            while(accumulator >= dt_fixed_timestep)
            {
                fixedUpdate();
                accumulator -= dt_fixed_timestep;
            }
            updateSystems();

             //glClearColor(0.5f, 0.3f, 0.8f, 1.0f); // Purple color

            // Clear the screen with the specified color

            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();


            //Time of last frame in seconds
            auto workTime = std::chrono::high_resolution_clock::now() - frameStart;
            if (workTime < requiredFrameTime)
                std::this_thread::sleep_for(requiredFrameTime - workTime);
                        
                    }

    }


    std::chrono::nanoseconds MyApplication::calculateRequiredFrameTime(int _gameFPS)
    {
        auto result = std::chrono::nanoseconds(1000000000) / _gameFPS;
        return result;
    }

    void  MyApplication::setTriangleEntity()
    {



    };

    bool MyApplication::initializeShaders()
    {
        // programShader = new Shader("C:\\Users\\Gaurav\\Documents\\IISC\\opengl\\test\\vertex_shader.glsl",
        //     "C:\\Users\\Gaurav\\Documents\\IISC\\opengl\\test\\fragment_shader.glsl");

        // programShader->use();
        // programShader->setUniform("screen_width", 1080);
        // programShader->setUniform("screen_height", 720);

        // programShader->setUniform("cam_x",-20.0f);
        // programShader->setUniform("cam_y",-20.0f);
        // programShader->setUniform("cam_z",0.0f);



        return true;
    }

    void MyApplication::setUpCameraSystem()
    {


        //cameraEntity = new CameraEntity(
        //    new PhysicsComponent(
        //        Vec4<float>(0, 0, 0, 0), Vec4<float>(0, 0, 0, 0), Vec4<float>(0, 0, 0, 0), Vec4<float>(0, 0, 0, 0)),
        //    new MVPComponent()
        //);
        //cameraEntity->active = true;

        cameraSystem = new CameraSystem(programShader,&deltaTime);
        //cameraSystem->addEntity(cameraEntity);


        //glfwSetWindowUserPointer(glfwWindow, this);
        glfwSetKeyCallback(glfwWindow, GLFW_KeyPress_Callback_Handler);
        

    }



    RenderSystem* MyApplication::GetRenderSystem()
    {
        return renderSystem;
    }

    CameraSystem* MyApplication::GetCameraSystem()
    {
        
        return cameraSystem;

    }

    PhysicsSystem* MyApplication::GetPhysicsSystem()
    {
        return physicsSystem;
    }

    void MyApplication::bridgeSystems()
    {
        // This function is used to bridge the systems together, if needed.
        // For now, it does nothing but can be extended in the future.
        Log::LogMessage("Bridging systems together", LogLevel::INFO_LEVEL);
        if (renderSystem && cameraSystem)
        {
            Log::LogMessage("RenderSystem and CameraSystem are available for bridging", LogLevel::INFO_LEVEL);
            renderSystem->SetActiveCamera(cameraSystem->getActiveCamera());
        }
        else
        {
            Log::LogMessage("RenderSystem or CameraSystem is not initialized properly", LogLevel::ERROR_LEVEL);
        }
    }
	void MyApplication::completePostConstruct()
	{
        for (auto entity : gameEntities)
        {
			entity->doPostConstruct();
        }
	}

    void MyApplication::setupGizmo()
    {

        Entity* gizmo_x_axis = CreateEntity();
        Entity* gizmo_y_axis = CreateEntity();
        Entity* gizmo_z_axis = CreateEntity();

        Shape::BuildLineShape(gizmo_x_axis, 0, 0, 0, 1000, 0, 0,COLOR(1,0,0,1) );
        Shape::BuildLineShape(gizmo_y_axis, 0, 0, 0, 0, 1000, 0, COLOR(0, 1, 1, 1));
        Shape::BuildLineShape(gizmo_z_axis, 0, 0, 0, 0, 0, 1000, COLOR(0, 0, 1, 1));

        int x_axis_id = renderSystem->addEntity(gizmo_x_axis);
        int y_axis_id = renderSystem->addEntity(gizmo_y_axis);
        int z_axis_id = renderSystem->addEntity(gizmo_z_axis);

        renderSystem->initEntityBuffers(x_axis_id);
        renderSystem->initEntityBuffers(y_axis_id);
        renderSystem->initEntityBuffers(z_axis_id);

    }

	void MyApplication::gizmoVisibility(bool _visibility)
	{
		//Set the visibility of the gizmo
		//This will be used to toggle the visibility of the gizmo in the scene.
		//Currently, it does nothing as we have not implemented the gizmo yet.
		Log::LogMessage("Gizmo visibility set to " + std::to_string(_visibility), LogLevel::INFO_LEVEL);
        
	}

    void MyApplication::setBackGroundColor(COLOR &_color)
    {
        backGroundColor = _color;
    }

    Entity* MyApplication::CreateEntity()
    {
        Entity* result = new Entity(GetGUID());
        gameEntities.push_back(result);
        return result;
    }

    //Destry an entity by first removing it from all the systems it's attached to. 
    void MyApplication::DestroyEntity(Entity* _entity)
    {

    }

    void MyApplication::RegisterEntity(Entity* _entity)
    {

        if(_entity->getComponent<PhysicsComponent>())
        {
            physicsSystem->addEntity(_entity);
        }

        if(_entity->getComponent<VerticesComponent<float>>())
        {
            int idx = renderSystem->addEntity(_entity);
            renderSystem->initEntityBuffers(idx);
        }

        for (auto* system : gameSystems)
        {
            system->addEntity(_entity);
        }
    }

    //Walk through all entities
    void MyApplication::SaveGame(std::string _saveLocation)
    {

        std::fstream saveStream(_saveLocation);

        //We'll create the file
        if(!saveStream)
        {
            Log::LogMessage("Cannot create file with name  " + _saveLocation);
        }
        
        for(auto* entity: gameEntities)
        {
            
        }
    }

}

