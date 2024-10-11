#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include "Player.h"
#include "Collectible.h"
#include "ParticleSystem.h"
#include "Enemy.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const float FLOOR_Y = 100.0f;

void processInput(GLFWwindow* window, Player& player);
void setupProjection();
void renderFloor(float floorY);
void checkCollisions(Player& player, Collectible collectibles[], int collectibleCount, int& score, ParticleSystem& particleSystem, Enemy& enemy, int& lives);
void renderText(std::string text, float x, float y);

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D Platformer", nullptr, nullptr);
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

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    setupProjection();

    Player player(100.0f, FLOOR_Y + 50.0f);
    Collectible collectibles[3] = {
        Collectible(200.0f, FLOOR_Y + 50.0f),
        Collectible(400.0f, FLOOR_Y + 50.0f),
        Collectible(600.0f, FLOOR_Y + 50.0f)
    };

    // Inimigo que se move de um lado para o outro
    Enemy enemy(500.0f, FLOOR_Y + 10.0f, 100.0f);  // Velocidade de 100.0f

    int score = 0;
    int lives = 3;  // O jogador começa com 3 vidas
    ParticleSystem particleSystem;

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, player);

        player.applyGravity(deltaTime);
        player.move(deltaTime, FLOOR_Y);

        enemy.update(deltaTime, 200.0f, 600.0f);  // O inimigo se move entre x = 200 e x = 600

        checkCollisions(player, collectibles, 3, score, particleSystem, enemy, lives);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderFloor(FLOOR_Y);
        player.render();

        for (int i = 0; i < 3; ++i) {
            collectibles[i].render();
        }

        enemy.render();

        particleSystem.update(deltaTime);
        particleSystem.render();

        // Exibir vidas e score na tela
        std::stringstream ssLives;
        ssLives << "Lives: " << lives;
        renderText(ssLives.str(), 10.0f, WINDOW_HEIGHT - 40.0f);  // Vidas acima do score

        std::stringstream ssScore;
        ssScore << "Score: " << score;
        renderText(ssScore.str(), 10.0f, WINDOW_HEIGHT - 60.0f);  // Score

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Player& player) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        player.velocityX = -200.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        player.velocityX = 200.0f;
    }
    else {
        player.velocityX = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && player.isGrounded(FLOOR_Y)) {
        player.velocityY = 300.0f;
    }
}

void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void renderFloor(float floorY) {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.0f, floorY);
    glVertex2f(WINDOW_WIDTH, floorY);
    glVertex2f(WINDOW_WIDTH, floorY + 10.0f);
    glVertex2f(0.0f, floorY + 10.0f);
    glEnd();
}

void checkCollisions(Player& player, Collectible collectibles[], int collectibleCount, int& score, ParticleSystem& particleSystem, Enemy& enemy, int& lives) {
    for (int i = 0; i < collectibleCount; ++i) {
        if (collectibles[i].checkCollision(player.x, player.y, player.width, player.height)) {
            score += 1;
            particleSystem.generate(collectibles[i].x, collectibles[i].y, 10);
        }
    }

    // Verifica colisão com o inimigo
    if (enemy.checkCollision(player.x, player.y, player.width, player.height)) {
        if (lives > 0) {
            lives -= 1;  // O jogador perde 1 vida
        }
    }
}

void renderText(std::string text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}