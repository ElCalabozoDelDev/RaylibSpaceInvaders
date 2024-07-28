#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    texture = LoadTexture("resources/graphics/mystery.png");
    active = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(texture);
}

void MysteryShip::Draw()
{
    if (active)
    {
        DrawTextureV(texture, position, WHITE);
    }
}

void MysteryShip::Update()
{
    if (active)
    {
        position.x += speed;
        if (position.x > GetScreenWidth() - texture.width || position.x < 0)
        {
            active = false;
        }
    }
}

void MysteryShip::Spawn()
{
    active = true;
    position.y = 90;
    speed = GetRandomValue(1, 3);
    int side = GetRandomValue(0, 1);
    if (side == 0)
    {
        position.x = 0;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - texture.width;
        speed = -3;
    }
}

Rectangle MysteryShip::GetCollisionRec()
{
    if (active)
    {
        return {position.x, position.y, (float)texture.width, (float)texture.height};
    }
    return {0, 0, 0, 0};
}
