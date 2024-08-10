#pragma once
#include "ecs.h"
#include "Components/AlienComponent.hpp"

class AlienManager
{
public:
    static AlienManager *Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new AlienManager();
            return s_pInstance;
        }

        return s_pInstance;
    }

    int GetAliensCount(ECS& ecs);

private:
    static AlienManager  *s_pInstance;
    AlienManager() {}
    ~AlienManager() {}
    // AlienManager(const AlienManager&) = delete;
    // AlienManager& operator=(const AlienManager&) = delete;
};
