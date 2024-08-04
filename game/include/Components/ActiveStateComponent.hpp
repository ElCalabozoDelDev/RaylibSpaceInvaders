#pragma once

#include "ecs.h"

class ActiveStateComponent : public Component
{
public:
    DEFINE_COMPONENT(ActiveStateComponent);
    bool Active;
};