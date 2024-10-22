#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ShaderProgram.h"

// Globais para controlar a posi��o e a velocidade do cubo
glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);  // Posi��o do cubo
float cubeSpeed = 2.5f;  // Velocidade de movimento do cubo
float cubeVelocityY = 0.0f;  // Velocidade no eixo Y
float gravity = -9.8f;  // For�a da gravidade
bool isJumping = false;  // Verifica se o cubo est� no ar

// Fun��o para processar entrada do teclado
void processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cubePosition.z -= cubeSpeed * deltaTime;  // Move para frente
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cubePosition.z += cubeSpeed * deltaTime;  // Move para tr�s
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cubePosition.x -= cubeSpeed * deltaTime;  // Move para esquerda
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cubePosition.x += cubeSpeed * deltaTime;  // Move para direita
    }

    // Pulo
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !isJumping) {
        cubeVelocityY = 5.0f;  // Definir a for�a do pulo
        isJumping = true;
    }
}

// Fun��o para aplicar gravidade no cubo
void applyGravity(float deltaTime) {
    cubeVelocityY += gravity * deltaTime;
    cubePosition.y += cubeVelocityY * deltaTime;

    // Impedir que o cubo atravesse o ch�o
    float cubeBottomY = cubePosition.y - 0.5f;  // A parte inferior do cubo
    if (cubeBottomY < -0.5f) {  // Ajuste para o ch�o estar em -0.5 em vez de -1.0
        cubePosition.y = 0.0f;  // Ajustar a posi��o do cubo de forma que sua base fique sobre o ch�o
        cubeVelocityY = 0.0f;  // Zerar a velocidade quando atingir o ch�o
        isJumping = false;  // Permitir que o jogador pule novamente
    }
}

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

// V�rtices do ch�o
float floorVertices[] = {
    // Posi��es           // Cores
    -5.0f,  -1.0f, -5.0f,  1.5f, 0.5f, 1.5f,  // Cinza
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cubo com Gravidade e Camera", NULL, NULL);
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

    // Habilitar teste de profundidade
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

    // Proje��o e configura��o da c�mera
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    float lastFrame = 0.0f;

    // Loop principal de renderiza��o
    while (!glfwWindowShouldClose(window)) {
        // Calcular o tempo desde o �ltimo quadro
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Processar entrada de teclado
        processInput(window, deltaTime);
        applyGravity(deltaTime);  // Aplicar a gravidade ao cubo

        // Limpar a tela
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Atualizar a matriz de visualiza��o para seguir o cubo
        glm::vec3 cameraPosition = cubePosition + glm::vec3(0.0f, 2.0f, 8.0f);  // Ajustar a posi��o da c�mera
        glm::mat4 view = glm::lookAt(cameraPosition, cubePosition, glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setUniform("view", view);
        shader.setUniform("projection", projection);

        // Atualizar a matriz de modelo para o cubo girar e se mover
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePosition);  // Aplicar a posi��o do cubo
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
