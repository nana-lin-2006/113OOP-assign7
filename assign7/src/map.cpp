#include "map.h"
#include "player.h"
#include "ghost.h"
#include <vector>
#include <iostream>
#include <utility>  
#include <algorithm>

Map::Map(int height, int width, char emptySym, char obstacleSym)
    : grid(height, std::vector<char>(width, emptySym)),
      emptySymbol(emptySym),
      obstacleSymbol(obstacleSym)
{}
void Map::setWall (){
    std::vector<std::pair<int, int>> walls = {
        //1
        {0,43 }, {0, 67},
        //2
        {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, 
        {1, 7},{1, 8}, {1, 9},{1, 10}, {1, 11},{1, 12}, {1, 13},{1, 43},
        {1, 67}, {1, 80},{1, 81}, {1, 82},{1, 83}, {1, 84},{1, 85}, {1, 86},
        {1, 87}, {1, 88},{1, 89}, {1, 90},{1, 91}, {1, 92},{1, 93}, {1, 94},
        {1, 95}, {1, 96},{1, 97}, {1, 98},{1, 99}, 
        //3
        {2, 25}, {2, 26},{2, 27}, {2, 28},{2, 29}, {2, 30},{2, 31}, {2, 32},{2, 33}, {2, 34},
        {2, 35}, {2, 36},{2, 37}, {2, 38},{2, 39}, {2, 40}, {2, 43},{2, 67},{2, 94},
        //4
        {3, 10}, {3, 11},{3, 12}, {3, 13}, {3, 14}, {3, 15}, {3, 16}, {3, 17}, {3, 18}, {3, 19},
        {3, 20},{3, 43}, {3, 44}, {3, 45}, {3, 46}, {3, 47}, {3, 48}, {3, 49}, {3, 50}, {3, 94},
        //5
        {4, 13},{4, 43},  {4, 94},
        //6
        {5, 13},  {5, 43}, {5, 56}, {5, 57}, {5, 58}, {5, 59}, {5, 60}, {5, 61}, {5, 62},
        {5, 63}, {5, 64}, {5, 65}, {5, 66}, {5, 67}, {5, 68}, {5, 69}, {5, 70}, {5, 71}, {5, 72}, {5, 73},
        {5, 74}, {5, 75}, {5, 94},
        //7
        {6, 13},  {6, 30},{6, 43},{6, 72},
        //8
        {7, 13}, {7, 17},{7, 30},{7, 72},
        //9
        {8, 17},{8, 30}, {8, 34}, {8, 35},{8, 36},{8, 37},{8, 38},{8, 39},{8, 40},{8, 41},{8, 42},{8, 43},{8, 44},{8, 45},{8, 46},
        {8, 47},{8, 48},{8, 49},{8, 50},{8, 51},{8, 52},{8, 53},{8, 60},{8, 72},
        //10
        {9, 17},{9, 30}, {9, 46}, {9, 60}, {9, 72},{9, 85},{9, 86},{9, 87},{9, 88},{9, 89},{9, 90},
        {9, 91},{9, 92},{9, 93},{9, 94},{9, 95},{9, 96},{9, 97},{9, 98},{9, 99},
        //11
        {10, 5}, {10, 6},{10, 7},{10, 8},{10, 9},{10, 10},{10, 11},{10, 12},{10, 13},{10, 14},{10, 15},{10, 16},
        {10, 17},{10, 18},{10, 19},{10, 20},{10, 21},{10, 22},{10, 23},{10, 24},{10, 25},{10, 30},{10, 46},{10, 60},{10, 72},
        //12
        {11, 30},{11, 39},{11, 46},{11, 60},{11, 72},{11, 90},
        //13
        {12, 10}, {12, 30}, {12, 39}, {12, 60},{12, 67},{12, 68},{12, 69},{12, 70},{12, 71},{12, 72},{12, 73},{12, 74},
        {12, 75},{12, 76},{12, 77},{12, 78},{12, 79},{12, 80},{12, 81},{12, 82},{12, 90},
        //14
        {13, 10},{13, 39},{13, 60},{13, 90},
        //15
        {14, 10}, {14, 39}, {14, 60}, {14, 90},

    };
    for (const auto& wall : walls) {
        int x = wall.first;
        int y = wall.second;
        if (x >= 0 && x < getHeight() && y >= 0 && y < getWidth()) {
            grid[x][y] = obstacleSymbol;
        }
    }
    
}

void Map::setPlayer(const player& player_) 
{
    std::pair<int, int> pos = player_.getPosition();
    int x = pos.first;
    int y = pos.second;
    if (x >= 0 && x < getHeight() && y >= 0 && y < getWidth())
    {
        grid[x][y] = player_.icon();
    }
        
}
void Map::setGhosts(const ghost& ghost_) 
{
    std::pair<int, int> pos = ghost_.getPosition();
    int x = pos.first;
    int y = pos.second;
    if (x >= 0 && x < getHeight() && y >= 0 && y < getWidth())
    {
        grid[x][y] = ghost_.icon();
    }
}

bool Map::movePlayer(int oldX, int oldY, int newX, int newY) {
    if (newX < 0 || newY < 0
     || newX >= getHeight()
     || newY >= getWidth())
        return false;
    if (grid[newX][newY] == obstacleSymbol)
        return false; // 檢查是否為障礙物
    grid[oldX][oldY] = emptySymbol;
    if( grid[newX][newY] == 'g') {
        grid[newX][newY] = 'g'; 
    }
    grid[newX][newY] = 'p';
    return true;

} 
void Map::moveGhost(player* player_, std::vector<ghost*>& ghosts_) {
    auto [px, py] = player_->getPosition();

    static const std::vector<std::pair<int,int>> dirs = {
        { 1, 0}, {-1, 0},
        { 0, 1}, { 0,-1}
    };

    for (auto g : ghosts_) {
        auto [gx, gy] = g->getPosition();

        std::vector<std::pair<int,int>> candidates;
        for (auto [dx, dy] : dirs) {
            int nx = gx + dx, ny = gy + dy;
            if (nx < 0 || nx >= getHeight() ||
                ny < 0 || ny >= getWidth())     continue;
            if (grid[nx][ny] == obstacleSymbol) continue;
            candidates.emplace_back(dx, dy);
        }
        if (candidates.empty()) continue;

        int chase_dx = (px > gx ? 1 : (px < gx ? -1 : 0));
        int chase_dy = (py > gy ? 1 : (py < gy ? -1 : 0));

       
        std::pair<int,int> chosen = candidates[std::rand() % candidates.size()];
        if (chase_dx || chase_dy) {
            for (auto& d : candidates) {
                if (d.first == chase_dx && d.second == 0) {
                    chosen = d;
                    break;
                }
                if (d.first == 0 && d.second == chase_dy) {
                    chosen = d;
                    break;
                }
            }
        }

      
        auto [dx, dy] = chosen;
        int newX = gx + dx, newY = gy + dy;
        grid[gx][gy]     = emptySymbol;
        grid[newX][newY] = g->icon();
        g->move(dx, dy);
    }
}

// 遊戲面板
void Map::display() const 
{
    int w = getWidth();
    // 上邊框（左角 + w 條 '-' + 右角）
    std::cout << '+';
    for (int i = 0; i < w; ++i) std::cout << '-';
    std::cout << "+\n";

    // 地圖內容 + 左右邊框
    for (const auto& row : grid) {
        std::cout << '|';
        for (char c : row) std::cout << c;
        std::cout << "|\n";
    }

    // 下邊框
    std::cout << '+';
    for (int i = 0; i < w; ++i) std::cout << '-';
    std::cout << "+\n";
}

int Map::getHeight() const { return static_cast<int>(grid.size()); }
int Map::getWidth()  const { return static_cast<int>(grid[0].size()); }
