#include "BlueGhost.hpp"
#include <cmath>

BlueGhost::BlueGhost(const BlueGhost& g) : Ghost(g), redGhost(g.getRedGhost()) {
}

BlueGhost::BlueGhost(int gId, int ticksPerMove, Position position, Direction direction, int width, Ghost* redGhost)
        :Ghost(gId, ticksPerMove, position, direction, Position(width,width)), redGhost(redGhost)
{
}

/*
* Returns the target position of the blue ghost, whether it is in chase
* mode, or in scatter mode.
*/
Position BlueGhost::getTargetPosition(Entity* pacman)
{
    if (isChaseMode())
    {
        Position targetP = pacman->getOrangeTarget();
        Position redGhostP = redGhost->getPosition();
        int redX = redGhostP.getX();
        int redY = redGhostP.getY();

        int distance;
        distance = static_cast<int>(pow(redX - (targetP.getX()), 2));
        distance += static_cast<int>(pow(redY - (targetP.getY()), 2));
        distance = static_cast<int>(sqrt(distance));
        distance /= 2;

        int newx = targetP.getX();
        int newy = targetP.getY();

        targetP.setX(newx+distance);
        targetP.setY(newy+distance);

        //TODO return pacman->getBlueTarget();
    }
    else if (isScatterMode())
    {
        return scatterTarget;
    }
    return {-1, -1};
    //the mode is scatter, this function shouldnt have been called
}

Ghost* BlueGhost::clone(){
    return new BlueGhost(*this);
}

Ghost* BlueGhost::getRedGhost() const {
    return redGhost;
}
