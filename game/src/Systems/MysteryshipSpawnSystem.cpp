#include "Systems/MysteryshipSpawnSystem.hpp"
#include "Components/MysteryshipComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/ActiveStateComponent.hpp"

void MysteryshipSpawnSystem::Update()
{
    DoForEachComponent<MysteryshipComponent>([this](MysteryshipComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        TextureComponent* texture = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
        if (!texture)
            return;

        double currentTime = GetTime();
        if (currentTime - component.Timer > component.Cooldown)
        {
            Spawn();
            component.Timer = GetTime();
            component.Cooldown = GetRandomValue(10, 20);
        }
    });
}
void MysteryshipSpawnSystem::Spawn()
{
    DoForEachComponent<MysteryshipComponent>([this](MysteryshipComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        TextureComponent* texture = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
        if (!texture)
            return;

        ActiveStateComponent* active = ECSContainer.TryGetComponent<ActiveStateComponent>(component.EntityId);
        if (!active)
            return;

        active->Active = true;
        component.Speed = GetRandomValue(1, 3);
        transform->Position.y = 90;
        int side = GetRandomValue(0, 1);
        if (side == 0)
        {
            transform->Position.x = 25;
            component.Speed = 3;
        }
        else
        {
            transform->Position.x = GetScreenWidth() - texture->Texture.width - 25;
            component.Speed = -3;
        }
    });
}