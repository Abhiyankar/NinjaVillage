#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos(){ return worldPos; }
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive(){ return alive; }
    void setAlive(bool isAlive){ alive=isAlive; }
protected:
    Texture2D texture{LoadTexture("textures/Idle.png")};
    Texture2D idle{LoadTexture("textures/Idle.png")};
    Texture2D run{LoadTexture("textures/Walk.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    float rightLeft{1.f};
    float upDown{1.f};
    int direction=1;

    float runningTime{};
    int frame{};
    int maxFrames{4};
    float updateTime{1.f/12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};
private:
    bool alive{true};
};

#endif