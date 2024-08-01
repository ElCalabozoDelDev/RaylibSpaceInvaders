#pragma once
#include "ecs.h"

class AiUpdateSystem : public System
{
public:
    SYSTEM_CONSTRUCTOR(AiUpdateSystem);

    void Update() override;
    void CheckDirectionChange(bool &changeDirection, int &globalDirection);
    void MoveAliens(bool changeDirection, int globalDirection);
};