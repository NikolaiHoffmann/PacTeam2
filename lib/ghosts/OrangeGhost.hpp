#ifndef PACTEAM2_ORANGEGHOST_HPP
#define PACTEAM2_ORANGEGHOST_HPP

#include "Ghost.hpp"

class OrangeGhost : public Ghost {
public:
    OrangeGhost(const OrangeGhost& g);
    OrangeGhost(int gId, int ticksPerMove, Position position, Direction direction, int width);
    Position getTargetPosition(Entity* pacman, Ghost* redGhost);
    virtual Ghost* clone();
};


#endif //PACTEAM2_ORANGEGHOST_HPP
