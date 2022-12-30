#include "RedGhost.hpp"

RedGhost::RedGhost(const RedGhost& g) : Ghost(g) {

}

RedGhost::RedGhost(int gId, int ticksPerMove, Position position, Direction direction, int width)
        :Ghost(gId, ticksPerMove, position, direction, Position(width,0))
{
}

Position RedGhost::getTargetPosition(Entity* pacman, Ghost* redGhost)
{
    if (isChaseMode())
    {
        return pacman->getPosition();
    }
    else if (isScatterMode())
    {
        return scatterTarget;
    }
    return Position(-1, -1);
    //the mode is scatter, this function shouldnt have been called
}

Ghost* RedGhost::clone() {
    return new RedGhost(*this);
}