#pragma once
#include "ecs.h"
#include "raylib.h"

class CollisionComponent : public Component
{
public:
    DEFINE_COMPONENT(CollisionComponent);
    Rectangle BoundingBox; // Área de colisión
};