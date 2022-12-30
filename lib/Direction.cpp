#include "Direction.hpp"

Direction opposite(Direction direction) {
    Direction dir;
    switch (direction) {
        case Up:
            dir = Down;
            break;
        case Down:
            dir = Up;
            break;
        case Left:
            dir = Right;
            break;
        case Right:
            dir = Left;
            break;
        case Null:
            dir = Null;
    }
    return dir;
}