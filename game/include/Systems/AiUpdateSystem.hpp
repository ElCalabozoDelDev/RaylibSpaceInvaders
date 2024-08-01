#pragma once
#include "ecs.h"

class AiUpdateSystem : public System
{
public:
    SYSTEM_CONSTRUCTOR(AiUpdateSystem);

    void Update() override;
};