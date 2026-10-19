/*
Game: Classy Clash
Author: Alexander Johnson
May, 21st 2026
*/

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>


int main() {
    // Window Dimensions
    const int windowWidth{1152};
    const int windowHeight{1152};

    // Window initialization
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/map2.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};
    Enemy goblin{Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")};


    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")}, 
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Rock.png")}
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies) {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while(!WindowShouldClose()){
    
    BeginDrawing();
    ClearBackground(WHITE);

    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

    // Draw the map
    DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
    
    // Draw the props
    for (auto prop : props) {
        prop.Render(knight.getWorldPos());
    }

    if(!knight.getAlive()) { // Character is not alive
        DrawText("Game Over!", 55.f, 45.f, 40, RED);
        EndDrawing();
        continue;
    }
    else { // Character is alive
        std::string knightsHealth{"Health: "};
        knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
        DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
    }

    knight.tick(GetFrameTime());
    // goblin.tick(GetFrameTime());
    for (auto enemy : enemies) {
        enemy->tick(GetFrameTime());
    }

    // Check map boundary
    if( knight.getWorldPos().x < 0.f || 
        knight.getWorldPos().y < 0.f || 
        knight.getWorldPos().x + windowWidth > map.width * mapScale || 
        knight.getWorldPos().y + windowHeight > map.height * mapScale
    ) {
        knight.undoMovement();
    }

    // Check knight collision
    for (auto prop : props) {
        if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
            knight.undoMovement();
        }
    }



    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (auto enemy : enemies) {
            if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
                enemy->setAlive(false);
            }
        }   
    }


    EndDrawing();
    }

    // Offload
    UnloadTexture(map);
    CloseWindow();
}