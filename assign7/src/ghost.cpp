#include "ghost.h"

void ghost::move (int dx, int dy) 
{
    auto pos = _pos;
    pos.first  += dx;
    pos.second += dy;
    _pos = pos;

}