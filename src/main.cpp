#include <raylib.h>
#include <vector>

#include "../assets/eatSound.h"

const int screenWidth = 1920;
const int screenHeight = 1080;
const int gridSize = 32;
const int gridWidth = screenWidth / gridSize;
const int gridHeight = screenHeight / gridSize;

const float moveInterval = 0.15f;

enum Direction { UP, RIGHT, DOWN, LEFT };

int main() {
	
	InitWindow(screenWidth, screenHeight, "Snake Game");
	InitAudioDevice();
    SetTargetFPS(60);

	//Sound eatSound = LoadSound("../assets/eatSound.wav");
	Wave eatWave = LoadWaveFromMemory(".wav", eatSound, eatSound_size);
	Sound eatSoundEffect = LoadSoundFromWave(eatWave);

    std::vector<Vector2> snakeBody;

    Direction snakeDirection = RIGHT;

    Direction nextDirection = RIGHT;

    bool shouldGrow = false;

    bool gameOver = false;

    int score = 0;

    float moveTimer = 0.0f;
    
    snakeBody.push_back({0, 0});
    

    Vector2 foodPosition = {
        static_cast<float>(GetRandomValue(0, gridWidth - 1)),
        static_cast<float>(GetRandomValue(0, gridHeight - 1))
    };

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        if (!gameOver) {
            if (IsKeyPressed(KEY_UP) && snakeDirection != DOWN) 
                nextDirection = UP;
            if (IsKeyPressed(KEY_RIGHT) && snakeDirection != LEFT) 
                nextDirection = RIGHT;
            if (IsKeyPressed(KEY_DOWN) && snakeDirection != UP) 
                nextDirection = DOWN;
            if (IsKeyPressed(KEY_LEFT) && snakeDirection != RIGHT) 
                nextDirection = LEFT;
        } else {

            if (IsKeyPressed(KEY_SPACE)) {
                snakeBody.clear();
                snakeBody.push_back({0, 0});
                snakeDirection = RIGHT;
                nextDirection = RIGHT;
                shouldGrow = false;
                gameOver = false;
                score = 0;
                moveTimer = 0.0f;

                foodPosition = {
                    static_cast<float>(GetRandomValue(0, gridWidth - 1)),
                    static_cast<float>(GetRandomValue(0, gridHeight - 1))
                };
            }
        }
        if (!gameOver) {
            moveTimer += deltaTime;

            if (moveTimer >= moveInterval) {

                moveTimer = 0.0f;

                snakeDirection = nextDirection;

                Vector2 newHead = snakeBody[0];
                
                switch (snakeDirection) {
                    case UP: newHead.y--; break;
                    case RIGHT: newHead.x++; break;
                    case DOWN: newHead.y++; break;
                    case LEFT: newHead.x--; break;
                }
                if (newHead.x < 0 || newHead.x >= gridWidth || 
                    newHead.y < 0 || newHead.y >= gridHeight) {
                    gameOver = true;
                }
                for (size_t i = 0; i < snakeBody.size(); i++) {
                    if (newHead.x == snakeBody[i].x && newHead.y == snakeBody[i].y) {
                        gameOver = true;
                        break;
                    }
                }
                if (!gameOver) {
                    snakeBody.insert(snakeBody.begin(), newHead);

                    if (newHead.x == foodPosition.x && newHead.y == foodPosition.y) {
                        shouldGrow = true;
                        score += 10;
                        
						PlaySound(eatSoundEffect);
						
                        foodPosition = {
                            static_cast<float>(GetRandomValue(0, gridWidth - 1)),
                            static_cast<float>(GetRandomValue(0, gridHeight - 1))
                        };
                        
                        bool foodOnSnake;
                        do {
                            foodOnSnake = false;
                            for (const auto& segment : snakeBody) {
                                if (foodPosition.x == segment.x && foodPosition.y == segment.y) {
                                    foodOnSnake = true;
                                    foodPosition = {
                                        static_cast<float>(GetRandomValue(0, gridWidth - 1)),
                                        static_cast<float>(GetRandomValue(0, gridHeight - 1))
                                    };
                                    break;
                                }
                            }
                        } while (foodOnSnake);
                    }
                    if (!shouldGrow) {
                        snakeBody.pop_back();
                    } else {
                        shouldGrow = false;
                    }
                }
            }
        }
        BeginDrawing();

        ClearBackground(BLACK);
        
        for (int i = 0; i < gridWidth; i++) {
            for (int j = 0; j < gridHeight; j++) {
                DrawRectangleLines(i * gridSize, j * gridSize, gridSize, gridSize, Color{50, 50, 50, 255});
            }
        }
        
        DrawRectangle(foodPosition.x * gridSize, foodPosition.y * gridSize, gridSize, gridSize, RED);
        
        for (size_t i = 0; i < snakeBody.size(); i++) {
            Color segmentColor = (i == 0) ? GREEN : LIME;
            DrawRectangle(snakeBody[i].x * gridSize, snakeBody[i].y * gridSize, 
                         gridSize, gridSize, segmentColor);
        }
        
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
        
        if (gameOver) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 40)/2, 
                    screenHeight/2 - 40, 40, RED);
            DrawText("Press SPACE to restart", screenWidth/2 - MeasureText("Press SPACE to restart", 20)/2, 
                    screenHeight/2 + 10, 20, WHITE);
        }
        
        EndDrawing();
    }
    
	UnloadSound(eatSoundEffect);
    CloseWindow();
}