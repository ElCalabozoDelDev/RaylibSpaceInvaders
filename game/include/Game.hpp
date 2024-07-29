#pragma once
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/CollisionSystem.hpp"

class Game
{
private:
    static Game *s_pInstance;
    Game(/* args */);
    ~Game();
    EntityManager entityManager;
    RenderSystem renderSystem;
    CollisionSystem collisionSystem;
    bool run;
public:
    static Game *Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }
    void Update(float deltaTime);
    void Draw();
    bool IsRunning() { return run; }
};
