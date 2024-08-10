#include "Managers/AlienManager.hpp"

AlienManager *AlienManager::s_pInstance = 0;

int AlienManager::GetAliensCount(ECS &ecs)
{
    ComponentTable<AlienComponent>* alienTable = ecs.GetComponentTable<AlienComponent>();
    if (!alienTable)
        return 0;

    int count = 0;
    for (auto& alien : alienTable->Components)
    {
        count++;
    }
    return count;
}