// Collectible.h
#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

class Collectible {
public:
    float x, y;
    float width, height;
    bool collected;

    Collectible(float startX, float startY);

    void render();
    bool checkCollision(float playerX, float playerY, float playerWidth, float playerHeight);
};

#endif
