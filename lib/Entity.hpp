#ifndef PACTEAM2_ENTITY_HPP
#define PACTEAM2_ENTITY_HPP

#include "Position.hpp"
#include "Direction.hpp"

class Entity {
private:
    //int id; //unique id of entity
    int nLives; //number of lives
    int ticksPerMove;
    Position pos;
    Direction direction;
public:
    Entity(const Entity& ent);
    Entity(int nLives, int ticksPerMove, Position pos, Direction direction);
    virtual ~Entity();
    // [[nodiscard]] int getId() const;
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] Position getPosition() const;
    [[nodiscard]] Position getPinkTarget() const;
    [[nodiscard]] Position getOrangeTarget() const;
    void setPosition(Position position);
    void setDirection(Direction newDirection);
    void print() const;
    virtual Entity* clone();
};

#endif //PACTEAM2_ENTITY_HPP
