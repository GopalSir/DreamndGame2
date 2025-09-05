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
        glfwWindow = glfwCreateWindow(1080, 720, "Game Window", nullptr, nullptr);
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
		physicsSystem = new PhysicsSystem(&deltaTime);




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

        setupGizmo();
         
        
    }


    MyApplication::~MyApplication()
    {
        log.~Log();
    }

    void MyApplication::updateSystems()
    {

        cameraSystem->update();
        renderSystem->update();
		physicsSystem->update();

        //for (auto i : gameSystems)
        //{
        //    i->update();
        //}
    }

    bool MyApplication::getGameState()
    {
        return gamestate;
    }

    void MyApplication::setGameState(bool _gamestate)
    {
        gamestate = _gamestate;
    }

    void MyApplication::run()
    {
        completePostConstruct();
        bridgeSystems();
        while (gamestate)
        {
            //glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // or your background color

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            frameStart = std::chrono::high_resolution_clock::now();
            if (glfwWindowShouldClose(glfwWindow))
            {

                gamestate = false;
            }

            updateSystems();

             //glClearColor(0.5f, 0.3f, 0.8f, 1.0f); // Purple color

            // Clear the screen with the specified color

            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();

            auto frameEnd = std::chrono::high_resolution_clock::now();
            actualFrameTime = frameEnd - frameStart;
            //Time of last frame in seconds
			deltaTime = std::chrono::duration<float>(actualFrameTime).count();
            if (actualFrameTime < requiredFrameTime)
            {
                requiredSleepTime = requiredFrameTime - actualFrameTime;
                std::this_thread::sleep_for(requiredSleepTime);
            }
        }

    }

    std::chrono::nanoseconds MyApplication::calculateRequiredFrameTime(int _gameFPS)
    {
        auto result = std::chrono::nanoseconds(1000000000) / _gameFPS;
        return result;
    }

    void  MyApplication::setTriangleEntity()
    {/*
        TriangleEntity* player = new TriangleEntity();
        TriangleEntity* enemy = new TriangleEntity();

        VerticesComponent<float>* playerVertexComponent = new VerticesComponent<float>;
        VerticesComponent<float>* enemyVertexComponent = new VerticesComponent<float>;

        DrawableComponent* playerDrawableComponent = new DrawableComponent();
        DrawableComponent* enemyDrawableComponent = new DrawableComponent();


        playerVertexComponent->vertices.push_back( PositionComponent<float>(20, 20, 0));
        playerVertexComponent->vertices.push_back(PositionComponent<float>(40, 20, 0));
        playerVertexComponent->vertices.push_back(PositionComponent<float>(40, 40, 0));



        VertexAttribComponent* playerVertexAttribComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(
            VertexAttribPointerGenerator::STYLE::DEFAULT
        );



        player->addComponent(playerVertexComponent);
        player->addComponent(playerVertexAttribComponent);
        player->addComponent(playerDrawableComponent);

        enemyVertexComponent->vertices.push_back( PositionComponent<float>(100, 100, 0));
        enemyVertexComponent->vertices.push_back( PositionComponent<float>(200, 100, 0));
        enemyVertexComponent->vertices.push_back(PositionComponent<float>(200, 200, 0));


        VertexAttribComponent* enemyVertexAttribComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(
            VertexAttribPointerGenerator::STYLE::DEFAULT
        );

        enemy->addComponent(enemyVertexComponent);
        enemy->addComponent(enemyVertexAttribComponent);
        enemy->addComponent(enemyDrawableComponent);

        playerEntityID = renderSystem->addEntity(player);
        enemyEntityID = renderSystem->addEntity(enemy);

        renderSystem->initEntityBuffers(playerEntityID);
        renderSystem->initEntityBuffers(enemyEntityID);


        RectangleEntity* rectangle = new RectangleEntity(60, 60, 40, 100);

        int rectangleEntityID = renderSystem->addEntity(rectangle);
        renderSystem->initEntityBuffers(rectangleEntityID);

        RectangleEntity* rectangle2 = new RectangleEntity(600, 600, 40, 100);

        int rectangleEntityID2 = renderSystem->addEntity(rectangle2);
        renderSystem->initEntityBuffers(rectangleEntityID2);*/


    };

    bool MyApplication::initializeShaders()
    {
        programShader = new Shader("C:\\Users\\Gaurav\\Documents\\IISC\\opengl\\test\\vertex_shader.glsl",
            "C:\\Users\\Gaurav\\Documents\\IISC\\opengl\\test\\fragment_shader.glsl");

        programShader->use();
        programShader->setUniform("screen_width", 1080);
        programShader->setUniform("screen_height", 720);

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
        for (auto entity : cameraSystem->entities)
        {
			entity->doPostConstruct();
        }
	}

    void MyApplication::setupGizmo()
    {
		//Crate 3 axis lines in the scene.
        Entity* gizmo_x_axis = Shape::GetLineShape(0, 0, 0, 1000, 0, 0,COLOR(1,0,0,1) );
        Entity* gizmo_y_axis = Shape::GetLineShape(0, 0, 0, 0, 1000, 0, COLOR(0, 1, 1, 1));
        Entity* gizmo_z_axis = Shape::GetLineShape(0, 0, 0, 0, 0, 1000, COLOR(0, 0, 1, 1));

       int x_axis_id =  renderSystem->addEntity(gizmo_x_axis);
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


}

