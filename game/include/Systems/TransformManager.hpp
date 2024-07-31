#pragma once
#include "ecs.h"
#include "Components/TransformComponent.hpp"

class TransformManager
{
private:
public:
    static void PushTransformComponent(const TransformComponent& transform, ECS& ecs);

    static void PopTransformComponent(const TransformComponent& transform, ECS& ecs);
};