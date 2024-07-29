#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"

class Obstacle
{
private:
    Vector2 position;
    static std::vector<std::vector<int>> grid;
    std::vector<Block> blocks;
public:
    Obstacle(Vector2 pos);
    virtual ~Obstacle() {}
    void Draw();
    static int GetWidth() { return grid[0].size() * 3; }
    // Métodos públicos para acceder a los iteradores de blocks
    std::vector<Block>::iterator BlocksBegin() { return blocks.begin(); }
    std::vector<Block>::iterator BlocksEnd() { return blocks.end(); }
    // Método público para borrar un bloque
    std::vector<Block>::iterator EraseBlock(std::vector<Block>::iterator it) { return blocks.erase(it); }
};