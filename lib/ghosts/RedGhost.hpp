#ifndef PACTEAM2_REDGHOST_HPP
#define PACTEAM2_REDGHOST_HPP

#include "Ghost.hpp"

class RedGhost: public Ghost {
public:
    RedGhost(const RedGhost& g);
    RedGhost(int gId, int ticksPerMove, Position position, Direction direction, int width);
    Position getTargetPosition(Entity* pacman, Ghost* redGhost);
    virtual Ghost* clone();
};


#endif //PACTEAM2_REDGHOST_HPP
