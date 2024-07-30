#include <rlgl.h>
#include "TransformManager.hpp"
#include "Components/TransformComponent.hpp"

TransformManager *TransformManager::s_pInstance = 0;

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
    rlTranslatef(transform.Position.x, transform.Position.y, 0);
    rlRotatef(transform.Angle, 0, 0, 1);
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