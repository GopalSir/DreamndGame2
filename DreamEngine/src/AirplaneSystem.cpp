// #include "../headers/System/AirplaneSystem.hpp"

// AirplaneSystem::AirplaneSystem() {}

// AirplaneSystem::~AirplaneSystem() {}

// Entity* AirplaneSystem::createAirplaneEntity() {
//     Entity* airplane = new Entity();
    
//     // Generate vertices for airplane shape using pixel coordinates
//     // Each three vertices define a triangle in CCW order
//     // Create a vector of PositionComponent<float> pointers for the airplane vertices
//     std::vector<PositionComponent<float>*> airplaneVertices;
    
//     // Function to add a vertex to the vector
//     auto addVertex = [&airplaneVertices](float x, float y, float z) {
//         PositionComponent<float>* pos = new PositionComponent<float>();
//         pos->x = x;
//         pos->y = y;
//         pos->z = z;
//         airplaneVertices.push_back(pos);
//     };

//     // Fuselage (center body)
//     addVertex(500, 300, 0);  // Center-top
//     addVertex(450, 600, 0);  // Bottom-left
//     addVertex(550, 600, 0);  // Bottom-right
    
//     float* vertices = {
//         // Fuselage (center body)
//         500, 300, 0,  // Center-top
//         450, 600, 0,  // Bottom-left
//         550, 600, 0,  // Bottom-right
        
//         // Nose
//         500, 200, 0,  // Tip
//         470, 300, 0,  // Left
//         530, 300, 0,  // Right
        
//         // Left wing
//         200, 350, 0,  // Left wing tip
//         470, 350, 0,  // Wing root front
//         470, 400, 0,  // Wing root back
        
//         200, 350, 0,  // Left wing tip (repeated)
//         470, 400, 0,  // Wing root back (repeated)
//         300, 420, 0,  // Wing back edge
        
//         // Right wing
//         800, 350, 0,  // Right wing tip
//         530, 350, 0,  // Wing root front
//         530, 400, 0,  // Wing root back
        
//         800, 350, 0,  // Right wing tip (repeated)
//         530, 400, 0,  // Wing root back (repeated)
//         700, 420, 0,  // Wing back edge
        
//         // Tail wings - horizontal stabilizers
//         350, 550, 0,  // Left stabilizer tip
//         470, 550, 0,  // Left stabilizer root
//         470, 590, 0,  // Tail back
        
//         650, 550, 0,  // Right stabilizer tip
//         530, 550, 0,  // Right stabilizer root
//         530, 590, 0,  // Tail back
        
//         // Vertical stabilizer
//         500, 500, 0,  // Top point
//         480, 590, 0,  // Left base
//         520, 590, 0   // Right base
//     };
    
//     // Add vertex component with generated vertices (no indices)
//     auto* vertexComp = new VerticesComponent<float>();
//     vertexComp->vertices = vertices;
//     airplane->addComponent(vertexComp);
    
//     // Add vertex attribute component for positions
//     auto* vertexAttribComp = VertexAttribPointerGenerator::generateVertexAttribPoinnter(
//         VertexAttribPointerGenerator::STYLE::DEFAULT
//     );
//     airplane->addComponent(vertexAttribComp);
    
//     // Add drawable component using GL_TRIANGLES mode
//     auto* drawableComp = new DrawableComponent();
//     airplane->addComponent(drawableComp);
    
//     return airplane;
// }