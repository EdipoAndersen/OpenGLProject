#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    GLuint ID;

    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    void use();
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);
};

#endif
