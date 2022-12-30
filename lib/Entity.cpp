#include "Entity.hpp"
#include <iostream>

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

Entity::Entity():
        id(-1),
        nLives(-1),
        ticksPerMove(-1),
        pos(Position(-1,-1))
{
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


Position Entity::getPinkTarget()
{
    int newx = pos.getX(), newy = pos.getY();
    Position newpos;
    if(direction == 0)
    {
        newy = newy - 4;
        newpos = Position(newx,newy);
    }
    else if(direction == 1)
    {
        newy = newy + 4;
        newpos = Position(newx,newy);
    }
    else if(direction == 2)
    {
        newx = newx + 4;
        newpos = Position(newx,newy);
    }
    else if(direction == 3)
    {
        newx = newx - 4;
        newpos = Position(newx,newy);
    }

    return newpos;
}

Position Entity::getOrangeTarget()
{
    int newx = pos.getX(), newy = pos.getY();
    Position newpos;
    if(direction == 0)
    {
        newy = newy - 2;
        newpos = Position(newx,newy);
    }
    else if(direction == 1)
    {
        newy = newy + 2;
        newpos = Position(newx,newy);
    }
    else if(direction == 2)
    {
        newx = newx + 2;
        newpos = Position(newx,newy);
    }
    else if(direction == 3)
    {
        newx = newx - 2;
        newpos = Position(newx,newy);
    }

    return newpos;
}



Entity* Entity::clone() {
    return new Entity(*this);
}