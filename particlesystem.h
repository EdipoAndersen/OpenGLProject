#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"

class ParticleSystem {
public:
    std::vector<Particle> particles;

    ParticleSystem();

    void generate(float x, float y, int count);
    void update(float deltaTime);
    void render();
};

#endif
