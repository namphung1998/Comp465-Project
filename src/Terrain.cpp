#include "Terrain.h"
#include <string>

using namespace std;
using namespace glm;
using namespace basicgraphics;

Terrain::Terrain() {
	setupGeometry();

    const int numVertices = cpuVertexArray.size();
    const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();

    mesh.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW,cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray,cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));

    mesh->setMaterialColor(vec4(0,1,0,1));
}

void Terrain::setupGeometry() {
    const int rows = 300;
    const int cols = 50;
    
    Mesh::Vertex vert;
    
    float terrain[rows][cols];
    
    float newX = 0.0;
    for(int x = 0; x < rows; x++) {
        float newY = 0.0;
        for(int y = 0; y < cols; y++) {
            
            terrain[x][y] = 4 * perlin(vec2(newX, newY));
            // cout << terrain[x][y] << endl;
            newY += 0.115f;
            
        }
        newX += 0.115f;
    }
    
    for (int row = 0; row < rows - 1; row++) {
        for (int col = 0; col <= cols; col++) {
            vert.position = vec3(col - cols/2, terrain[row][col], row - rows/2);
            vert.normal = vec3(0, 1, 0);
            vert.texCoord0 = vec2(0, 0);
            cpuVertexArray.push_back(vert);
            cpuIndexArray.push_back(2 * ((cols + 1) * row + col));
            
            vert.position = vec3(col - cols/2, terrain[row + 1][col], row - rows/2 + 1);
            vert.normal = vec3(0, 1, 0);
            vert.texCoord0 = vec2(0, 0);
            cpuVertexArray.push_back(vert);
            cpuIndexArray.push_back(2 * ((cols + 1) * row + col) + 1);
        }
    }
}

void Terrain::draw(GLSLProgram &shader) {
	
    mesh->draw(shader);
}
