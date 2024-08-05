#pragma once
#include <raylib.h>
#include "ecs.h"

class LaserComponent : public Component
{
public:
    DEFINE_COMPONENT(LaserComponent);
    Vector2 Size = {4, 15};
};