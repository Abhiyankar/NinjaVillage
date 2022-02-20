#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos=worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width*scale,
        height*scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame=worldPos;

    runningTime+=deltaTime;
    if(runningTime>=updateTime)
    {
        frame++;
        runningTime=0.f;
        if(frame>maxFrames)     frame=0;
    }
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
    //0 for up
    //1 for right
    //2 for down
    //3 for left

    Rectangle dest{getScreenPos().x,getScreenPos().y,scale*width,scale*height};
    DrawTexturePro(texture,source,dest,Vector2{},0.f,WHITE);
}