#pragma once
#include "raylib.h"

class Game
{
private:
    Sound explosionSound;
    Sound shootSound;
    int Lives;
    static Game *s_pInstance;
    int score;
    int highScore;
    bool run;
    Game(/* args */);
    ~Game();

    void RegisterComponents();
    void RegisterSystems();
    void CreateEntities();
    void GenerateSpaceship();
    void GenerateAliens();
    void GenerateMysteryship();
    void GenerateObstacles();
    void LoadSounds();
    void UnloadSounds();
    void SaveHighScore(int score);
    int LoadHighScore();
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
    Sound GetExplosionSound() { return explosionSound; }
    Sound GetShootSound() { return shootSound; }
    int GetLives() { return Lives; }
    void DecreaseLives() { Lives--; }
    int GetScore() { return score; }
    int GetHighScore() { return highScore; }
    int GetAliensCount();
    void CheckHighScore();
    void GameOver();
};