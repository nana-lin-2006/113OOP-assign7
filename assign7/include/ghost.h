#ifndef GHOSTF_H
#define GHOST_H
#include "gameObject.h"

class ghost : public GameObject {
public:
    ghost(int x, int y) : GameObject(x, y) {}
    void move(int dx, int dy);
    char icon() const override { return 'G'; }
};

#endif
