/*
-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "Game.hpp"
#include "patch.hpp"

std::string FormatScore(int score, int leadingZeros)
{
	std::string scoreStr = std::to_string(score);
	int zeros = leadingZeros - scoreStr.length();
	scoreStr = std::string(zeros, '0') + scoreStr;
	return scoreStr;
}

int main ()
{
	Color grey = {29, 29, 27, 255};
	Color yellow = { 243, 216, 63, 255 };
	int offset = 50;
	int screenWidth = 750;
	int screenHeight = 700;
	// set up the window
	InitWindow(screenWidth + offset, screenHeight + (2 * offset), "C++ Space Invaders");
	SetTargetFPS(60);

	InitAudioDevice();

	Font font = LoadFontEx("resources/fonts/monogram.ttf", 64, 0, 0);
	Texture2D spaceshipTexture = LoadTexture("resources/graphics/spaceship.png");
	std::cout << "Screen Width: " << GetScreenWidth() << std::endl;
	std::cout << "screenWidth: " << screenWidth  + offset << std::endl;
	std::cout << "Screen Height: " << GetScreenHeight() << std::endl;
	std::cout << "screenHeight: " << screenHeight + (2 * offset) << std::endl;
	// game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(Game::Instance()->GetMusic());
		Game::Instance()->HandleInput();
		Game::Instance()->Update();
		BeginDrawing();
		ClearBackground(grey);
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 2, yellow);
		DrawLineEx({25, 730}, {775, 730}, 3, yellow);
		if(Game::Instance()->IsRunning())
		{
			DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);

		} else {
			DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
		}
		float x = 50;
		for (int i = 0; i < Game::Instance()->GetLives(); i++)
		{
			DrawTextureV(spaceshipTexture, {x, 745}, WHITE);
			x += 50;
		}
		
		DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
		std::string scoreStr = FormatScore(Game::Instance()->GetScore(), 5);
		DrawTextEx(font, scoreStr.c_str(), {50, 40}, 34, 2, yellow);

		DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
		std::string highScoreStr = FormatScore(Game::Instance()->GetHighScore(), 5);
		DrawTextEx(font, highScoreStr.c_str(), {655, 40}, 34, 2, yellow);

		Game::Instance()->Draw();
		
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	CloseAudioDevice();
	return 0;
}