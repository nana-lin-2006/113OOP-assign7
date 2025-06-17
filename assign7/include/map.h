#ifndef MAP_H
#define MAP_H

#include <vector>

class Map {
public:
    Map(int height, int width, char emptySym = ' ', char obstacleSym = '#');
    void setPlayer(const class player& player_);
    void setGhosts(const class ghost& ghost_);
    void setWall();
    bool movePlayer(int oldX, int oldY, int newX, int newY);
    void moveGhost(player* player_, std::vector<ghost*>& ghosts_);
    void display() const;
    int getHeight() const;
    int getWidth() const;

private:
    std::vector<std::vector<char>> grid;
    char emptySymbol;
    char obstacleSymbol;
};

#endif
