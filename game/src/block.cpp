#include "block.hpp"

Block::Block(Vector2 pos)
{
    position = pos;
}

void Block::Draw()
{
    DrawRectangleV(position, {3, 3}, {243, 216, 63, 255});
}
