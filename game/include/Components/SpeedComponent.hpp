#pragma once
#include "ecs.h"

class SpeedComponent : public Component
{
public:
    DEFINE_COMPONENT(SpeedComponent);
    float Speed = 0;
};