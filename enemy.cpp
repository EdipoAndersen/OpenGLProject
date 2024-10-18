#include <glad/glad.h>
#include "Enemy.h"

Enemy::Enemy(float startX, float startY, float velX)
    : x(startX), y(startY), width(40.0f), height(40.0f), velocityX(velX) {}

void Enemy::update(float deltaTime, float minX, float maxX) {
    x += velocityX * deltaTime;
    if (x < minX || x + width > maxX) {
        velocityX = -velocityX;
    }
}

void Enemy::render() {
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(x, y, 0.0f);
    glVertex3f(x + width, y, 0.0f);
    glVertex3f(x + width, y + height, 0.0f);
    glVertex3f(x, y + height, 0.0f);
    glEnd();
}

bool Enemy::checkCollision(float playerX, float playerY, float playerWidth, float playerHeight) {
    return (playerX < x + width && playerX + playerWidth > x &&
        playerY < y + height && playerY + playerHeight > y);
}
