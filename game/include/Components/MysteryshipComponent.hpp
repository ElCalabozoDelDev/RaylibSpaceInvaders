#pragma once

#include "ecs.h"

class MysteryshipComponent : public Component
{
public:
    DEFINE_COMPONENT(MysteryshipComponent);
    float Timer;
    float Cooldown;
};