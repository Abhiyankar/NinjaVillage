#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth,int winHeight):
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width=texture.width/maxFrames;
    height=texture.height;
}

Vector2 Character::getScreenPos()
{
    return {
        static_cast<float>(windowWidth)/2.f-scale*(0.5f*width),
        static_cast<float>(windowHeight)/2.f-scale*(0.5f*height)
    };
}

void Character::tick(float deltaTime)
{
    if(!getAlive()) return;

    if(IsKeyDown(KEY_A))    {velocity.x-=1.0;direction=3;}
    if(IsKeyDown(KEY_D))    {velocity.x+=1.0;direction=1;}
    if(IsKeyDown(KEY_W))    {velocity.y-=1.0;direction=0;}
    if(IsKeyDown(KEY_S))    {velocity.y+=1.0;direction=2;}
    
    BaseCharacter::tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    float changeX{};
    float changeY{};
    if(direction==1)
    {
        origin={0.f,weapon.height*1.f};
        offset={45.f,70.f};
        weaponCollisionRec={
            getScreenPos().x+offset.x,
            getScreenPos().y+offset.y-weapon.height*scale,
            weapon.width*scale,
            weapon.height*scale
        };
        rotation=-90.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? changeX = 20.f : 0.f;
    }
    else if(direction==3)
    {
        origin={weapon.width*scale,weapon.height*1.f};
        offset={20.f,70.f};
        weaponCollisionRec={
            getScreenPos().x+offset.x-weapon.width*scale,
            getScreenPos().y+offset.y-weapon.height*scale,
            weapon.width*scale,
            weapon.height*scale
        };
        rotation=90.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? changeX = -20.f : 0.f;
    }
    else if(direction==0)
    {
        origin={weapon.width*scale,weapon.height*1.f};
        offset={40.f,40.f};
        weaponCollisionRec={
            getScreenPos().x+offset.x-weapon.width*scale,
            getScreenPos().y+offset.y-weapon.height*scale,
            weapon.width*scale,
            weapon.height*scale
        };
        rotation=180.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? changeY = -20.f : 0.f;
    }
    else if(direction==2)
    {
        origin={weapon.width*scale,weapon.height*1.f};
        offset={65.f,70.f};
        weaponCollisionRec={
            getScreenPos().x+offset.x-weapon.width*scale,
            getScreenPos().y+offset.y-weapon.height*scale,
            weapon.width*scale,
            weapon.height*scale
        };
        rotation=360.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? changeY = 20.f : 0.f;
    }

    Rectangle source{0.f,0.f,static_cast<float>(weapon.width)*rightLeft,static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x+offset.x+changeX,getScreenPos().y+offset.y+changeY,weapon.width*scale,weapon.height*scale};
    DrawTexturePro(weapon,source,dest,origin,rotation,WHITE);

    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}

void Character::takeDamage(float damage)
{
    health-=damage;
    if(health<=0.f)
    {
        setAlive(false);
    }
}