#include "gameObject.h"

GameObject::GameObject(int x, int y)
  : _pos(x, y)
{}

std::pair<int,int> GameObject::getPosition() const {
    return _pos;
}
