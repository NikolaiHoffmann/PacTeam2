#ifndef PACTEAM2_BLUEGHOST_HPP
#define PACTEAM2_BLUEGHOST_HPP

#include "Ghost.hpp"
#include "RedGhost.hpp"

class BlueGhost: public Ghost {
private:
    Ghost* redGhost;
public:
    BlueGhost(const BlueGhost& g);
    BlueGhost(int gId, int ticksPerMove, Position position, Direction direction, int width, Ghost* redGhost);
    //virtual ~Ghost();
    Position getTargetPosition(Entity* pacman) final;
    Ghost* clone() final;
    [[nodiscard]] Ghost* getRedGhost() const;
};


#endif //PACTEAM2_BLUEGHOST_HPP
