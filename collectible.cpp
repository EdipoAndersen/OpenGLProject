// Collectible.cpp
#include <C:/Users/edipo/Desktop/OpenGL/glad/include/glad/glad.h>
#include "Collectible.h"

Collectible::Collectible(float startX, float startY)
    : x(startX), y(startY), width(20.0f), height(20.0f), collected(false) {}

void Collectible::render() {
    if (!collected) {
        // Render the collectible as a yellow square (quad)
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for the collectible
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
}

bool Collectible::checkCollision(float playerX, float playerY, float playerWidth, float playerHeight) {
    // Check if the collectible intersects with the player (simple AABB collision detection)
    if (!collected && playerX < x + width && playerX + playerWidth > x &&
        playerY < y + height && playerY + playerHeight > y) {
        collected = true;
        return true;  // Return true if the player collects the item
    }
    return false;
}
