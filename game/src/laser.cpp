#include "laser.hpp"

void Laser::Update()
{
    position.y -= speed;
    if (active && (position.y < 0 || position.y > GetScreenHeight()))
    {
        active = false;
    }
    
}

void Laser::Draw()
{
    if (active)
    {
        DrawRectangleV(position, {4, 15}, {243, 216, 63, 255});
    }
    
}