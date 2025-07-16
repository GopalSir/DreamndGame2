#include "../include/System/RenderSystem.hpp"

namespace DREAM
{
    RenderSystem::RenderSystem(GLFWwindow* _glfwWindow)
    {
        if (_glfwWindow == nullptr)
        {
            Log::LogMessage("RenderSystem Error: glfw window parameter is nullptr", LogLevel::ERROR_LEVEL);
            exit(0);
        }
        else
        {
            Log::LogMessage("RenderSystem Info: glfw window ok", LogLevel::INFO_LEVEL);

        }
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


            // third parameter is the number of vertices to render. 
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0, verticesCount);


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