#include "PacmanKeyBoardAgent.hpp"
#include <windows.h>

void PacmanKeyBoardAgent::updateState(Board* board) {
    if (GetAsyncKeyState(VK_UP) & 1) {
        //Up arrow was clicked since last time
        //player->setDirection(Direction::Up);
        board->changePlayerDirection(Direction::Up);
    }
    else if (GetAsyncKeyState(VK_DOWN) & 1) {
        board->changePlayerDirection(Direction::Down);
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 1) {
        board->changePlayerDirection(Direction::Right);
    }
    else if (GetAsyncKeyState(VK_LEFT) & 1) {
        board->changePlayerDirection(Direction::Left);
    }
    board->movePlayer();
}