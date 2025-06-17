#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>

class GameObject {
public:
    GameObject(int x, int y);
    std::pair<int,int> getPosition() const;
    virtual ~GameObject() = default;
    virtual char icon() const = 0;
protected:
    std::pair<int,int> _pos;
};

#endif // GAMEOBJECT_H
