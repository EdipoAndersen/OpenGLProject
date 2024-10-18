#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float x, y;
    float width, height;
    float velocityX, velocityY;

    Player(float x, float y);
    void applyGravity(float deltaTime);
    void move(float deltaTime, float floorY);
    bool isGrounded(float floorY);
    void render();
};

#endif
