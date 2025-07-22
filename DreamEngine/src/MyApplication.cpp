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


        renderSystem = new RenderSystem(glfwWindow);





        DREAM::EventSystem::registerEvent(DREAM::WindowCloseEvent::GetEventTypeCode(), renderSystem);
        glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window) {

            DREAM::WindowCloseEvent* windowCloseEvent = new DREAM::WindowCloseEvent();
            DREAM::EventSystem::handleEvent(windowCloseEvent);
            delete windowCloseEvent;


            });



        gameFPS = 120;
        requiredFrameTime = calculateRequiredFrameTime(gameFPS);
        Log::LogMessage("Required frame time" + std::to_string(requiredFrameTime.count()));

        initializeShaders();
        //setTriangleEntity();
        setUpCameraSystem();

        glfwSetFramebufferSizeCallback(glfwWindow, GLFW_WindowResize_Callback_Handler);
        glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* _window, int _button, int _action, int mods) {
            MouseClickEvent* mouseClickEvent = new MouseClickEvent();
            mouseClickEvent->action = _action;
            mouseClickEvent->key = _button;
            mouseClickEvent->mods = mods;

			glfwGetCursorPos(_window, &mouseClickEvent->x, &mouseClickEvent->y);

            EventSystem::handleEvent(mouseClickEvent);
            });
            
        EventSystem::registerEvent(MouseClickEvent::GetEventTypeCode(), cameraSystem);
        gamestate = true;
    }


    MyApplication::~MyApplication()
    {
        log.~Log();
    }

    void MyApplication::updateSystems()
    {
        cameraSystem->update();
        renderSystem->update();

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
        while (gamestate)
        {
            glClear(GL_COLOR_BUFFER_BIT);
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
    {
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
        renderSystem->initEntityBuffers(rectangleEntityID2);


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

        cameraSystem = new CameraSystem(programShader);
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

}

