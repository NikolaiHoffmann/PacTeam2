#include "PinkGhost.hpp"

PinkGhost::PinkGhost(const PinkGhost& g) : Ghost(g) {

}

PinkGhost::PinkGhost(int gId, int ticksPerMove, Position position, Direction direction)
        :Ghost(gId, ticksPerMove, position, direction, Position(0,0))
{
}

/*
* Returns the target position of the pink ghost, whether it is in chase
* mode, or in scatter mode.
*/
Position PinkGhost::getTargetPosition(Entity* pacman, Ghost* redGhost)
{
    if (isChaseMode())
    {
        return pacman->getPinkTarget();
    }
    else if (isScatterMode())
    {
        return scatterTarget;
    }
    return Position(-1, -1);
    //the mode is scatter, this function shouldnt have been called
}

Ghost* PinkGhost::clone() {
    return new PinkGhost(*this);
}