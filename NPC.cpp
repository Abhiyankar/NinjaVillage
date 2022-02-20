#include "NPC.h"

NPC::NPC(Vector2 pos,Texture2D idle,Texture2D run,int x,int y,int w,int h,int f)
{
    worldPos=pos;
    this->idle=idle;
    this->run=run;
    locX=x;
    locY=y;
    width=w;
    height=h;
    maxFrames=f;
    speed=1.5f;
    texture=idle;
}

void NPC::tick(float deltaTime,Vector2 playerPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos,playerPos) };

    Vector2 vec{800.f,300.f};
    velocity=Vector2Subtract(vec,screenPos);

    if(worldPos.x==800.f&&worldPos.y==300.f)
    velocity={};
    
    runningTime+=deltaTime;
    if(runningTime>=updateTime)
    {
        frame++;
        runningTime=0.f;
        if(frame>maxFrames)     frame=0;
    }

    if(static_cast<int>(velocity.x)<0)    {direction=3;}
    if(static_cast<int>(velocity.x)>0)    {direction=1;}
    if(static_cast<int>(velocity.y)<0)    {direction=0;}
    if(static_cast<int>(velocity.y)>0)    {direction=2;}

    Rectangle source;
    if(Vector2Length(velocity)!=0.0)
    {
        worldPos=Vector2Add(worldPos,Vector2Scale(Vector2Normalize(velocity),speed));
        
        velocity.x < 0.f ? rightLeft=-1.f : rightLeft=1.f;
        velocity.y < 0.f ? upDown=-1.f : upDown=1.f;
        texture=run;

        if(frame==0)    frame+=1;

        if(rightLeft==-1&&direction==3)
        {
            source={32,width*frame,width,height};
        }
        if(rightLeft==1&&direction==1)
        {
            source={48,width*frame,width,height};
        }
        if(upDown==-1&&direction==0)
        {
            source={16,width*frame,width,height};
        }
        if(upDown==1&&direction==2)
        {
            source={0,width*frame,width,height};
        }
    }
    else
    {
        texture=idle;
        if(rightLeft==-1&&direction==3)
        source={32,0.f,width,height};
        if(rightLeft==1&&direction==1)
        source={48,0.f,width,height};
        if(upDown==-1&&direction==0)
        source={16,0.f,width,height};
        if(upDown==1&&direction==2)
        source={0,0.f,width,height};
    }
    
    velocity={};
    Rectangle dest{screenPos.x,screenPos.y,scale*width,scale*height};
    DrawTexturePro(texture,source,dest,Vector2{},0.f,WHITE);
}