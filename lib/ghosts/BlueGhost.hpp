#ifndef PACTEAM2_BLUEGHOST_HPP
#define PACTEAM2_BLUEGHOST_HPP

#include "Ghost.hpp"

class BlueGhost: public Ghost {
public:
    BlueGhost(const BlueGhost& g);
    BlueGhost(int gId, int ticksPerMove, Position position, Direction direction, int width);
    Position getTargetPosition(Entity* pacman, Ghost* redGhost);
    virtual Ghost* clone();
};


#endif //PACTEAM2_BLUEGHOST_HPP
