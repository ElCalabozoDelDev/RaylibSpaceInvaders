#pragma once

#include "ecs.h"

class MysteryshipComponent : public Component
{
public:
    DEFINE_COMPONENT(MysteryshipComponent);
    int Speed;
    float Timer;
    float Cooldown;
};