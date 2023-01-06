#ifndef PACTEAM2_ASTAR_HPP
#define PACTEAM2_ASTAR_HPP
#include "Direction.hpp"
#include "PieceBoard.hpp"
#include "Position.hpp"
#include <vector>

namespace Astar {
    struct Node {
        Position pos;
        int hcost, gcost;
        Node* parent;
        explicit Node(Position position, Node* parent_ = nullptr);
        int getFcost() const;
    };

    Direction getOptimalDirection(PieceBoard* pb, Position currentPosition, Position endPosition, Position invalidPosition = Position(-1,-1));

    Node* getNode(const std::vector<Node*>& nodeList, Position position);
}

#endif //PACTEAM2_ASTAR_HPP
