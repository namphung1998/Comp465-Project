#include "App.h"

int main(int argc, char **argv) {
    
    // argc, argv need to be passed to the app so that MinVR can parse command
    // line args to see which config files to load.
	App app(argc, argv);

    

    // for (float x = 0.0; x < 20; x+=0.1) {
    //     for (float y = 0.0; y < 20; y+=0.1) {
    //         float noise = glm::perlin(glm::vec2(x, y));
    //         std::cout << noise << std::endl;
    //     }
    // }

    

    // Does not return until the program shuts down.
    app.run();

    return 0;
}
