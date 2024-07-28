#pragma once
#include <raylib.h>

class MysteryShip
{
private:
    Vector2 position;
    Texture2D texture;
    int speed;
    bool active;
public:
    MysteryShip(/* args */);
    ~MysteryShip();
    void Draw();
    void Update();
    void Spawn();
    Rectangle GetCollisionRec();
    void Deactivate() { active = false; }
};
