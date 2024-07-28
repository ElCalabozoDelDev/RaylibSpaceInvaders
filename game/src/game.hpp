#pragma once
#include <raylib.h>
#include <vector>
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game
{
private:
    static Game* s_pInstance;
    Spaceship player;
    MysteryShip mysteryShip;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;
    int alienDir;
    int lives;
    constexpr static float alienLaserCooldown = 0.5;
    float alienLaserTimer;
    float mysteryShipCooldown;
    float mysteryShipTimer;
    bool run;
    int score;
    int highScore;
    Music music;
    Sound explosionSound;
    Game();
    ~Game();
    std::vector<Obstacle> GenerateObstacles();
    std::vector<Alien> GenerateAliens();
    void MoveAliens();
    void MoveDownAliens(int dist);
    void DeleteInactives();
    void AlienShoot();
    void CheckCollisions();
    void Init();
    void GameOver();
    void Restart();
    void CheckHighScore();
    void SaveHighScore(int score);
    int LoadHighScore();
    int GetAliensCount() { return aliens.size(); }
public:
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    void Draw();
    void Update();
    void HandleInput();
    void Shutdown() {}
    bool IsRunning() { return run; }
    int GetLives() { return lives; }
    int GetScore() { return score; }
    int GetHighScore() { return highScore; }
    Music GetMusic() { return music; }
};
