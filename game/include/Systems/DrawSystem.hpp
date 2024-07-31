#pragma once
#include "ecs.h"

class DrawSystem : public System
{
public:
	SYSTEM_CONSTRUCTOR(DrawSystem);

	void Update() override;
};