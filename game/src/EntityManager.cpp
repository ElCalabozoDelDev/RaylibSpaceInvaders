#include "EntityManager.hpp"

Entity EntityManager::CreateEntity() {
    return nextEntityId++;
}

void EntityManager::DestroyEntity(Entity entity) {
    // Eliminar componentes asociados con la entidad
}

template<typename T>
void EntityManager::AddComponent(Entity entity, T component) {
    // Añadir el componente a la entidad
}

template<typename T>
T& EntityManager::GetComponent(Entity entity) {
    // Obtener el componente asociado con la entidad
}