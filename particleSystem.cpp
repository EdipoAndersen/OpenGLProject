#include "ParticleSystem.h"
#include <cstdlib>

ParticleSystem::ParticleSystem() {}

void ParticleSystem::generate(float x, float y, int count) {
    for (int i = 0; i < count; ++i) {
        float velX = (rand() % 100 - 50) / 10.0f;
        float velY = (rand() % 100 - 50) / 10.0f;
        particles.push_back(Particle(x, y, velX, velY));
    }
}

void ParticleSystem::update(float deltaTime) {
    for (auto& particle : particles) {
        particle.update(deltaTime);
    }
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](Particle& p) { return !p.isAlive(); }),
        particles.end());
}

void ParticleSystem::render() {
    for (auto& particle : particles) {
        particle.render();
    }
}
