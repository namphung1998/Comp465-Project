#include "Terrain.h"
#include <string>

using namespace std;
using namespace glm;
using namespace basicgraphics;

Terrain::Terrain() {

    shared_ptr<Texture> tex = Texture::create2DTextureFromFile("lightingToon.jpg");
    tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
	setupGeometry();

    const int numVertices = cpuVertexArray.size();
    const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();

    mesh.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW,cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray,cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));

//    mesh->setMaterialColor(vec4(0,1,0,1));
}

void Terrain::setupGeometry() {
    const int rows = 30;
    const int cols = 30;
    
    Mesh::Vertex vert;

    float terrain[rows][cols];
    
    float newX = 0.0;
    for(int x = 0; x < rows; x++) {
        float newY = 0.0;
        for(int y = 0; y < cols; y++) {
            if(x == 0 || x == rows-1 || y == 0 || y == cols-1) {
                terrain[x][y] = 0;
            } else {
                terrain[x][y] = 4 * perlin(vec2(newX, newY));
                newY += 0.115f;
            }
        }
        newX += 0.115f;
    }
    
    for (int row = 0; row < rows - 1; row++) {
        for (int col = 0; col <= cols; col++) {
            vert.position = vec3(col - cols/2, terrain[row][col] , row - rows/2);
            // vert.position = vec3(col - cols/2, 0, row - rows/2);
            
            if(row == 0 || row == rows-1 || col == 0 || col == cols-1) {
                vert.normal = vec3(0, -1, 0);
            } else {
                vec3 a = vec3(col - cols/2, terrain[row-1][col], row - 1 - rows/2);
                vec3 b = vec3(col + 1 - cols/2, terrain[row-1][col + 1], row - 1 - rows/2);
                vec3 c = vec3(col - 1 - cols/2, terrain[row][col - 1], row - rows/2);
                vec3 d = vec3(col + 1 - cols/2, terrain[row][col + 1], row - rows/2);
                vec3 e = vec3(col - 1 - cols/2, terrain[row + 1][col - 1], row + 1 - rows/2);
                vec3 f = vec3(col - cols/2, terrain[row + 1][col], row + 1 - rows/2);
                
                vec3 ba = normalize(cross(a - vert.position, b - vert.position));
                vec3 ac = normalize(cross(c - vert.position, a - vert.position));
                vec3 ce = normalize(cross(e - vert.position, c - vert.position));
                vec3 ef = normalize(cross(f - vert.position, e - vert.position));
                vec3 fd = normalize(cross(d - vert.position, f - vert.position));
                vec3 db = normalize(cross(b - vert.position, d - vert.position));
                
                vert.normal = normalize(ba + ac + ce + ef + fd + db);
            }
            vert.texCoord0 = vec2(0, 0);
            cpuVertexArray.push_back(vert);
            cpuIndexArray.push_back(2 * ((cols + 1) * row + col));
            
            vert.position = vec3(col - cols/2, terrain[row + 1][col] , row - rows/2 + 1);
            
            if(row + 1 == rows - 1 || col == 0 || col == cols - 1) {
                vert.normal = vec3(0, -1, 0);
            } else {
                vec3 a = vec3(col - cols/2, terrain[row][col], row - rows/2);
                vec3 b = vec3(col + 1 - cols/2, terrain[row][col + 1], row - rows/2);
                vec3 c = vec3(col - 1 - cols/2, terrain[row + 1][col - 1], row + 1 - rows/2);
                vec3 d = vec3(col + 1 - cols/2, terrain[row + 1][col + 1], row + 1 - rows/2);
                vec3 e = vec3(col - 1 - cols/2, terrain[row + 2][col - 1], row + 2 - rows/2);
                vec3 f = vec3(col - cols/2, terrain[row + 2][col], row + 2 - rows/2);
                
                vec3 ba = normalize(cross(a - vert.position, b - vert.position));
                vec3 ac = normalize(cross(c - vert.position, a - vert.position));
                vec3 ce = normalize(cross(e - vert.position, c - vert.position));
                vec3 ef = normalize(cross(f - vert.position, e - vert.position));
                vec3 fd = normalize(cross(d - vert.position, f - vert.position));
                vec3 db = normalize(cross(b - vert.position, d - vert.position));
                
                vert.normal = normalize(ba + ac + ce + ef + fd + db);
            }
            
            
            
            
            // vert.position = vec3(col - cols/2, 0, row - rows/2 + 1);
            vert.normal = vec3(0, 1, 0);
            vert.texCoord0 = vec2(0, 0);
            cpuVertexArray.push_back(vert);
            cpuIndexArray.push_back(2 * ((cols + 1) * row + col) + 1);
        }
    }
}
//
//vec3 Terrain::getPosition(int row, int rows, int col, int cols) {
//    return vec3(col - cols/2, terrain[row][col], row - rows/2);
//}

void Terrain::draw(GLSLProgram &shader) {
	
    mesh->draw(shader);
}
