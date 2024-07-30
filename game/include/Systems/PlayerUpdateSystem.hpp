#pragma once
#include "ecs.h"

class PlayerUpdateSystem : public System
{
public:
	SYSTEM_CONSTRUCTOR(PlayerUpdateSystem);

	void Update() override;
};