#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "AnimatedProp.h"
#include "Enemy.h"
#include "NPC.h"
#include "NavRectangle.h"
#include <string>
#include <vector>

int main()
{   
    const int windowWidth{500};
    const int windowHeight{500};
    InitWindow(windowWidth,windowHeight,"NinjaVillage");

    Texture2D map=LoadTexture("textures/untitled.png");
    Vector2 mapPos{0.0,0.0};

    Character ninja{windowWidth,windowHeight};

    const float mapScale{4.0f};

    Prop props[2]
    {
        Prop{Vector2{600.f,300.f}, LoadTexture("textures/TilesetNature.png"),0,162,16,16},
        Prop{Vector2{400.f,500.f}, LoadTexture("textures/TilesetNature.png"),48,176,16,16},
    };

    AnimatedProp Aprops[1]
    {
        AnimatedProp{Vector2{700.f,700.f}, LoadTexture("textures/Flag.png"),0,0,16,16,4}
    };

    Enemy BlueSamurai{
        Vector2{800.f,300.f},
        LoadTexture("textures/BlueIdle.png"),  
        LoadTexture("textures/BlueWalk.png")
    };

    NPC Monk{
        Vector2{800.f,100.f},
        LoadTexture("textures/MonkIdle.png"),
        LoadTexture("textures/MonkWalk.png"),
        0,0,16,16,4
    };

    Enemy* enemies[]
    {
        &BlueSamurai
    };

    NPC* npcs[]
    {
        &Monk
    };

    // std::vector<NavRec> points;
    // points.push_back(NavRec{800.f,300.f,16.f,16.f});

    for(auto enemy:enemies)
    {
        enemy->setTarget(&ninja);
    }

    // for(auto npc:npcs)
    // {
    //     npc->setTarget(points,&ninja);
    // }

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        mapPos=Vector2Scale(ninja.getWorldPos(),-1.f);
        DrawTextureEx(map,mapPos,0.0,mapScale,WHITE);

        for(auto prop:props)
        {
            prop.Render(ninja.getWorldPos());
        }

        // for(auto Aprop:Aprops)
        // {
                //this is not working
        // }
        //Aprops[0].tick(GetFrameTime(),ninja.getWorldPos());

        int i=0;
        while(i!=1)
        {
            Aprops[i].tick(GetFrameTime(),ninja.getWorldPos());
            i++;
        }
        
        for(auto npc:npcs)
        {
            npc->tick(GetFrameTime(),ninja.getWorldPos());
        }

        ninja.tick(GetFrameTime());

        if(ninja.getWorldPos().x<0.f||
           ninja.getWorldPos().y<0.f||
           ninja.getWorldPos().x+windowWidth>map.width*mapScale||
           ninja.getWorldPos().y+windowHeight>map.height*mapScale)
        {
            ninja.undoMovement();
        }

        for(auto Aprop:Aprops)
        {
            if(CheckCollisionRecs(Aprop.GetCollisionRecAprop(ninja.getWorldPos()),ninja.GetCollisionRec()))
            {
                ninja.undoMovement();
            }
        }

        for(auto prop:props)
        {
            if(CheckCollisionRecs(prop.GetCollisionRec(ninja.getWorldPos()),ninja.GetCollisionRec()))
            {
                ninja.undoMovement();
            }
        }

        for(auto enemy:enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // for(auto npc:npcs)
        // {
        //     npc->tick(GetFrameTime());
        // }

        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}