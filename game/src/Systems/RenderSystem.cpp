#include "ecs.h"
#include "raylib.h"
#include "Systems/RenderSystem.hpp"
#include "Components/TransformComponent.hpp"
#include "TransformManager.hpp"

void RenderSystem::Update()
{
	DoForEachComponent<TransformComponent>([this](TransformComponent& component)
		{
			TransformManager::Instance()->PushTransformComponent(component, ECSContainer);
			
			// Color tint = WHITE;
			// ColorComponent* color = ECSContainer.TryGetComponent<ColorComponent>(component.EntityId);
			// if (color)
			// 	tint = color->GetColor();

			// CircleComponent* circle = ECSContainer.TryGetComponent<CircleComponent>(component.EntityId);
			// if (circle)
			// 	DrawCircleV(Vector2Zero(), circle->Radius, tint);

			// RectangleComponent* rectangle = ECSContainer.TryGetComponent<RectangleComponent>(component.EntityId);
			// if (rectangle)
			// 	DrawRectangleRec(rectangle->Bounds, tint);

			TransformManager::Instance()->PopTransformComponent(component, ECSContainer);
		});
}