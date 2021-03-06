#include "Terrain.h"
#include <string>

using namespace std;
using namespace glm;
using namespace basicgraphics;

Terrain::Terrain(float flying) {

    _flying = flying;

    // shared_ptr<Texture> tex = Texture::create2DTextureFromFile("sand2.jpg");
    // tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // textures.push_back(tex);
    
	setupGeometry(0);
//    setupGeometry(1);

    const int numVertices = cpuVertexArray.size();
    const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();

    mesh.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW,cpuVertexByteSize * 2, cpuIndexByteSize * 2, 0, cpuVertexArray,cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));

    mesh->setMaterialColor(vec4(0.929, 0.788, 0.686,1));
}

void Terrain::setupGeometry(int offset) {
    const int rows = 200;
    const int cols = 70;
    
    Mesh::Vertex vert;
    
    float newX = _flying;
    for(int x = 0; x < rows; x++) {
        float newY = 0.0;
        for(int y = 0; y < cols; y++) {
            if(x == 0 || x == rows-1 || y == 0 || y == cols-1) {
                terrain.push_back(0.0);
            } else {

                terrain.push_back(4 * perlin(vec2(newX, newY)));
                newY += 0.115f;
            }
        }
        newX += 0.115f;
    }
    
    for (int row = 0; row < rows - 1; row++) {


        
        int newRow = offset * rows + row;



        for (int col = 0; col <= cols; col++) {
            vert.position = vec3(col - cols/2.0, terrain[(row) * cols + col] , newRow - rows/2.0);
            
            if(row == 0 || row == rows-1 || col == 0 || col == cols-1) {
                vert.normal = vec3(0, -1, 0);
            } else {
                vec3 a = vec3(2, terrain[row * cols + col + 1] - terrain[row * cols + col - 1], 0);
                vec3 b = vec3(0, terrain[(row - 1) * cols + col] - terrain[(row + 1) * cols + col], 2);

                vert.normal = normalize(cross(a, b));
            }
            // vert.texCoord0 = vec2( (float) col/cols, ((float)(row + _flying) /rows) % 1.0 );

            // vert.texCoord0 = vec2( (float) col / cols, fmod(((float)(row + _flying) / rows ), 1.0 ));

            vert.texCoord0 = vec2(col/cols, row/rows);

            cpuVertexArray.push_back(vert);
            cpuIndexArray.push_back(2 * ((cols + 1) * newRow + col));
            
            vert.position = vec3(col - cols/2.0, terrain[(row+1) * cols + col] , newRow - rows/2.0 + 1);
            
            if(row + 1 == rows - 1 || col == 0 || col == cols - 1) {
                vert.normal = vec3(0, -1, 0);
            } else {
                vec3 a = vec3(2, terrain[(row + 1) * cols + col + 1] - terrain[(row + 1) * cols + col - 1], 0);
                vec3 b = vec3(0, terrain[(row) * cols + col] - terrain[(row + 2) * cols + col], 2);

                vert.normal = normalize(cross(a, b));
            }

            // vert.texCoord0 = vec2(( (float)col/cols, ((float)(row+1 + _flying)/rows))% 1.0 );

            // vert.texCoord0 = vec2( (float) col / cols, fmod(((float)(row + _flying + 1) / rows ), 1.0 ));

            vert.texCoord0 = vec2(col/cols, (row + 1)/rows);
            cpuVertexArray.push_back(vert);
            cpuIndexArray.push_back(2 * ((cols + 1) * newRow + col) + 1);
        }
    }
}

void Terrain::updateGeometry() {
    terrain.clear();

    setupGeometry(1);

    const int numVertices = cpuVertexArray.size();
    const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
    const int filledVertexByteSize = mesh->getFilledVertexByteSize();
    const int filledIndexByteSize = mesh->getFilledIndexByteSize();
    // if (cpuVertexByteSize > filledVertexByteSize) {
        // Just upload the new data
    const int vertexOffset = (float)filledVertexByteSize / (float)sizeof(Mesh::Vertex);
    const int newVertexDataByteSize = cpuVertexByteSize - filledVertexByteSize;
    const int newIndexDataByteSize = cpuIndexByteSize - filledIndexByteSize;
    mesh->updateVertexData(filledVertexByteSize, vertexOffset, cpuVertexArray);
    mesh->updateIndexData(cpuIndexArray.size() * 2, filledIndexByteSize, newIndexDataByteSize, &cpuIndexArray[0]+vertexOffset);


}

void Terrain::draw(GLSLProgram &shader) {
	
    mesh->draw(shader);
}
