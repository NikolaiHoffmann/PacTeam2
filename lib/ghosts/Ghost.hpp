#ifndef PACTEAM2_GHOST_HPP
#define PACTEAM2_GHOST_HPP

#include "../Entity.hpp"
#include "../PieceBoard.hpp"
#include <chrono>

#define FRIGHTENED_DURATION 3.0
#define SCATTER_DURATION 7.0
#define CHASE_DURATION 20.0

enum Mode {Chase, Scatter, Frightened};

/*
* Instances of class Ghost can't be instantiated, because there is an abstract method!
* Only classes that define this method can be instantiated.
*/
class Ghost : public Entity {
private:
    int ghostId;
    Mode mode;
    //position of the target of the ghosts when they're in scatter mode
    std::chrono::time_point<std::chrono::system_clock> lastScatterTime, lastFrightenedTime, lastChaseTime;
public:
    Ghost(const Ghost& gh);
    Ghost(int gId, int ticksPerMove, Position pos, Direction direction, Position scatter);
    Direction getNextDirection(PieceBoard* pb, Entity* pacman, Ghost* redGhost);
    virtual Position getTargetPosition(Entity* pacman, Ghost* redGhost) = 0;
    void checkMode();
    void frighten();
    bool isChaseMode();
    bool isFrightenedMode();
    bool isScatterMode();
    void reverseDirection();
    virtual Ghost* clone(); //maybe needs change
protected:
    Position scatterTarget;
};

#endif //PACTEAM2_GHOST_HPP
