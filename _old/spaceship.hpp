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
    Sound shootSound;
    std::vector<Laser> lasers;
public:
    Spaceship(/* args */);
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void Shoot();
    void Reset();
    Rectangle GetCollisionRec();
    std::vector<Laser>& GetLasers() { return lasers; }
    std::vector<Laser>::iterator LasersBegin() { return lasers.begin(); }
    std::vector<Laser>::iterator LasersEnd() { return lasers.end(); }
    std::vector<Laser>::iterator EraseLaser(std::vector<Laser>::iterator it) { return lasers.erase(it); }
};