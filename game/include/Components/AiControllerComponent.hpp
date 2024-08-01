#pragma once
#include "ecs.h"

class AiControllerComponent : public Component
{
public:
    DEFINE_COMPONENT(AiControllerComponent);
    int Type;
    float Direction = 1;
};