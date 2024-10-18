#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ShaderProgram.h"

// Cube vertices and colors
float vertices[] = {
    // Positions           // Colors
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  // Red
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  // Green
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,  // Blue
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  // Yellow

    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,  // Magenta
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,  // Cyan
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // White
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f   // Black
};

// Cube indices for element buffer
unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,  // Back face
    4, 5, 6, 6, 7, 4,  // Front face
    0, 4, 7, 7, 3, 0,  // Left face
    1, 5, 6, 6, 2, 1,  // Right face
    3, 7, 6, 6, 2, 3,  // Top face
    0, 1, 5, 5, 4, 0   // Bottom face
};

int main() {
    // Initialize GLFW and OpenGL
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Colored Cube", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Create and compile shaders
    ShaderProgram shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader.use();

    // Set up vertex buffer object (VBO), vertex array object (VAO), and element buffer object (EBO)
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind VBO, EBO, and buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // View and Projection matrices for transforming the cube
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));  // Move the camera back
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Pass the matrices to the shader
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the model matrix to rotate the cube over time
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));  // Rotate the cube over time

        // Pass the updated model matrix to the shader
        shader.setUniform("model", model);

        // Render the cube
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
