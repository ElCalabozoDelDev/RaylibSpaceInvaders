#pragma once
#include <raylib.h>

class Alien
{
private:
    static Texture2D textures [3];
    Vector2 position;
    int type;
public:
    Alien(int type, Vector2 position);
    virtual ~Alien(){}
    void Draw();
    void Update(int dir);
    static void UnloadTextures();
    int GetType() { return type; }
    void MoveDown(int dist) { position.y += dist; }
    Vector2 GetPosition() { return position; }
    Texture2D GetTexture() { return textures[type - 1]; }
    Rectangle GetCollisionRec() { return {position.x, position.y, (float)textures[type - 1].width, (float)textures[type - 1].height}; }
    int GetPoints();
};
