#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float x, y;
    float width, height;
    float velocityX, velocityY;

    Player(float startX, float startY);

    void move(float deltaTime, float floorY);
    void applyGravity(float deltaTime);
    void render();
    bool isGrounded(float floorY);  // Now takes the floor's Y position into account
};

#endif
