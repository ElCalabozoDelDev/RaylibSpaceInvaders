/*
Author: FJBC
Date: 2024-07-31
Description: Main file of the game
*/

#include "raylib.h"
#include "Components/PlayerInputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpaceshipComponent.hpp"
#include "Systems/DrawSystem.hpp"
#include "Systems/PlayerUpdateSystem.hpp"

#define _ECS_IMPLEMENTATION
#include "ecs.h"
#include <iostream>

int main()
{
    int offset = 50;
	int screenWidth = 750;
	int screenHeight = 700;
    Color grey = {29, 29, 27, 255};
	Color yellow = { 243, 216, 63, 255 };
	// set up the window
	InitWindow(screenWidth + offset, screenHeight + 2 * offset, "C++ Space Invaders");
    SetTargetFPS(60);

    ECS ecs;
    // Register components
    ecs.RegisterComponent<PlayerInputComponent>();
    ecs.RegisterComponent<TransformComponent>();
    ecs.RegisterComponent<SpaceshipComponent>();

    // Register systems
    ecs.RegisterSystem<PlayerUpdateSystem>();
    ecs.RegisterSystem<DrawSystem>();

    // Create entities
    uint64_t spaceshipId = ecs.GetNewEntity();
    ecs.GetComponent<SpaceshipComponent>(spaceshipId)->Texture = LoadTexture("resources/graphics/spaceship.png");
    int spaceshipWidth = ecs.GetComponent<SpaceshipComponent>(spaceshipId)->Texture.width;
    int spaceshipHeight = ecs.GetComponent<SpaceshipComponent>(spaceshipId)->Texture.height;
    float spaceshipX = (GetScreenWidth() - spaceshipWidth) / 2;
    float spaceshipY = (GetScreenHeight() - spaceshipHeight - 100);
    ecs.GetComponent<TransformComponent>(spaceshipId)->Position = {spaceshipX, spaceshipY};
    ecs.GetComponent<TransformComponent>(spaceshipId)->Angle = 0;
    ecs.GetComponent<PlayerInputComponent>(spaceshipId)->LinearSpeed = 5;
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);

        ecs.Update();
        DrawFPS(10, 10);
        EndDrawing();
    }
    // Close window and OpenGL context
    CloseWindow();
    return 0;
}