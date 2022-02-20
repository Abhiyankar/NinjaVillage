#ifndef NPC_H
#define NPC_H

#include "raylib.h"
#include "raymath.h"

class NPC
{
public:
    NPC(Vector2 pos,Texture2D idle,Texture2D run,int x,int y,int w,int h,int f);
    void tick(float deltaTime,Vector2 playerPos);
    //Rectangle GetCollisionRec(Vector2 playerPos);

private:
    Texture2D idle{};
    int direction=1;
    Texture2D texture{};
    Texture2D run{};
    float rightLeft{1.f};
    float upDown{1.f};
    Vector2 worldPos{};
    float scale{4.f};
    Vector2 velocity{};
    int width{};
    int height{};
    int locX{};
    int locY{};
    int frame=0;
    float speed{};
    int maxFrames{};
    float runningTime{};
    float updateTime{1.f/12.f};
};

#endif