#include "Position.hpp"
#include <cmath>

Position::Position(int x, int y) :
        x(x),
        y(y)
{
}

Position::Position() :
        x(-1),
        y(-1)
{
}

bool Position::operator == (const Position& coords) {
    return (x == coords.x && y == coords.y);
}

Position Position::translate(Direction direction) {
    int new_x = x;
    int new_y = y;
    switch (direction) {
        case Up:
            new_y -= 1;
            break;
        case Down:
            new_y += 1;
            break;
        case Right:
            new_x += 1;
            break;
        case Left:
            new_x -= 1;
            break;
        case Null:
            break;
    }
    return Position(new_x, new_y);
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}

int Position::manhattanDistance(Position endPos) {
    return std::abs(endPos.y - y) + std::abs(endPos.x - x);
}

bool Position::equals(Position pos) {
    return (x == pos.x) && (y == pos.y);
}

Direction Position::getDirection(Position newPos) {
    Position neighbors[4] = {
            translate(Direction::Up),
            translate(Direction::Down),
            translate(Direction::Left),
            translate(Direction::Right)
    };
    if (newPos.equals(neighbors[0])) {
        return Direction::Up;
    }
    else if (newPos.equals(neighbors[1])) {
        return Direction::Down;
    }
    else if (newPos.equals(neighbors[2])) {
        return Direction::Left;
    }
    else if (newPos.equals(neighbors[3])) {
        return Direction::Right;
    }
    return Direction::Null;
}

Direction Position::direction(Position endPos) {
    int diffX = endPos.getX() - x;
    int diffY = endPos.getY() - y;

    if (diffX == 1 && diffY == 0) {
        return Right;
    }
    else if (diffX == -1 && diffY == 0) {
        return Left;
    }
    else if (diffX == 0 && diffY == 1) {
        return Down;
    }
    else if (diffX == 0 && diffY == -1) {
        return Up;
    }
    return Null;
}

void Position::setX(int newx)
{
    x = newx;
}

void Position::setY(int newy)
{
    y = newy;
}