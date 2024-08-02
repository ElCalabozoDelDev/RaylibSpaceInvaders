#pragma once
#include "ecs.h"

class MysteryshipSpawnSystem : public System
{
public:
    SYSTEM_CONSTRUCTOR(MysteryshipSpawnSystem);

    void Update() override;
    void Spawn();
};