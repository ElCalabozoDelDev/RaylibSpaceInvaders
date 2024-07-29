#pragma once
#include <raylib.h>

class Block
{
private:
    Vector2 position;
public:
    Block(Vector2 pos);
    virtual ~Block() {}
    void Draw();
    Rectangle GetCollisionRec() { return {position.x, position.y, 3, 3}; }
};