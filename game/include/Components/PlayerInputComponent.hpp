#pragma once

#include "ecs.h"

class PlayerInputComponent : public Component
{
public:
	DEFINE_COMPONENT(PlayerInputComponent);

	float LinearSpeed = 100;
	float RotationSpeed = 180;
};