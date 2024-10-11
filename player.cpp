#include <C:/Users/edipo/Desktop/OpenGL/glad/include/glad/glad.h>
#include "Player.h"

const float GRAVITY = -500.0f;  // Gravity pulls down (negative Y direction)

Player::Player(float startX, float startY)
    : x(startX), y(startY), width(50.0f), height(50.0f), velocityX(0.0f), velocityY(0.0f) {}

void Player::move(float deltaTime, float floorY) {
    // Move player horizontally
    x += velocityX * deltaTime;

    // Move player vertically
    y += velocityY * deltaTime;

    // Prevent player from falling through the floor
    if (y <= floorY) {
        y = floorY;          // Stop the player at the top of the floor
        velocityY = 0.0f;    // Reset vertical velocity when hitting the floor
    }
}

void Player::applyGravity(float deltaTime) {
    // Apply gravity to the player
    velocityY += GRAVITY * deltaTime;  // Gravity pulls down
}

bool Player::isGrounded(float floorY) {
    // Check if the player is on the floor
    return (y <= floorY);
}

void Player::render() {
    // Render the player as a simple rectangle (quad)
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the player
    glVertex2f(x, y);             // Bottom-left corner
    glVertex2f(x + width, y);     // Bottom-right corner
    glVertex2f(x + width, y + height);  // Top-right corner
    glVertex2f(x, y + height);         // Top-left corner
    glEnd();
}