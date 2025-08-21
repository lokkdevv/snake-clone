#include <raylib.h>

int main()
{
	constexpr int width = 800; //25  *  32(cell size)
	constexpr int height = 416; //13  *  32(cell size)

	InitWindow(width, height, "snake-clone");
	SetTargetFPS(60);
}