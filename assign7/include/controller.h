#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <atomic>
#include "map.h"
#include "gameObject.h"
#include "player.h"
#include "ghost.h"

class Controller 
{
    public:
        Controller(int height, int width);
        ~Controller();
        void setPlayer(player* P);
        void addGhost(ghost* G);
        void run();

    private:
   
        std::vector<ghost*> ghosts_;    
        Map map_;                   
        player* player_;                   
        static char getch();
        void handleInput(int key);
};

#endif 
