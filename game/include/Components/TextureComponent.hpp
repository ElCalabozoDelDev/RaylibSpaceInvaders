#pragma once

#include "ecs.h"
#include <raymath.h>
#include "raylib.h"

class TextureComponent : public Component
{
public:
    DEFINE_COMPONENT(TextureComponent);

    Texture2D Texture;
};