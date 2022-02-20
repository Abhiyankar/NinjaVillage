#ifndef ANIMATED_PROP_H
#define ANIMATED_PROP_H

#include "Prop.h"
#include "raylib.h"
#include "raymath.h"

class AnimatedProp : Prop
{
public:
    AnimatedProp(Vector2 pos,Texture2D tex,int x,int y,int w,int h,int f);
    void tick(float deltaTime,Vector2 playerPos);
    Rectangle GetCollisionRecAprop(Vector2 playerPos);

private:
    int frame=0;
    int maxFrames{};
    float runningTime{};
    float updateTime{1.f/12.f};
};

#endif