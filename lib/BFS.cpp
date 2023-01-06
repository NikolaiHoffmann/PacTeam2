#include "BFS.hpp"
#include <queue>

/*
* Returns the distance from pacman to the nearest piece given as argument
*/
int BFS::getClosestPieceDistanceFromPacman(Piece p, Board* board) {
    PieceBoard* pb = board->getPieceBoard();
    Position startingPosition = board->getPacman()->getPosition();
    int boardH = board->getHeight(), boardW = board->getWidth();
    bool** visited = new bool* [boardH];
    //initialize visited array
    for (int i = 0; i < boardH; i++) {
        visited[i] = new bool[boardW];
        for (int j = 0; j < boardW; j++) {
            visited[i][j] = false;
        }
    }

    //queue with tuple {Position, depth}
    //so that we associate certain nodes with their distance to the origin
    std::queue <std::pair<Position, int>> nodeQueue;
    int depth = 0;

    nodeQueue.push({ startingPosition, depth });
    visited[startingPosition.getY()][startingPosition.getX()] = true;

    while (!nodeQueue.empty()) {
        std::pair<Position, int> node = nodeQueue.front();
        Position pos = node.first;
        depth = node.second;

        //the current node is the requested piece, so we return the depth (distance from the
        // initial node to the current node.
        if (pb->isPiece(pos, p)) return depth;

        //remove analysed node from the queue
        nodeQueue.pop();

        //iterate every direction
        //for every direction, if the position adjacent to the current isn't a wall,
        // we add it to the queue so as to analyse it later.
        for (int i = 0; i < 4; i++) {
            auto currentDirection = (Direction)i;
            Position newPos = pos.translate(currentDirection);
            int newPosY = newPos.getY(), newPosX = newPos.getX();

            if (!visited[newPosY][newPosX] &&
                !pb->isWall(newPos)) {
                nodeQueue.push({ newPos, depth + 1 });
                visited[newPosY][newPosX] = true;
            }
        }
    }
    // we free the nodes of the visited matrix
    for (int h = 0; h < boardH; h++) {
        delete[] visited[h];
    }
    delete[] visited;
    return -1; //couldnt find the given piece in the PieceBoard
}

/*
* Given the number of ghosts to get the distance from pacman, we return a vector with
* the corresponding distances
*/
std::vector<int> BFS::getNearestGhostsDistanceFromPacman(int nghosts, Board* board) {
    PieceBoard* pb = board->getPieceBoard();
    int boardH = board->getHeight(), boardW = board->getWidth();
    Position startingPosition = board->getPacman()->getPosition();
    bool** visited = new bool* [boardH];
    //initialize visited array
    for (int i = 0; i < boardH; i++) {
        visited[i] = new bool[boardW];
        for (int j = 0; j < boardW; j++) {
            visited[i][j] = false;
        }
    }

    std::vector<int> ret;
    int ghostsFound = 0;

    //queue with tuple {Position, depth}
    //so that we associate certain nodes with their distance to the origin
    std::queue <std::pair<Position, int>> nodeQueue;
    int depth = 0;

    nodeQueue.push({ startingPosition, depth });
    visited[startingPosition.getY()][startingPosition.getX()] = true;

    while (!nodeQueue.empty()) {
        std::pair<Position, int> node = nodeQueue.front();
        Position pos = node.first;
        depth = node.second;

        if (board->collisionGhosts(pos)) {
            //this node collides with a ghost, so we return the distance from the origin
            // to this ghost, and we increase the count of ghosts found
            ret.push_back(depth);
            ghostsFound++;
            if (ghostsFound == nghosts) return ret;
        }
        nodeQueue.pop();

        //iterate every direction
        for (int i = 0; i < 4; i++) {
            auto currentDirection = (Direction)i;
            Position newPos = pos.translate(currentDirection);
            int newPosY = newPos.getY(), newPosX = newPos.getX();

            if (!visited[newPosY][newPosX] &&
                !pb->isWall(newPos)) {
                nodeQueue.push({ newPos, depth + 1 });
                visited[newPosY][newPosX] = true;
            }
        }
    }
    for (int h = 0; h < boardH; h++) {
        delete[] visited[h];
    }
    delete[] visited;
    return ret;
}