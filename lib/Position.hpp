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
    [[nodiscard]] Position translate(Direction direction) const;
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    void setX(int newx);
    void setY(int newy);
    [[nodiscard]] int manhattanDistance(Position endPos) const;
    [[nodiscard]] bool equals(Position pos) const;
    [[nodiscard]] Direction getDirection(Position newPos) const;
    bool operator == (const Position& coords) const;
    [[nodiscard]] Direction direction(Position endPos) const;
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
