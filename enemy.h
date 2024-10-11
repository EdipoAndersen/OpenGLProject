#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    float x, y;
    float width, height;
    float velocityX;

    Enemy(float startX, float startY, float velX);

    void update(float deltaTime, float minX, float maxX);
    void render();
    bool checkCollision(float playerX, float playerY, float playerWidth, float playerHeight);
};

#endif
