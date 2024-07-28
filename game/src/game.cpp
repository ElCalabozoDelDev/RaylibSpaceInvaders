#include "game.hpp"
#include <iostream>
#include <fstream>

Game* Game::s_pInstance = 0;

Game::Game()
{
    Init();
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
    Alien::UnloadTextures();
}

void Game::Init()
{
    music = LoadMusicStream("resources/sounds/music.ogg");
    PlayMusicStream(music);
    explosionSound = LoadSound("resources/sounds/explosion.ogg");
    obstacles = GenerateObstacles();
    aliens = GenerateAliens();
    alienDir = 1;
    alienLaserTimer = 0;
    mysteryShipTimer = 0;
    mysteryShipCooldown = GetRandomValue(10, 20);
    lives = 3;
    run = true;
    score = 0;
    highScore = LoadHighScore();
}

void Game::Restart()
{
    player.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::CheckHighScore()
{
    if (score > highScore)
    {
        highScore = score;
        SaveHighScore(highScore);
    }
}

void Game::SaveHighScore(int score)
{
    std::ofstream file("resources/highscore.txt");
    if (file.is_open())
    {
        file << score;
        file.close();
    } else {
        std::cerr << "Unable to save highscore to file" << std::endl;
    }
}

int Game::LoadHighScore()
{
    int score = 0;
    std::ifstream file("resources/highscore.txt");
    if (file.is_open())
    {
        file >> score;
        file.close();
    } else {
        std::cerr << "Unable to load highscore from file" << std::endl;
    }
    return score;
}

void Game::DeleteInactives()
{
    for (auto it = player.LasersBegin(); it != player.LasersEnd();)
    {
        if (!it->IsActive())
        {
            it = player.EraseLaser(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->IsActive())
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::AlienShoot()
{
    double currentTime = GetTime();
    if (currentTime - alienLaserTimer >= alienLaserCooldown && aliens.size() > 0)
    {
        int alienIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[alienIndex];
        Vector2 pos = {alien.GetPosition().x + alien.GetTexture().width/2, alien.GetPosition().y + alien.GetTexture().height};
        alienLasers.push_back(Laser(pos, -6));
        alienLaserTimer = GetTime();
    }
}

void Game::CheckCollisions()
{
    // spaceship lasers
    for (auto& laser : player.GetLasers())
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->GetCollisionRec(), laser.GetCollisionRec()))
            {
                PlaySound(explosionSound);
                score += it->GetPoints();
                it = aliens.erase(it);
                laser.Deactivate();
                CheckHighScore();
            }
            else
            {
                ++it;
            }
        }
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.BlocksBegin();
            while (it != obstacle.BlocksEnd())
            {
                if (CheckCollisionRecs(it->GetCollisionRec(), laser.GetCollisionRec()))
                {
                    it = obstacle.EraseBlock(it);
                    laser.Deactivate();
                }
                else
                {
                    ++it;
                }
            }
        }
        if (CheckCollisionRecs(mysteryShip.GetCollisionRec(), laser.GetCollisionRec()))
        {
            PlaySound(explosionSound);
            score += mysteryShip.GetPoints();
            mysteryShip.Deactivate();
            laser.Deactivate();
            CheckHighScore();
        }
    }

    // alien lasers
    for (auto& laser : alienLasers)
    {
        if (CheckCollisionRecs(laser.GetCollisionRec(), player.GetCollisionRec()))
        {
            lives--;
            if (lives == 0)
            {
                GameOver();
            }
            
            laser.Deactivate();
        }
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.BlocksBegin();
            while (it != obstacle.BlocksEnd())
            {
                if (CheckCollisionRecs(it->GetCollisionRec(), laser.GetCollisionRec()))
                {
                    it = obstacle.EraseBlock(it);
                    laser.Deactivate();
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // aliens collision with obstacles
    for (auto& alien : aliens)
    {
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.BlocksBegin();
            while (it != obstacle.BlocksEnd())
            {
                if (CheckCollisionRecs(it->GetCollisionRec(), alien.GetCollisionRec()))
                {
                    it = obstacle.EraseBlock(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        if(CheckCollisionRecs(alien.GetCollisionRec(), player.GetCollisionRec()))
        {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    std::cout << "Game Over" << std::endl;
    run = false;
}

std::vector<Obstacle> Game::GenerateObstacles()
{
    int obstacleWidth = Obstacle::GetWidth();
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
}

std::vector<Alien> Game::GenerateAliens()
{
    std::vector<Alien> aliens;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            int type;
            if (i == 0)
            {
                type = 3;
            }
            else if (i < 3)
            {
                type = 2;
            }
            else
            {
                type = 1;
            }
            float x = j * 55 +75;
            float y = i * 55 + 110;
            aliens.push_back(Alien(type, {x, y}));
        }
        
    }
    return aliens;
}

void Game::MoveAliens()
{
    for (auto& alien: aliens)
    {
        if (alien.GetPosition().x + alien.GetTexture().width > GetScreenWidth() - 25)
        {
            alienDir = -1;
            MoveDownAliens(4);
        }
        if (alien.GetPosition().x < 25)
        {
            alienDir = 1;
            MoveDownAliens(4);
        }
        alien.Update(alienDir);
    }
}

void Game::MoveDownAliens(int dist)
{
    for (auto& alien: aliens)
    {
        alien.MoveDown(dist);
    }
}

void Game::Update()
{
    if (!run)
    {
        return;
    }
    double currentTime = GetTime();
    if (currentTime - mysteryShipTimer > mysteryShipCooldown)
    {
        mysteryShip.Spawn();
        mysteryShipTimer = GetTime();
        mysteryShipCooldown = GetRandomValue(10, 20);
    }
    for (auto& laser : player.GetLasers())
    {
        laser.Update();
    }
    MoveAliens();
    AlienShoot();
    for (auto& laser : alienLasers)
    {
        laser.Update();
    }
    DeleteInactives();
    mysteryShip.Update();
    CheckCollisions();
}

void Game::Draw()
{
    player.Draw();
    for (auto& laser : player.GetLasers())
    {
        laser.Draw();
    }
    for (auto& obstacle : obstacles)
    {
        obstacle.Draw();
    }
    for (auto& alien : aliens)
    {
        alien.Draw();
    }
    for (auto& laser : alienLasers)
    {
        laser.Draw();
    }
    mysteryShip.Draw();
}

void Game::HandleInput()
{
    if(!run)
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            Restart();
            Init();
        }
        return;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        player.MoveLeft();
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player.MoveRight();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        player.Shoot();
    }
}