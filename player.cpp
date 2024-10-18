#include "Player.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include "RenderUtils.h"

Player::Player(float x, float y) {
    this->x = x;
    this->y = y;
    this->width = 1.0f;
    this->height = 1.0f;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
}

void Player::applyGravity(float deltaTime) {
    velocityY -= 9.81f * deltaTime;
}

void Player::move(float deltaTime, float floorY) {
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    // Parar no chão
    if (y < floorY + 0.5f) {
        y = floorY + 0.5f;
        velocityY = 0.0f;
    }
}

bool Player::isGrounded(float floorY) {
    return y <= floorY + 0.5f;
}

void Player::render() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);  // Posiciona o jogador
    glScalef(width, height, width);  // Escala o cubo para o tamanho do jogador
    glPopMatrix();
}