#include "BFS.hpp"
#include <queue>

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
        int depth = node.second;

        if (pb->isPiece(pos, p)) return depth;

        nodeQueue.pop();

        //iterate every direction
        for (int i = 0; i < 4; i++) {
            Direction currentDirection = (Direction)i;
            Position newPos = pos.translate(currentDirection);
            int newPosY = newPos.getY(), newPosX = newPos.getX();

            if (visited[newPosY][newPosX] == false &&
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
    return -1; //couldnt find the given piece in the PieceBoard
}

std::vector<int> BFS::getNearestGhostsDistanceFromPacman(int nghosts, Board* board) {
    PieceBoard* pb = board->getPieceBoard();
    int boardH = board->getHeight(), boardW = board->getWidth();
    Position startingPosition = board->getPacman()->getPosition();
    bool** visited = new bool* [boardH];
    //bool visited[board->getHeight()][board->getWidth()]; //visited Positions array
    //initialize visited array
    for (int i = 0; i < boardH; i++) {
        visited[i] = new bool[boardW];
        for (int j = 0; j < boardW; j++) {
            visited[i][j] = false;
        }
    }
    //initialize visited array
    for (int i = 0; i < boardH; i++) {
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
        int depth = node.second;

        if (board->collisionGhosts(pos)) {
            ret.push_back(depth);
            ghostsFound++;
            if (ghostsFound == nghosts) return ret;
        }
        nodeQueue.pop();

        //iterate every direction
        for (int i = 0; i < 4; i++) {
            Direction currentDirection = (Direction)i;
            Position newPos = pos.translate(currentDirection);
            int newPosY = newPos.getY(), newPosX = newPos.getX();

            if (visited[newPosY][newPosX] == false &&
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