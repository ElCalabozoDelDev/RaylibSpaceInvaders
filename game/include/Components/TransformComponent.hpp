#pragma once

#include "ecs.h"
#include "raylib.h"

class TransformComponent : public Component
{
public:
	DEFINE_COMPONENT(TransformComponent);

	Vector2 Position = { 0,0 };
	float Angle = 0;
	uint64_t Parent = uint64_t(-1);
};