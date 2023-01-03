#include "Astar.hpp"
#include <iostream>

/*
* This function receives the current state of the board, the start position,
* the end position, and optionally, a position which optimal path can't go through (invalidPosition)
* this function uses the A* algorithm to calculate the next best direction to take
*/
Direction Astar::getOptimalDirection(PieceBoard* pb, Position currentPosition, Position endPosition, Position invalidPosition) {
    std::vector<Node*> open, closed;
    //open has the nodes that need to be analysed
    //closed has the nodes already analysed
    open.reserve(100);
    closed.reserve(100);
    Node* currentNode = nullptr;
    int currentNodeIndex = 0;

    //pushes no open vector the initial node
    open.push_back(new Node(currentPosition));

    while (!open.empty()) {
        auto currentNode_it = open.begin();
        currentNode = *currentNode_it;

        //this loop sets currentNode to the node with the least f cost
        //in astar, each iteration we analyse the node with the least f cost
        for (auto it = open.begin(); it != open.end(); it++) {
            auto node = *it;
            if (node->getFcost() <= currentNode->getFcost()) {
                currentNode = node;
                //currentNodeIndex = i;
                currentNode_it = it;
            }
        }

        //we reached the destination, so we can stop searching
        if (endPosition.equals(currentNode->pos)) break;

        //currentNode has been analysed, so we remove it from open and insert it
        // in closed
        open.erase(currentNode_it);
        closed.push_back(currentNode);

        Direction directions[4] = {
                Direction::Up,
                Direction::Down,
                Direction::Left,
                Direction::Right
        };

        //for each direction, we're going to check if the adjacent position in that
        // direction is a valid position. If so, we add it to open if it isn't already there.
        for (int i = 0; i < 4; i++) {
            Position currentNeighbor = (currentNode->pos).translate(directions[i]);

            //if the current neighbor position is a wall, or if he's in the closed list,
            //go to the next neighbor
            if (pb->isInvalid(currentNeighbor) || currentNeighbor.equals(invalidPosition) || getNode(closed, currentNeighbor)) continue;

            int cost = currentNode->gcost + 1;

            Node* neighborNode = getNode(open, currentNeighbor);
            if (neighborNode == nullptr) {
                //the neighbor is not in the open list, so we create it and insert in open
                neighborNode = new Node(currentNeighbor, currentNode);
                neighborNode->gcost = cost;
                neighborNode->hcost = currentNeighbor.manhattanDistance(endPosition);
                open.push_back(neighborNode);
            }
            else if (cost < neighborNode->gcost) {
                //this new path is closer than the previous one,
                // so we set the new parent and the new gcost.
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
    //we insert in positionList all the positions from origin to destination
    while (currentNode != nullptr) {
        positionList.insert(positionList.begin(), currentNode->pos);
        currentNode = currentNode->parent;
    }
    if (positionList.size() < 2) {
        //couldnt find path
        return Direction::Null;
    }
    //positionList[0] is the origin, and positionList[1] is the most optimal position in
    // order to get to the destination node.
    Direction ret = positionList[0].getDirection(positionList[1]);
    //here we free all the nodes created
    for (auto it = open.begin(); it != open.end(); it++) {
        auto node = *it;
        delete node;
    }
    for (auto it = closed.begin(); it != closed.end(); it++) {
        auto node = *it;
        delete node;
    }
    return ret;
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

/*
* Returns FCost. F cost is the sum of hcost and gcost, which are the distances to the destination
* and the distance to the origin, respectively.
*/
int Astar::Node::getFcost() {
    return hcost + gcost;
}

/*
* Creates a new node given the position and the parent node.
*/
Astar::Node::Node(Position position, Node* parent_)
{
    pos = position;
    hcost = gcost = 0;
    parent = parent_;
}