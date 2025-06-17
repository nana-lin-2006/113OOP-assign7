#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <termios.h>
#include <unistd.h>
#include "controller.h"

int main() {
    // 建立地圖
    Controller control(15, 100);
    player player(0, 0);
    control.setPlayer(&player);
    control.run();
    return 0;
}
