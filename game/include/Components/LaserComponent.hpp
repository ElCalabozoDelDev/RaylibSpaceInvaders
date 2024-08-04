#pragma once
#include <raylib.h>
#include "ecs.h"

class LaserComponent : public Component
{
public:
    DEFINE_COMPONENT(LaserComponent);
    float LastShootTime;
    float ShootCooldown;
};