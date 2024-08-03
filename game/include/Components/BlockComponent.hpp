#pragma once
#include "raylib.h"
#include "ecs.h"

class BlockComponent : public Component
{
public:
    DEFINE_COMPONENT(BlockComponent);
    Vector2 Size = {3, 3};
    Color Color = {243, 216, 63, 255};
};