#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Lighting {
public:
    glm::vec3 lightPos;

    Lighting(glm::vec3 position) : lightPos(position) {}

    glm::vec3 GetLightPosition() {
        return lightPos;
    }

    void SetLightUniforms(unsigned int shaderProgram) {
        glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);  // Luz branca
    }
};

#endif