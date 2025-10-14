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
            PhysicsComponent* physicsComponent = tempEntities->getComponent<PhysicsComponent>();

            

            int verticesCount = tempEntities->getComponent<VerticesComponent<float>>()->vertices.size();
            //glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
            glBindVertexArray(tempVAO);

            Mat4<float> model_matrix = Mat4<float>::identity;


            //We can derive model matrix via PhysicsComponent of this entity
            if (physicsComponent )
            {
                model_matrix = PhysicsSystem::GetModelMatrixfromComponent(physicsComponent);
               /* std::cout << "MM: " << model_matrix.r1.x << " " << model_matrix.r1.y << " " << model_matrix.r1.z << " " << model_matrix.r1.w << "\n";
                std::cout << "R2: " << model_matrix.r2.x << " " << model_matrix.r2.y << " " << model_matrix.r2.z << " " << model_matrix.r2.w << "\n";
                std::cout << "R3: " << model_matrix.r3.x << " " << model_matrix.r3.y << " " << model_matrix.r3.z << " " << model_matrix.r3.w << "\n";
                std::cout << "R4: " << model_matrix.r4.x << " " << model_matrix.r4.y << " " << model_matrix.r4.z << " " << model_matrix.r4.w << "\n";*/
            }
            Mat4<float> tempMVP = CalculateMVP(activeCameraComponent->projection, activeCameraComponent->cameraViewMatrix,model_matrix);
            shader->setUniform("mvp", tempMVP);
            

           // Logging MVP
     /*       std::cout << tempMVP.r1.x << " " << tempMVP.r1.y << " " << tempMVP.r1.z << " " << tempMVP.r1.w << "\n";
            std::cout << tempMVP.r2.x << " " << tempMVP.r2.y << " " << tempMVP.r2.z << " " << tempMVP.r2.w << "\n";
            std::cout << tempMVP.r3.x << " " << tempMVP.r3.y << " " << tempMVP.r3.z << " " << tempMVP.r3.w << "\n";
            std::cout << tempMVP.r4.x << " " << tempMVP.r4.y << " " << tempMVP.r4.z << " " << tempMVP.r4.w << "\n";*/

           // Logging Projection matrix
			//std::cout << activeCameraComponent->projection.r1.x << " " << activeCameraComponent->projection.r1.y << " " << activeCameraComponent->projection.r1.z << " " << activeCameraComponent->projection.r1.w << "\n";
			//std::cout << activeCameraComponent->projection.r2.x << " " << activeCameraComponent->projection.r2.y << " " << activeCameraComponent->projection.r2.z << " " << activeCameraComponent->projection.r2.w << "\n";
			//std::cout << activeCameraComponent->projection.r3.x << " " << activeCameraComponent->projection.r3.y << " " << activeCameraComponent->projection.r3.z << " " << activeCameraComponent->projection.r3.w << "\n";
			//std::cout << activeCameraComponent->projection.r4.x << " " << activeCameraComponent->projection.r4.y << " " << activeCameraComponent->projection.r4.z << " " << activeCameraComponent->projection.r4.w << "\n";

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
        const int VERTEX_BUFFER_SIZE = 3 * verticesComponent->vertices.size() + 4*verticesComponent->vertices_color.size();

        

        float* vertexBuffer = new float[VERTEX_BUFFER_SIZE];

        int position = 0;
        int index = 0;

        //for (PositionComponent<float> p : verticesComponent->vertices)
        //{
        //    vertexBuffer[position++] = p.x;
        //    vertexBuffer[position++] = p.y;
        //    vertexBuffer[position++] = p.z;

        //    

        //}


        for (int index = 0; index < verticesComponent->vertices.size(); ++index)
        {
            vertexBuffer[position++] = verticesComponent->vertices[index].x;
            vertexBuffer[position++] = verticesComponent->vertices[index].y;
            vertexBuffer[position++] = verticesComponent->vertices[index].z;

            vertexBuffer[position++] = verticesComponent->vertices_color[index].r;
            vertexBuffer[position++] = verticesComponent->vertices_color[index].g;
            vertexBuffer[position++] = verticesComponent->vertices_color[index].b;
            vertexBuffer[position++] = verticesComponent->vertices_color[index].a;


        }


        glBindVertexArray(tempVAO);
        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE * sizeof(float), vertexBuffer, GL_STATIC_DRAW);

        for (auto* vatp : verticesComponent->vertexAttributePointers)
        {
          
            glVertexAttribPointer(
                vatp->shader_layout_index,
                vatp->count,
                vatp->type,
                vatp->normalized,
                vatp->stride,
                vatp->ptr
            );

            glEnableVertexAttribArray(vatp->shader_layout_index);
        }



        //  glBindVertexArray(0);
        //  glBindBuffer(GL_ARRAY_BUFFER,0);

        DrawableComponent* dc = entities[_index]->getComponent<DrawableComponent>();

        dc->VBO = tempVBO;
        dc->VAO = tempVAO;
        // delete vertexBuffer;
        return true;
    }
    void RenderSystem::disableEntity(int _index)
    {
        Entity* tempEntity = entities[_index];
        
        Entity::disableEntity(tempEntity);
    }
    void RenderSystem::deleteEntity(int _index)
    {
        delete entities[_index];
    }
    Vec4<float> RenderSystem::ScreenToWorldCoordinate(Vec4<float> _screenCoord, CameraComponent* _cameraComponent)
    {
        //First we will convert screen coords to NDC, for that we need viewport coords too.
        int view_port[4];
        glGetIntegerv(GL_VIEWPORT, view_port);

        float view_port_width = (float)(view_port[2]);
        float view_port_height = (float)(view_port[3]);

        //Now converting them to NDC
        float x_ndc = 2 * _screenCoord.x / view_port_width - 1;
        float y_ndc = 1 - (2 * _screenCoord.y / view_port_height);
        float z_ndc = 0.7f;

        Vec4<float> ndc_point(x_ndc, y_ndc, z_ndc, 1);

        Mat4<float> pv = _cameraComponent->projection * _cameraComponent->cameraViewMatrix;

        Mat4<float> inverse_of_projection_view = pv.inverse();


        Vec4<float> result;
        result = inverse_of_projection_view * ndc_point;

        if (std::abs(result.w) > 1e-6) {
            result.x /= result.w;
            result.y /= result.w;
            result.z /= result.w;
            result.w = 1.0f;
        }

        return result;
    };

    //This function will take in screen coordinates, and based on window size return NDC
    Vec4<float> RenderSystem::ScreenToNDC(Vec4<float> _screenCoord)
    {
        int view_port[4];
        glGetIntegerv(GL_VIEWPORT, view_port);

        float view_port_width = (float)(view_port[2]);
        float view_port_height = (float)(view_port[3]);

        //Now converting them to NDC
        float x_ndc = 2 * _screenCoord.x / view_port_width - 1;
        float y_ndc = 1 - (2 * _screenCoord.y / view_port_height);
        float z_ndc = -1.0f;

        Vec4<float> ndc_point(x_ndc, y_ndc, z_ndc, 1);
        
        return ndc_point;


    }
    
   
}