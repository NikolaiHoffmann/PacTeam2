#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h> // srand, rand
#include "lib/Game.hpp"
#include "lib/PacmanKeyBoardAgent.hpp"
#include "lib/PacmanMiniMaxAgent.hpp"
#include "lib/EvaluationFunction.hpp"

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    int ticksPerSecond = 5;
    srand(time(NULL));
    milliseconds timeout((int)((1.0 / ticksPerSecond) * 1000));
    Game game = Game("../maps/map0.txt", ticksPerSecond, 1, 1, new PacmanMiniMaxAgent(new EvaluationFunction()));
    /*
    Current solution only works for windows! (the GetAsyncKeyState function)
    We should find an alternative to work on linux too.
    */

    game.printBoard();
    sleep_for(timeout); //sleep interval
    while (game.update()) {
        system("cls");
        game.printBoard();
        sleep_for(timeout); //sleep interval
    }
    //cycle ends when the game is over
    system("cls");
    game.printBoard(); //prints final board state

    return 0;
}
