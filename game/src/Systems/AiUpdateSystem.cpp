#include "raylib.h"
#include "Systems/AiUpdateSystem.hpp"
#include "Components/AiControllerComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"

void AiUpdateSystem::Update()
{
    DoForEachComponent<AiControllerComponent>([this](AiControllerComponent& component)
        {
            TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
            if (!transform)
                return;
            TextureComponent* texture = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
            if (!texture)
                return;
            Vector2 move = {0, 0};
            if(component.Type < 4)
            {
                if(transform->Position.x + texture->Texture.width > GetScreenWidth() - 25)
                {
                    component.Direction = -1;
                    move.y = 4;
                }
                if(transform->Position.x < 25)
                {
                    component.Direction = 1;
                    move.y = 4;
                }
            }
            move.x = component.Direction;
            // Move aliens
            transform->Position = Vector2Add(transform->Position, move);
        });
}
