#pragma once
#include "raylib.h"

class Game
{
private:
    static Game *s_pInstance;
    Game(/* args */);
    ~Game();

    void RegisterComponents();
    void RegisterSystems();
    void CreateEntities();
    void GenerateSpaceship();
    void GenerateAliens();
    void GenerateMysteryship();

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
    void Update();
};