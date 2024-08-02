#pragma once
#include "raylib.h"
#include "ecs.h"
class AlienComponent : public Component
{
public:
    DEFINE_COMPONENT(AlienComponent);
    int Type;
};