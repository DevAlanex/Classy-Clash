/*
Game: Classy Clash
Author: Alexander Johnson
May, 21st 2026
*/

#include "raylib.h"
#include "raymath.h"

int main() {
    // Window Dimensions
    const int windowWidth{384};
    const int windowHeight{384};

    // Window initialization
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos {
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };

    float directionOfTravel{1.0};

    // Animation Variables
    float runningTime{};
    int frame{};
    const int maxFrames{};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
    
    BeginDrawing();
    ClearBackground(WHITE);

    Vector2 direction{};
    if(IsKeyDown(KEY_A)) direction.x -= 1.0;
    if(IsKeyDown(KEY_D)) direction.x += 1.0;
    if(IsKeyDown(KEY_W)) direction.y -= 1.0;
    if(IsKeyDown(KEY_S)) direction.y += 1.0;

    if(Vector2Length(direction) != 0.0) {

        //set mapPos = mapPos - direction
        mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? directionOfTravel = -1.f : directionOfTravel = 1.f;
    }

    // Draw the map - FIX MAP TEXTURES!!!!
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    runningTime += GetFrameTime();
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

    // Draw the character variables
    Rectangle source { 0.f, 0.f, directionOfTravel * (float)knight.width/6, (float)knight.height};
    Rectangle dest {knightPos.x, knightPos.y, 4.0f * knight.width/6, 4.0f * knight.height};

    // Draw the character
    DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

    EndDrawing();
    }

    // Offload
    UnloadTexture(map);
    UnloadTexture(knight);
    CloseWindow();
}