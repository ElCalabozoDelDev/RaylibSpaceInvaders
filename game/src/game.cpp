#include "Game.hpp"

Game* Game::s_pInstance = 0;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Update(float deltaTime) {
    // Actualizar sistemas
    collisionSystem.Update(/* parámetros */);
}

void Game::Draw() {
    // Dibujar entidades
    renderSystem.Update(/* parámetros */);
}