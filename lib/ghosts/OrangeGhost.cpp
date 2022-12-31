#include "OrangeGhost.hpp"
#include <math.h>

OrangeGhost::OrangeGhost(const OrangeGhost& g) : Ghost(g)
{
}

OrangeGhost::OrangeGhost(int gId, int ticksPerMove, Position position, Direction direction, int width)
        :Ghost(gId, ticksPerMove, position, direction, Position(0,width))
{
}

Ghost* OrangeGhost::clone(){
    return new OrangeGhost(*this);
}

Position OrangeGhost::getTargetPosition(Entity* pacman, Ghost* redGhost)
{
    if (isChaseMode())
    {
        Position ghostP = getPosition();
        Position pacmanP = pacman->getPosition();
        int ghostX = ghostP.getX();
        int ghostY = ghostP.getY();
        int pacmanX = pacmanP.getX();
        int pacmanY = pacmanP.getY();

        double distance = pow((pacmanX-ghostX)*(pacmanX-ghostX) + (pacmanY-ghostY)*(pacmanY-ghostY), 0.5f);

        if(distance <= 8)
        {
            return scatterTarget;
        }
        else
        {
            return pacman->getPosition();
        }
    }
    else if (isScatterMode())
    {
        return scatterTarget;
    }
    return Position(-1, -1);
    //the mode is scatter, this function shouldnt have been called
}
