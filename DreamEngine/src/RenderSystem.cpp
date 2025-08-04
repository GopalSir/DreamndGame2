#include "../include/System/RenderSystem.hpp"

namespace DREAM
{
    RenderSystem::RenderSystem(GLFWwindow* _glfwWindow,Shader* _shader)
    {
        if (_glfwWindow == nullptr)
        {
            Log::LogMessage("RenderSystem Error: glfw window parameter is nullptr", LogLevel::ERROR_LEVEL);
            exit(0);
        }
        else
        {
			glfwWindow = _glfwWindow;
			shader = _shader;


            Log::LogMessage("RenderSystem Info: glfw window ok", LogLevel::INFO_LEVEL);

      



        }
    }

    Mat4<float> RenderSystem::CalculateMVP(Mat4<float>& _projection, Mat4<float>& _view, Mat4<float>& _model = Mat4<float>::identity)
    {
		Mat4<float> resultMVP = _projection * _view * _model;
        return resultMVP;
    }

    void RenderSystem::update()
    {
        // std::cout<<"Render System being updated at 1 fps";

        // go through all entities and take out their Vertices to render
        for (auto* tempEntities : entities)
        {
            //for open gl , we gotta bind to the buffer first 
            int tempVBO = tempEntities->getComponent<DrawableComponent>()->VBO;
            int tempVAO = tempEntities->getComponent<DrawableComponent>()->VAO;

			

            int verticesCount = tempEntities->getComponent<VerticesComponent<float>>()->vertices.size();
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
            glBindVertexArray(tempVAO);

            Mat4<float> tempMVP = CalculateMVP(activeCameraComponent->projection, activeCameraComponent->cameraViewMatrix);
            shader->setUniform("mvp", tempMVP);

            //Logging MVP
            //std::cout << tempMVP.r1.x << " " << tempMVP.r1.y << " " << tempMVP.r1.z << " " << tempMVP.r1.w << "\n";
            //std::cout << tempMVP.r2.x << " " << tempMVP.r2.y << " " << tempMVP.r2.z << " " << tempMVP.r2.w << "\n";
            //std::cout << tempMVP.r3.x << " " << tempMVP.r3.y << " " << tempMVP.r3.z << " " << tempMVP.r3.w << "\n";
            //std::cout << tempMVP.r4.x << " " << tempMVP.r4.y << " " << tempMVP.r4.z << " " << tempMVP.r4.w << "\n";

           // Logging Projection matrix
			std::cout << activeCameraComponent->projection.r1.x << " " << activeCameraComponent->projection.r1.y << " " << activeCameraComponent->projection.r1.z << " " << activeCameraComponent->projection.r1.w << "\n";
			std::cout << activeCameraComponent->projection.r2.x << " " << activeCameraComponent->projection.r2.y << " " << activeCameraComponent->projection.r2.z << " " << activeCameraComponent->projection.r2.w << "\n";
			std::cout << activeCameraComponent->projection.r3.x << " " << activeCameraComponent->projection.r3.y << " " << activeCameraComponent->projection.r3.z << " " << activeCameraComponent->projection.r3.w << "\n";
			std::cout << activeCameraComponent->projection.r4.x << " " << activeCameraComponent->projection.r4.y << " " << activeCameraComponent->projection.r4.z << " " << activeCameraComponent->projection.r4.w << "\n";

			//Logging View matrix
		/*	std::cout << activeCameraComponent->cameraViewMatrix.r1.x << " " << activeCameraComponent->cameraViewMatrix.r1.y << " " << activeCameraComponent->cameraViewMatrix.r1.z << " " << activeCameraComponent->cameraViewMatrix.r1.w << "\n";
			std::cout << activeCameraComponent->cameraViewMatrix.r2.x << " " << activeCameraComponent->cameraViewMatrix.r2.y << " " << activeCameraComponent->cameraViewMatrix.r2.z << " " << activeCameraComponent->cameraViewMatrix.r2.w << "\n";
			std::cout << activeCameraComponent->cameraViewMatrix.r3.x << " " << activeCameraComponent->cameraViewMatrix.r3.y << " " << activeCameraComponent->cameraViewMatrix.r3.z << " " << activeCameraComponent->cameraViewMatrix.r3.w << "\n";
			std::cout << activeCameraComponent->cameraViewMatrix.r4.x << " " << activeCameraComponent->cameraViewMatrix.r4.y << " " << activeCameraComponent->cameraViewMatrix.r4.z << " " << activeCameraComponent->cameraViewMatrix.r4.w << "\n";*/


            // third parameter is the number of vertices to render. 
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glDrawArrays(tempEntities->getComponent<DrawableComponent>()->drawable_type, 0, verticesCount);
            


            /*it's gonna draw the
            currently bound buffer.
            and the arugument takes the
            starting position and number
            of verties. */

        }

    };

    int RenderSystem::handleEvent(EventInfo* _eventInfo)
    {
        Log::LogMessage("RenderSytem reacted to Window Close", LogLevel::INFO_LEVEL);
        //delete _eventInfo;
        return 0;
    };

    bool RenderSystem::initEntityBuffers(int _index)
    {
        GLuint tempVBO;
        GLuint tempVAO;

        glGenBuffers(1, &tempVBO);
        glGenVertexArrays(1, &tempVAO);

        VerticesComponent<float>* verticesComponent = entities[_index]->getComponent<VerticesComponent<float>>();

        //One position component component holds 3 floats
        const int VERTEX_BUFFER_SIZE = 3 * verticesComponent->vertices.size();

        float* vertexBuffer = new float[VERTEX_BUFFER_SIZE];

        int position = 0;

        for (PositionComponent<float> p : verticesComponent->vertices)
        {
            vertexBuffer[position++] = p.x;
            vertexBuffer[position++] = p.y;
            vertexBuffer[position++] = p.z;

        }


        VertexAttribComponent* vtb = entities[_index]->getComponent<VertexAttribComponent>();


        glBindVertexArray(tempVAO);
        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE * sizeof(float), vertexBuffer, GL_STATIC_DRAW);
        glVertexAttribPointer(
            vtb->shader_layout_index,
            vtb->count,
            vtb->type,
            vtb->normalized,
            vtb->stride,
            vtb->ptr
        );
        //  glBindVertexArray(0);
        //  glBindBuffer(GL_ARRAY_BUFFER,0);

        DrawableComponent* dc = entities[_index]->getComponent<DrawableComponent>();

        dc->VBO = tempVBO;
        dc->VAO = tempVAO;
        // delete vertexBuffer;
        return true;
    };
}