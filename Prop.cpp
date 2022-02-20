#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos,Texture2D tex,int x,int y,int w,int h)
{
    worldPos=pos;
    texture=tex;
    locX=x;
    locY=y;
    width=w;
    height=h;
}

void Prop::Render(Vector2 playerPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos,playerPos) };
    //DrawTextureEx(texture,screenPos,0.f,scale,WHITE);
    Rectangle source{locX,locY,width,height};
    Rectangle dest{screenPos.x,screenPos.y,scale*width,scale*height};
    DrawTexturePro(texture,source,dest,Vector2{},0.f,WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 playerPos)
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