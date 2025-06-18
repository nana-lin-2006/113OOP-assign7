
#ifndef PLAYER_H
#define PLAYER_H
#include "gameObject.h"
#include <vector>
#include <iostream>
class player: public GameObject
{
    public:
    player(int x, int y) : GameObject(x, y) {}
    char icon() const override { return 'P'; }
    void move(int dx, int dy);
};

#endif
