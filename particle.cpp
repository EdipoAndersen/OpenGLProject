#include <glad/glad.h>
#include "Particle.h"

Particle::Particle(float startX, float startY, float velX, float velY)
    : x(startX), y(startY), velocityX(velX), velocityY(velY), life(1.0f) {}

void Particle::update(float deltaTime) {
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
    life -= deltaTime;  // Particle fades over time
}

void Particle::render() {
    if (isAlive()) {
        glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, life);  // Fades as life decreases
        glVertex2f(x - 2.0f, y - 2.0f);
        glVertex2f(x + 2.0f, y - 2.0f);
        glVertex2f(x + 2.0f, y + 2.0f);
        glVertex2f(x - 2.0f, y + 2.0f);
        glEnd();
    }
}

bool Particle::isAlive() {
    return life > 0.0f;
}
