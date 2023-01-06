#include "RedGhost.hpp"

RedGhost::RedGhost(const RedGhost& g) = default;

RedGhost::RedGhost(int gId, int ticksPerMove, Position position, Direction direction, int width)
        :Ghost(gId, ticksPerMove, position, direction, Position(width,0))
{
}

/*
* Returns the target position of the red ghost, whether it is in chase
* mode, or in scatter mode.
* In chase mode, the red ghost's target tile is pacman's position.
*/
Position RedGhost::getTargetPosition(Entity* pacman)
{
    if (isChaseMode())
    {
        return pacman->getPosition();
    }
    else if (isScatterMode())
    {
        return scatterTarget;
    }
    return {-1, -1};
    //the mode is scatter, this function shouldnt have been called
}

Ghost* RedGhost::clone() {
    return new RedGhost(*this);
}