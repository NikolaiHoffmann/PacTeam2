#include "BlueGhost.hpp"
#include <math.h>

BlueGhost::BlueGhost(const BlueGhost& g) : Ghost(g) {

}

BlueGhost::BlueGhost(int gId, int ticksPerMove, Position position, Direction direction, int width)
        :Ghost(gId, ticksPerMove, position, direction, Position(width,width))
{
}

Position BlueGhost::getTargetPosition(Entity* pacman, Ghost* redGhost)
{
    if (isChaseMode())
    {
        Position targetP = pacman->getOrangeTarget();
        Position redGhostP = redGhost->getPosition();
        int redX = redGhostP.getX();
        int redY = redGhostP.getY();

        int distance = 0;
        distance = pow(redX - (targetP.getX()), 2);
        distance += pow(redY - (targetP.getY()), 2);
        distance = sqrt(distance);
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
    return Position(-1, -1);
    //the mode is scatter, this function shouldnt have been called
}

Ghost* BlueGhost::clone(){
    return new BlueGhost(*this);
}