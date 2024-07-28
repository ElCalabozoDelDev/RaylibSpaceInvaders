#include "spaceship.hpp"
#include <iostream>

Spaceship::Spaceship()
{
    texture = LoadTexture("resources/graphics/spaceship.png");
    position.x = (GetScreenWidth() - texture.width)/2;
    position.y = GetScreenHeight() - texture.height - 50;
    lastShootTime = 0.0;
}
Spaceship::~Spaceship()
{
    UnloadTexture(texture);
}

void Spaceship::Draw()
{
    DrawTextureV(texture, position, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= 5;
    if (position.x <= 0)
    {
        position.x = 0;
    }
}

void Spaceship::MoveRight()
{
    position.x += 5;
    if (position.x >= GetScreenWidth() - texture.width)
    {
        position.x = GetScreenWidth() - texture.width;
    }
}

void Spaceship::Shoot()
{
    if (GetTime() - lastShootTime >= 0.35)
    {
        lasers.push_back(Laser({position.x + texture.width/2 - 2, position.y}, 6));
        lastShootTime = GetTime();
    }
    
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - texture.width)/2;
    position.y = GetScreenHeight() - texture.height - 50;
    lasers.clear();
}

Rectangle Spaceship::GetCollisionRec()
{
    return {position.x, position.y, (float)texture.width, (float)texture.height};
}
