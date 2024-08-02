#pragma once
#include "raylib.h"
#include "ecs.h"

class AiControllerComponent : public Component
{
public:
    DEFINE_COMPONENT(AiControllerComponent);
    Vector2 Direction = {0, 0};
};