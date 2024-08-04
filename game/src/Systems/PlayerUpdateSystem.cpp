#include "raylib.h"
#include "raymath.h"
#include "Systems/PlayerUpdateSystem.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/LaserComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include <iostream>


void PlayerUpdateSystem::Update()
{
	DoForEachComponent<PlayerInputComponent>([this](PlayerInputComponent& component)
		{
			float deltaSpeed = component.LinearSpeed;

			TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
			if (!transform)
				return;
			TextureComponent* spaceship = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
			if (!spaceship)
				return;

			Vector2 move = { 0,0 };

			if (IsKeyDown(KEY_LEFT))
			{
				move.x -= deltaSpeed;
				if (transform->Position.x <= 25)
				{
					move.x = 0;
				}
			}

			if (IsKeyDown(KEY_RIGHT))
			{
				move.x += deltaSpeed;
				if (transform->Position.x >= GetScreenWidth() - spaceship->Texture.width - 25)
				{
					move.x = 0;
				}
			}

			if(IsKeyPressed(KEY_SPACE))
			{
				component.Shoot = true;
			} else
			{
				component.Shoot = false;
			}

			transform->Position = Vector2Add(transform->Position, move);
		});
}