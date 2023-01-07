#include <iostream>
#include <chrono>
#include <thread>
#include "lib/Game.hpp"
#include "lib/PacmanMiniMaxAgent.hpp"
#include "lib/EvaluationFunction.hpp"
#include "lib/PacmanKeyBoardAgent.hpp"

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    int ticksPerSecond = 5;
    milliseconds timeout((int)((1.0 / ticksPerSecond) * 1000));
    int mapID;
    bool playerActive;
    std::string mapPath;

    std::cout << "Insert ID of map (0,1,2):" << std::endl;
    std::cin >> mapID;
    std::cout << "Type in '1' to play as player or '0' to let the agent play:" << std::endl;
    std::cin >> playerActive;

    switch (mapID) {
        default:
            mapPath = "../../maps/map0.txt";
            break;
        case 0:
            mapPath = "../../maps/map0.txt";
            break;
        case 1:
            mapPath = "../../maps/map1.txt";
            break;
        case 2:
            mapPath = "../../maps/map2.txt";
            break;
    }

    PacmanAgent* agent;
    if (playerActive) agent = new PacmanKeyBoardAgent();
    else agent = new PacmanMiniMaxAgent(new EvaluationFunction());

    Game game = Game(mapPath, agent);

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
