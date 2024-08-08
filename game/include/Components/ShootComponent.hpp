#pragma once

#include "ecs.h"

class ShootComponent : public Component
{
public:
    DEFINE_COMPONENT(ShootComponent);
    bool Shoot = false;
    float LastShootTime = 0;
    float ShootCooldown = 0.5f;
};