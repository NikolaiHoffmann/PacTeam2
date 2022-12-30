#ifndef PACTEAM2_PINKGHOST_HPP
#define PACTEAM2_PINKGHOST_HPP

#include "Ghost.hpp"

class PinkGhost: public Ghost {
public:
    PinkGhost(const PinkGhost& g);
    PinkGhost(int gId, int ticksPerMove, Position position, Direction direction);
    Position getTargetPosition(Entity* pacman, Ghost* redGhost);
    virtual Ghost* clone();
};

#endif //PACTEAM2_PINKGHOST_HPP
