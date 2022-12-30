#ifndef PACTEAM2_BFS_HPP
#define PACTEAM2_BFS_HPP

#include "PieceBoard.hpp"
#include "Board.hpp"
#include <queue>
#include <vector>

namespace BFS {

    //returns the distance from pacman to the nearest piece given as argument
    int getClosestPieceDistanceFromPacman(Piece p, Board* board);

    //returns a vector with the distances to the ghosts, given the number of ghosts to look for
    std::vector<int> getNearestGhostsDistanceFromPacman(int nghosts, Board* board);
}

#endif //PACTEAM2_BFS_HPP
