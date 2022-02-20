//#include "raymath.h"
#include "AnimatedProp.h"
#include <iostream>

AnimatedProp::AnimatedProp(Vector2 pos,Texture2D tex,int x,int y,int w,int h,int f) : Prop(pos,tex,x,y,w,h)
{
    maxFrames=f;
}

void AnimatedProp::tick(float deltaTime,Vector2 playerPos)
{
    runningTime+=deltaTime;
    if(runningTime>=updateTime)
    {
        frame++;
        runningTime=0.f;
        if(frame>maxFrames)     frame=0;
    }
    Rectangle source{width*frame,locY,width,height};
    Vector2 screenPos{ Vector2Subtract(worldPos,playerPos) };
    //DrawTextureEx(texture,screenPos,0.f,scale,WHITE);
    Rectangle dest{screenPos.x,screenPos.y,scale*width,scale*height};
    DrawTexturePro(texture,source,dest,Vector2{},0.f,WHITE);
}

Rectangle AnimatedProp::GetCollisionRecAprop(Vector2 playerPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos,playerPos) };
    DrawRectangleLines(
        screenPos.x+10,
        screenPos.y+10,
        width*2.f,
        height*2.f,
        RED
    );
    return Rectangle{
        screenPos.x+10,
        screenPos.y+10,
        width*2.f,
        height*2.f
    };
}