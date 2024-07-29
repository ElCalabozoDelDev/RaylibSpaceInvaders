#include "spaceship.hpp"
#include <iostream>

Spaceship::Spaceship()
{
    shootSound = LoadSound("resources/sounds/laser.ogg");
    texture = LoadTexture("resources/graphics/spaceship.png");
    position.x = (GetScreenWidth() - texture.width)/2;
    position.y = GetScreenHeight() - texture.height - 100;
    lastShootTime = 0.0;
}
Spaceship::~Spaceship()
{
    UnloadSound(shootSound);
    UnloadTexture(texture);
}

void Spaceship::Draw()
{
    DrawTextureV(texture, position, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= 5;
    if (position.x <= 25)
    {
        position.x = 25;
    }
}

void Spaceship::MoveRight()
{
    position.x += 5;
    if (position.x >= GetScreenWidth() - texture.width - 25)
    {
        position.x = GetScreenWidth() - texture.width - 25;
    }
}

void Spaceship::Shoot()
{
    if (GetTime() - lastShootTime >= 0.35)
    {
        lasers.push_back(Laser({position.x + texture.width/2 - 2, position.y}, 6));
        lastShootTime = GetTime();
        PlaySound(shootSound);
    }
    
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - texture.width)/2;
    position.y = GetScreenHeight() - texture.height - 100;
    lasers.clear();
}

Rectangle Spaceship::GetCollisionRec()
{
    return {position.x, position.y, (float)texture.width, (float)texture.height};
}
