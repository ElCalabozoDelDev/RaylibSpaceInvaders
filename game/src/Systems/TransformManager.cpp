#include <rlgl.h>
#include "Systems/TransformManager.hpp"
#include "Components/TransformComponent.hpp"


void TransformManager::PushTransformComponent(const TransformComponent &transform, ECS &ecs)
{
    if (transform.Parent != uint64_t(-1))
    {
        TransformComponent *parentTransform = ecs.TryGetComponent<TransformComponent>(transform.Parent);
        if (parentTransform)
        {
            PushTransformComponent(*parentTransform, ecs);
        }
    }

    rlPushMatrix();
    // rlTranslatef(transform.Position.x, transform.Position.y, 0);
    // rlRotatef(transform.Angle, 0, 0, 1);
}

void TransformManager::PopTransformComponent(const TransformComponent &transform, ECS &ecs)
{
    rlPopMatrix();

    if (transform.Parent != uint64_t(-1))
    {
        TransformComponent *parentTransform = ecs.TryGetComponent<TransformComponent>(transform.Parent);
        if (parentTransform)
        {
            PopTransformComponent(*parentTransform, ecs);
        }
    }
}