#pragma once
#include "ecs.h"

class LaserShootSystem : public System
{
public:
    SYSTEM_CONSTRUCTOR(LaserShootSystem);

    void Update() override;
};