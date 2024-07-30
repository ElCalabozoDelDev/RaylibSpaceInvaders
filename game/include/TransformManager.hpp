#pragma once
#include "Components/TransformComponent.hpp"

class TransformManager
{
private:
    static TransformManager* s_pInstance;
    TransformManager() {}
    ~TransformManager() {}
public:
    static TransformManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new TransformManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    void PushTransformComponent(const TransformComponent& transform, ECS& ecs);

    void PopTransformComponent(const TransformComponent& transform, ECS& ecs);
};