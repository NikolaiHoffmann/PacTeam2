#include "Entity.hpp"
#include <iostream>

/*
* Entity clone constructor
*/
Entity::Entity(const Entity& ent) {
    id = ent.id;
    nLives = ent.nLives;
    ticksPerMove = ent.ticksPerMove;
    pos = ent.pos;
    direction = ent.direction;
}

Entity::Entity(int nLives, int ticksPerMove, Position pos, Direction direction):
        nLives(nLives),
        ticksPerMove(ticksPerMove),
        pos(pos),
        direction(direction)
{
}

Entity::~Entity() {
}

int Entity::getId() {
    return id;
}

Direction Entity::getDirection() {
    return direction;
}

Position Entity::getPosition() {
    return pos;
}

void Entity::setPosition(Position position) {
    pos = position;
}

void Entity::setDirection(Direction newDirection) {
    direction = newDirection;
}

void Entity::print() {
    std::cout << id << "," << nLives << ",(" << pos.getX() << "," << pos.getY() << ")" << std::endl;
}

/*
* Returns the position of the pink ghost's target when it is in chase mode
*/
Position Entity::getPinkTarget()
{
    int newx = pos.getX(), newy = pos.getY();
    Position newpos;
    switch (direction) {
    case (Up):
        newy = newy - 4;
        break;
    case (Down):
        newy = newy + 4;
        break;
    case (Right):
        newx = newx + 4;
        break;
    case (Left):
        newx = newx - 4;
        break;
    case (Null):
        break;
    }
    
    newpos = Position(newx, newy);

    return newpos;
}

/*
* Returns the position of the orange ghost's target when it is in chase mode
*/
Position Entity::getOrangeTarget()
{
    int newx = pos.getX(), newy = pos.getY();
    switch (direction) {
    case (Up):
        newy = newy - 2;
        break;
    case (Down):
        newy = newy + 2;
        break;
    case (Right):
        newx = newx + 2;
        break;
    case (Left):
        newx = newx - 2;
        break;
    case (Null):
        break;
    }
    Position newpos = Position(newx, newy);

    return newpos;
}

Entity* Entity::clone() {
    return new Entity(*this);
}