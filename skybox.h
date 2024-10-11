#ifndef SKYBOX_H
#define SKYBOX_H

#include <C:\Users\edipo\Desktop\OpenGL\glad\include\glad\glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Skybox {
public:
    Skybox();
    unsigned int loadCubemap(std::vector<std::string> faces);
    void render(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int skyboxVAO, skyboxVBO, cubemapTexture;
};

#endif
