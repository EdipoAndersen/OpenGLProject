#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    float x, y;
    float velocityX, velocityY;
    float life;  // Time to live

    Particle(float startX, float startY, float velX, float velY);

    void update(float deltaTime);
    void render();
    bool isAlive();
};

#endif
