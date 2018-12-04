#ifndef Terrain_h
#define Terrain_h

#include <GLSLProgram.h>
#include <Texture.h>
#include <Mesh.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/noise.hpp>

class Terrain {
public:
    Terrain();
    ~Terrain(){};
    
    
    // Calculate and set up the buffers to render to screen
    void setupGeometry();
    
    // Draw the Earth to screen
    void draw(basicgraphics::GLSLProgram &shader);
    
protected:
    
    // Stores the earth texture data
    std::vector< std::shared_ptr<basicgraphics::Texture> > textures;
    std::vector<basicgraphics::Mesh::Vertex> cpuVertexArray;
    std::vector<int> cpuIndexArray;
    std::unique_ptr<basicgraphics::Mesh> mesh;
    
//    vec3 getPosition(int row, int rows, int col, int cols);
    
    
};

#endif
