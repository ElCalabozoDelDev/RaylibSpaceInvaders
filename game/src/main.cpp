/*
Author: FJBC
Date: 2024-07-31
Description: Main file of the game
*/

#include "raylib.h"
#include "Game.hpp"


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
    InitAudioDevice();
    Game *game = Game::Instance();

    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);

        game->Update();
        DrawFPS(10, 10);
        EndDrawing();
    }
    // Close window and OpenGL context
    CloseWindow();
    CloseAudioDevice();
    return 0;
}