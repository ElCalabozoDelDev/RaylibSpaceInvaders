#pragma once
#include "raylib.h"
#include "ecs.h"

class AiControllerComponent : public Component
{
public:
    DEFINE_COMPONENT(AiControllerComponent);
    int Type;
    Vector2 Direction = {1, 0};
};