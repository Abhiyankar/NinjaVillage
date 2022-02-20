#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos=pos;
    texture=idle_texture;
    idle=idle_texture;
    run=run_texture;
    width=texture.width/maxFrames;
    height=texture.height;
    speed=1.5f;
}

bool Enemy::Check(Rectangle R1, Rectangle R2)
{
    if (   (R2.x+R2.width) < (R1.x+R1.width)
        && (R2.x) > (R1.x)
        && (R2.y) > (R1.y)
        && (R2.y+R2.height) < (R1.y+R1.height)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Enemy::tick(float deltaTime)
{
    DetectionBox={getScreenPos().x-100,getScreenPos().y-100,300,300};

    if(!getAlive()) return;
    velocity=Vector2Subtract(target->getScreenPos(),getScreenPos());

    if(!Check(DetectionBox,target->GetCollisionRec()))
    {
        velocity={};
    }

    if(Vector2Length(velocity)<radius)  { velocity={}; }

    if(static_cast<int>(velocity.x)<0)    {direction=3;}
    if(static_cast<int>(velocity.x)>0)    {direction=1;}
    if(static_cast<int>(velocity.y)<0)    {direction=0;}
    if(static_cast<int>(velocity.y)>0)    {direction=2;}

    DrawRectangleLines(
        getScreenPos().x-100,
        getScreenPos().y-100,
        300,
        300,
        RED
    );

    //0 for up
    //1 for right
    //2 for down
    //3 for left

    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(target->GetCollisionRec(),GetCollisionRec()))
    {
        target->takeDamage(damagePerSec*deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}