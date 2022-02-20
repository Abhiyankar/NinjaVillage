#ifndef PROP_H
#define PROP_H

#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos,Texture2D tex,int x,int y,int w,int h);
    void Render(Vector2 playerPos);
    Rectangle GetCollisionRec(Vector2 playerPos);

protected:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
    int width{};
    int height{};
    int locX{};
    int locY{};
};

#endif