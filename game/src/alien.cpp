#include "alien.hpp"
#include "patch.hpp"
#include <string>
#include <iostream>

Texture2D Alien::textures[3] = {0};

Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;

    if (textures[type - 1].id == 0)
    {
        if (type < 1 || type > 3)
        {
            this->type = 1;
        }
        this->textures[type - 1] = LoadTexture(("resources/graphics/alien_" + patch::to_string(type) + ".png").c_str());
    }
    
}

void Alien::Draw()
{
    DrawTextureV(textures[type - 1], position, WHITE);
}

void Alien::Update(int dir)
{
    position.x += dir;
}
void Alien::UnloadTextures()
{
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(textures[i]);
    }
}

int Alien::GetPoints()
{
    return type * 100;
}
