#pragma once

#include "ecs.h"
#include <raymath.h>
#include "raylib.h"

class SpaceshipComponent : public Component
{
public:
    DEFINE_COMPONENT(SpaceshipComponent);

    Texture2D Texture;
};