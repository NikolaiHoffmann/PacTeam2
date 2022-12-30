#ifndef PACTEAM2_POSITION_HPP
#define PACTEAM2_POSITION_HPP

#include "Direction.hpp"

struct Position {
private:
    int x;
    int y;
public:
    Position();
    Position(int x, int y);
    Position translate(Direction direction);
    int getX();
    int getY();
    void setX(int newx);
    void setY(int newy);
    int manhattanDistance(Position endPos);
    bool equals(Position pos);
    Direction getDirection(Position newPos);
    bool operator == (const Position& coords);
    Direction direction(Position endPos);
};

/*
class Position {
private:
	int x;
	int y;
public:
	Position();
	Position(int x, int y);
	Position translate(Direction direction);
	int getX();
	int getY();
	int manhattanDistance(Position endPos);
	bool equals(Position pos);
	Direction getDirection(Position newPos);
};
*/


#endif //PACTEAM2_POSITION_HPP
