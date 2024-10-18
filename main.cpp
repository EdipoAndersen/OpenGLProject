#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ShaderProgram.h"

// V�rtices do cubo e suas cores
float vertices[] = {
    // Posi��es           // Cores
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  // Vermelho
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  // Verde
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,  // Azul
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  // Amarelo

    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,  // Magenta
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,  // Ciano
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // Branco
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f   // Preto
};

// �ndices do cubo para o buffer de elementos
unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,  // Face de tr�s
    4, 5, 6, 6, 7, 4,  // Face da frente
    0, 4, 7, 7, 3, 0,  // Face esquerda
    1, 5, 6, 6, 2, 1,  // Face direita
    3, 7, 6, 6, 2, 3,  // Face de cima
    0, 1, 5, 5, 4, 0   // Face de baixo
};

// V�rtices do ch�o (ch�o agora posicionado um pouco mais abaixo)
float floorVertices[] = {
    // Posi��es           // Cores
    -5.0f,  -1.0f, -5.0f,  0.5f, 0.5f, 0.5f,  // Cinza
     5.0f,  -1.0f, -5.0f,  0.5f, 0.5f, 0.5f,
     5.0f,  -1.0f,  5.0f,  0.5f, 0.5f, 0.5f,
    -5.0f,  -1.0f,  5.0f,  0.5f, 0.5f, 0.5f
};

// �ndices para o ch�o
unsigned int floorIndices[] = {
    0, 1, 2,
    2, 3, 0
};

int main() {
    // Inicializar GLFW e OpenGL
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cubo Colorido", NULL, NULL);
    if (!window) {
        std::cerr << "Falha ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    // Habilitar teste de profundidade para renderiza��o 3D
    glEnable(GL_DEPTH_TEST);

    // Criar e compilar shaders
    ShaderProgram shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader.use();

    // Configura��o dos buffers para o cubo
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributos de posi��o do cubo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atributos de cor do cubo
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Configura��o dos buffers para o ch�o
    unsigned int floorVAO, floorVBO, floorEBO;
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);
    glGenBuffers(1, &floorEBO);

    glBindVertexArray(floorVAO);

    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);

    // Atributos de posi��o para o ch�o
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atributos de cor para o ch�o
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Matrizes de visualiza��o e proje��o para transformar o cubo e o ch�o
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -8.0f));  // Mover a c�mera mais para tr�s
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Passar as matrizes de visualiza��o e proje��o para o shader
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);

    // Loop principal de renderiza��o
    while (!glfwWindowShouldClose(window)) {
        // Processar input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Limpar a tela
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Atualizar a matriz de modelo para o cubo girar
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));  // Rota��o do cubo

        // Passar a matriz de modelo para o shader do cubo
        shader.setUniform("model", model);

        // Renderizar o cubo
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Desenhar o ch�o
        glm::mat4 floorModel = glm::mat4(1.0f);  // O ch�o n�o rotaciona
        shader.setUniform("model", floorModel);  // Usar uma matriz de modelo diferente para o ch�o

        glBindVertexArray(floorVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // Desenhar o ch�o

        // Trocar buffers e lidar com eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteBuffers(1, &floorVBO);
    glDeleteBuffers(1, &floorEBO);

    glfwTerminate();
    return 0;
}