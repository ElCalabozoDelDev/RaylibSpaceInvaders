#pragma once
#include <raylib.h>

class Laser
{
private:
    Vector2 position;
    int speed;
    bool active;
public:
    Laser(Vector2 pos, int speed) : 
        position(pos), 
        speed(speed),
        active(true) {};
    ~Laser() {}
    void Update();
    void Draw();
    bool IsActive() { return active; }
    Rectangle GetCollisionRec() { return {position.x, position.y, 4, 15}; }
    void Deactivate() { active = false; }
};
