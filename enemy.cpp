#include <glad/glad.h>
#include "Enemy.h"

Enemy::Enemy(float startX, float startY, float velX)
    : x(startX), y(startY), width(40.0f), height(40.0f), velocityX(velX) {}

void Enemy::update(float deltaTime, float minX, float maxX) {
    x += velocityX * deltaTime;

    // Se o inimigo atingir as bordas, inverta a direção
    if (x < minX || x + width > maxX) {
        velocityX = -velocityX;
    }
}

void Enemy::render() {
    // Renderiza o inimigo como um quadrado laranja
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);  // Cor laranja
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

bool Enemy::checkCollision(float playerX, float playerY, float playerWidth, float playerHeight) {
    // Colisão simples AABB (Axis-Aligned Bounding Box)
    return (playerX < x + width && playerX + playerWidth > x &&
        playerY < y + height && playerY + playerHeight > y);
}
