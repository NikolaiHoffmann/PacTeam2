#include <iostream>
#include <chrono>
#include <thread>
// #include <cstdlib> // srand, rand
#include "lib/Game.hpp"
#include "lib/PacmanKeyBoardAgent.hpp"
#include "lib/PacmanMiniMaxAgent.hpp"
#include "lib/EvaluationFunction.hpp"

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    int ticksPerSecond = 5;
    //srand(time(nullptr));
    milliseconds timeout((int)((1.0 / ticksPerSecond) * 1000));
    Game game = Game("../../maps/map0.txt", ticksPerSecond, 1, 1, new PacmanMiniMaxAgent(new EvaluationFunction()));
    /*
    Current solution only works for windows! (the GetAsyncKeyState function)
    We should find an alternative to work on linux too.
    */

    steady_clock::time_point begin = std::chrono::steady_clock::now();
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
    steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Total game ticks: " << game.elapsedGameTicks() << std::endl;
    std::cout << "Total elapsed time: " << duration_cast<seconds>(end-begin).count() << std::endl;

    return 0;
}
