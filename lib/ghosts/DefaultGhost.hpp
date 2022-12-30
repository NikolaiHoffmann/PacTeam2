#ifndef PACTEAM2_DEFAULTGHOST_HPP
#define PACTEAM2_DEFAULTGHOST_HPP

#include "Ghost.hpp"

class DefaultGhost : public Ghost {
public:
    DefaultGhost(const DefaultGhost& g);
    DefaultGhost(int gId, int ticksPerMove, Position pos, Direction direction);
    Position getTargetPosition(Entity* pacman);
    virtual Ghost* clone();
};


#endif //PACTEAM2_DEFAULTGHOST_HPP
