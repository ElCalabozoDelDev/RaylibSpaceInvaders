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
#include "game.hpp"


int main ()
{
	Color grey = {29, 29, 27, 255};
	Color yellow = { 243, 216, 63, 255 };
	int offset = 50;
	int screenWidth = 750;
	int screenHeight = 700;
	// set up the window
	InitWindow(screenWidth + offset, screenHeight + 2 * offset, "C++ Space Invaders");
	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose())
	{
		Game::Instance()->HandleInput();
		Game::Instance()->Update();
		BeginDrawing();
		ClearBackground(grey);
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 2, yellow);
		Game::Instance()->Draw();
		
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}