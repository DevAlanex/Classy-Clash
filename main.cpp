/*
Game: Classy Clash
Author: Alexander Johnson
May, 21st 2026
*/

#include "raylib.h"
#include "raymath.h"
#include "Character.h"


int main() {
    // Window Dimensions
    const int windowWidth{384};
    const int windowHeight{384};

    // Window initialization
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
    
    BeginDrawing();
    ClearBackground(WHITE);

    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

    // Draw the map
    DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
    knight.tick(GetFrameTime());

    if( knight.getWorldPos().x < 0.f || 
        knight.getWorldPos().y < 0.f || 
        knight.getWorldPos().x + windowWidth > map.width * mapScale || 
        knight.getWorldPos().y + windowHeight > map.height * mapScale
    ) {
        knight.undoMovement();
    }

    EndDrawing();
    }

    // Offload
    UnloadTexture(map);
    CloseWindow();
}