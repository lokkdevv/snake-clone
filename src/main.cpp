#include <raylib.h>
#include <vector>
#include <array>
#include <iostream>
#include <thread>
#include <chrono>

constexpr int MAX_TILES = 500; //20 * 25

constexpr int screenHeight = 640; //32 * 20
constexpr int screenWidth = 800; //32 * 25

int main()
{
	InitWindow(screenWidth, screenHeight, "snake");
	SetTargetFPS(60);

	std::array<int, MAX_TILES> tileState;

	/*
	for(auto i : mapTiles)
	{
		std::cout << i.x << ',' << i.y << '\n';
	}
	*/

	Vector2 snakeSize = {32, 32};
	Vector2 snakePos = {0, 0};
	Vector2 snakeDir = {0, 0};

	while(!WindowShouldClose())
	{
		////////////////////////////////INPUT////////////////////////////////
		if((snakeDir.x == 1 || snakeDir.x == -1) && (IsKeyDown(KEY_W) || IsKeyDown(KEY_S))) snakeDir.x = 0;
		
		if(IsKeyDown(KEY_A) && snakeDir.x != 1.f) snakeDir.x = -1;
		if(IsKeyDown(KEY_D) && snakeDir.x != -1.f) snakeDir.x = 1;
		
		if((snakeDir.y == 1 || snakeDir.y == -1) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))) snakeDir.y = 0;
		
		if(IsKeyDown(KEY_W) && snakeDir.y != 1.f) snakeDir.y = -1;
		if(IsKeyDown(KEY_S) && snakeDir.y != -1.f) snakeDir.y = 1;

		///////////////////////////////UPDATE////////////////////////////////
		for(int i = 0; i < MAX_TILES; i++)
		{
			i++;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(70));

		snakePos.x += snakeDir.x * 32;
		snakePos.y += snakeDir.y * 32;

		////////////////////////////////DRAW/////////////////////////////////
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangle(snakePos.x, snakePos.y, snakeSize.x, snakeSize.y, RED);
		EndDrawing();
	}

	CloseWindow();
}