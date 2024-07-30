#pragma once
#include "ecs.h"

class RenderSystem : public System
{
public:
	SYSTEM_CONSTRUCTOR(RenderSystem);

	void Update() override;
};