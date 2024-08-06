#pragma once
#include "ecs.h"

class CollisionSystem : public System
{
public:
    SYSTEM_CONSTRUCTOR(CollisionSystem);

    void Update() override;

private:
    void CheckSpaceshipLasersCollisions();
    int GetAliensCount();
};