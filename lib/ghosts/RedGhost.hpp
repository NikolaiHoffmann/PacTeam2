#ifndef PACTEAM2_REDGHOST_HPP
#define PACTEAM2_REDGHOST_HPP

#include "Ghost.hpp"

class RedGhost: public Ghost {
public:
    RedGhost(const RedGhost& g);
    RedGhost(int gId, int ticksPerMove, Position position, Direction direction, int width);
    Position getTargetPosition(Entity* pacman) final;
    Ghost* clone() final;
};


#endif //PACTEAM2_REDGHOST_HPP
