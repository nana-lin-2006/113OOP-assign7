#include "player.h"

void player::move (int dx, int dy) 
{
    auto pos = _pos;
    pos.first  += dx;
    pos.second += dy;
    _pos = pos;

}



