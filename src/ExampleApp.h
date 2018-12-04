#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include <api/MinVR.h>
using namespace MinVR;
#include "Terrain.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#ifdef _WIN32
#include "GL/glew.h"
#include "GL/wglew.h"
#elif (!defined(__APPLE__))
#include "GL/glxew.h"
#endif

// OpenGL Headers
#if defined(WIN32)
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#elif defined(__APPLE__)
#define GL_GLEXT_PROTOTYPES
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#include <BasicGraphics.h>
using namespace basicgraphics;

class ExampleApp : public VRApp {
public:
    
    /** The constructor passes argc, argv, and a MinVR config file on to VRApp.
     */
	ExampleApp(int argc, char** argv);
    virtual ~ExampleApp();

    
    /** USER INTERFACE CALLBACKS **/
    virtual void onAnalogChange(const VRAnalogEvent &state);
    virtual void onButtonDown(const VRButtonEvent &state);
    virtual void onButtonUp(const VRButtonEvent &state);
	virtual void onCursorMove(const VRCursorEvent &state);
    virtual void onTrackerMove(const VRTrackerEvent &state);
    
    
    /** RENDERING CALLBACKS **/
    virtual void onRenderGraphicsScene(const VRGraphicsState& state);
    virtual void onRenderGraphicsContext(const VRGraphicsState& state);
    
    
private:

	std::unique_ptr<Box> _box;
	float _flying;
    bool paused;

	double _lastTime;
	double _curFrameTime;

	virtual void reloadShaders();
	GLSLProgram _shader;
    GLSLProgram _normalShader;
    
    void setupGeometry();
    
    glm::mat4 viewportMat;

	void initializeText();
	void drawText(const std::string text, float xPos, float yPos, GLfloat windowHeight, GLfloat windowWidth);
	struct FONScontext* fs;
	GLSLProgram _textShader;
    std::shared_ptr<Terrain> terrain;
    
    
protected:
    
    std::vector< std::shared_ptr<basicgraphics::Texture> > textures;
    std::vector<basicgraphics::Mesh::Vertex> cpuVertexArray;
    std::vector<int> cpuIndexArray;
    std::unique_ptr<basicgraphics::Mesh> mesh;

    shared_ptr<Texture> tex;
    
    
};




#endif //EXAMPLEAPP_H
