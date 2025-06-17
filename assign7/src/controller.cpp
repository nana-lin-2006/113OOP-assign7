#include "controller.h"
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib> 

Controller::Controller(int height, int width)
  : map_(height, width),
    player_(nullptr)
    {
        map_.setWall(); // 設定障礙物
        
        ghosts_.push_back(new ghost(0, 99)); // 兩隻鬼
        ghosts_.push_back(new ghost(14, 0));
        for (auto& g : ghosts_) {
            map_.setGhosts(*g);
        }
    }

Controller::~Controller() = default;

void Controller::setPlayer(player* p) {
    player_ = p;
    map_.setPlayer(*player_);
}

void Controller::addGhost(ghost* g) {
    ghosts_.push_back(g);
    map_.setGhosts(*g);
}

char Controller::getch() {
    char buf = 0;
    struct termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    newt.c_lflag &= ~ECHO;
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    read(STDIN_FILENO, &buf, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return buf;
}

void Controller::handleInput(int key) {
    if (!player_ || key < 0) return;

    int dx = 0, dy = 0;
    switch (key) {
        case 'w': case 'W': dx = -1; break;
        case 's': case 'S': dx =  1; break;
        case 'a': case 'A': dy = -1; break;
        case 'd': case 'D': dy =  1; break;
        default: return;
    }
    
    auto oldPos = player_->getPosition();
    int newX = oldPos.first  + dx;
    int newY = oldPos.second + dy;


    if(map_.movePlayer(oldPos.first, oldPos.second, newX, newY)) {
        player_->move(dx, dy);
    }
    
    
}
void Controller::run() {
    std::atomic<bool> running{true};
    std::atomic<char> direction{' '};
    std::thread inputThread([&](){
        while (running.load()) {
            char c = getch();
            if (c == 27)           // ESC
                running = false;
            else
                direction = c;     // W/A/S/D
        }
    });

    while (running.load()) {
       
        map_.moveGhost(player_, ghosts_);
        {
            auto [px, py] = player_->getPosition();
            for (auto g : ghosts_) {
                auto [gx, gy] = g->getPosition();
                if (px == gx && py == gy) {
                
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    map_.display();
                    std::cout << "You lose!\n";
                    running = false;
                    inputThread.join();
                    exit(0);
                }
            }
        }

       
        handleInput(direction.load());

        
        {
            auto [px, py] = player_->getPosition();
            if (px == map_.getHeight() - 1 && py == map_.getWidth() - 1) {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                map_.display();
                std::cout << "You win!\n";
                running = false;
                inputThread.join();
                exit(0);
            }
        }

       
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        map_.display();

       
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    inputThread.join();
    std::cout << "Game quit!\n";
}
