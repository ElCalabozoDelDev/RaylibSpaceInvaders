#include "Systems/PlayerUpdateSystem.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "raylib.h"
#include "raymath.h"
void PlayerUpdateSystem::Update()
{
	DoForEachComponent<PlayerInputComponent>([this](PlayerInputComponent& component)
		{
			float deltaSpeed = component.LinearSpeed * GetFrameTime();

			TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
			if (!transform)
				return;

			Vector2 move = { 0,0 };

			if (IsKeyDown(KEY_W))
				move.y -= deltaSpeed;

			if (IsKeyDown(KEY_S))
				move.y += deltaSpeed;

			if (IsKeyDown(KEY_A))
				move.x -= deltaSpeed;

			if (IsKeyDown(KEY_D))
				move.x += deltaSpeed;

			transform->Position = Vector2Add(transform->Position, move);
		});
}