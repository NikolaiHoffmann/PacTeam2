#include "Astar.hpp"
#include <iostream>

/*
* This function receives the current state of the board, the start position,
* the end position, and optionally, a position the optimal path can't go through (invalidPosition)
* this function uses the A* algorithm to calculate the next best direction to take
*/
Direction Astar::getOptimalDirection(PieceBoard* pb, Position currentPosition, Position endPosition, Position invalidPosition) {
    std::vector<Node*> open, closed;
    open.reserve(100);
    closed.reserve(100);
    Node* currentNode = nullptr;
    int currentNodeIndex = 0;

    open.push_back(new Node(currentPosition));

    while (!open.empty()) {
        auto current_it = open.begin();
        currentNode = *current_it;
        for (auto it = open.begin(); it != open.end(); it++) {
            auto node = *it;
            if (node->getFcost() <= currentNode->getFcost()) {
                currentNode = node;
                //currentNodeIndex = i;
                current_it = it;
            }
        }
        //currentNode = open[0];
        //for (int i = 0; i < open.size(); i++) {
        //	if (open[i]->getFcost() <= currentNode->getFcost()) {
        //		currentNode = open[i];
        //		currentNodeIndex = i;
        //	}
        //}
        if (endPosition.equals(currentNode->pos)) break;

        open.erase(current_it);
        closed.push_back(currentNode);

        Direction directions[4] = {
                Direction::Up,
                Direction::Down,
                Direction::Left,
                Direction::Right
        };
        for (int i = 0; i < 4; i++) {
            Position currentNeighbor = (currentNode->pos).translate(directions[i]);
            //if the current neighbor position is a wall, or if he's in the closed list,
            //go to the next neighbor
            if (pb->isInvalid(currentNeighbor) || currentNeighbor.equals(invalidPosition) || getNode(closed, currentNeighbor)) continue;

            int cost = currentNode->gcost + 1;

            Node* neighborNode = getNode(open, currentNeighbor);
            if (neighborNode == nullptr) {
                //the neighbor is not in the open list
                neighborNode = new Node(currentNeighbor, currentNode);
                neighborNode->gcost = cost;
                neighborNode->hcost = currentNeighbor.manhattanDistance(endPosition);
                open.push_back(neighborNode);
            }
            else if (cost < neighborNode->gcost) {
                neighborNode->parent = currentNode;
                neighborNode->gcost = cost;
            }
        }
    }

    std::vector<Position> positionList;
    if (open.empty()) {
        /*
        * In case the open vector is empty, it means it didn't find the end position.
        * Therefore, we will set currentNode to the node that has the least manhattan distance
        * to the end position, and we will backtrace the path from there
        */
        auto current_it = closed.begin();
        currentNode = *current_it;
        for (auto it = closed.begin(); it != closed.end(); it++) {
            auto node = *it;
            if ((node->pos).manhattanDistance(endPosition) < (currentNode->pos).manhattanDistance(endPosition)) {
                currentNode = node;
                //currentNodeIndex = i;
                current_it = it;
            }
        }
    }
    while (currentNode != nullptr) {
        positionList.insert(positionList.begin(), currentNode->pos);
        currentNode = currentNode->parent;
    }
    return positionList[0].getDirection(positionList[1]);
}

/*
* Gets a node list and a position, and returns the node with the given position,
* or returns nullptr if the list doesnt contain a node with this position
*/
Astar::Node* Astar::getNode(std::vector<Node*> nodeList, Position position) {
    for (Node* node : nodeList) {
        if (position.equals(node->pos)) {
            return node;
        }
    }
    return nullptr;
}

int Astar::Node::getFcost() {
    return hcost + gcost;
}

Astar::Node::Node(Position position, Node* parent_)
{
    pos = position;
    hcost = gcost = 0;
    parent = parent_;
}