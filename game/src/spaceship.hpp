#pragma once
#include <raylib.h>
#include <laser.hpp>
#include <vector>

class Spaceship
{
private:
    Texture2D texture;
    Vector2 position;
    double lastShootTime;
public:
    Spaceship(/* args */);
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void Shoot();
    void Reset();
    Rectangle GetCollisionRec();
    std::vector<Laser> lasers;
};