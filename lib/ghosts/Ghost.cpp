#include "Ghost.hpp"
#include "../Astar.hpp"
#include <iostream>
#include <stdlib.h> //srand, rand

Ghost::Ghost(const Ghost& gh) : Entity(gh) {
    ghostId = gh.ghostId;
    mode = gh.mode;
    lastScatterTime = gh.lastScatterTime;
    lastFrightenedTime = gh.lastFrightenedTime;
    lastChaseTime = gh.lastChaseTime;
}

Ghost::Ghost(int gId, int ticksPerMove, Position pos, Direction direction, Position scatter)
        :Entity(1, ticksPerMove, pos, direction) {
    ghostId = gId;
    mode = Mode::Chase;
    scatterTarget = scatter;
    lastScatterTime = lastChaseTime = lastFrightenedTime = std::chrono::system_clock::now();
}

Ghost::~Ghost() {}

/*
* Receives the current state of the pieceBoard, and returns the next move
* for the ghost
* In this case, calls the A* algorithm, with origin in the ghost position,
* and destination in the pacman's position.
*/
Direction Ghost::getNextDirection(PieceBoard* pb, Entity* pacman, Ghost* redGhost) {
    Direction currentDirection = getDirection();
    if (mode == Mode::Frightened) {
        //return a random possible direction!
        Direction d = (Direction) (rand() % 4);
        return d;
    }
    else {
        Position previousPosition = getPosition().translate(opposite(currentDirection));
        Position endPosition = getTargetPosition(pacman, redGhost);
        Direction optimal = Astar::getOptimalDirection(pb, getPosition(), endPosition, previousPosition);
        return optimal;
    }

}

/*
* This function updates the mode of this ghost, if it is time to change his mode
*/
void Ghost::checkMode() {
    auto current_timer = std::chrono::system_clock::now();
    //when the ghost changes from chase to scatter, the direction is reversed
    if (mode == Mode::Chase) {
        std::chrono::duration<double> elapsed_seconds = current_timer - lastChaseTime;
        if (elapsed_seconds.count() >= CHASE_DURATION) {
            mode = Mode::Scatter;
            lastScatterTime = current_timer;
            reverseDirection();
        }
    } else if (mode == Mode::Scatter) {
        std::chrono::duration<double> elapsed_seconds = current_timer - lastScatterTime;
        if (elapsed_seconds.count() >= SCATTER_DURATION) {
            mode = Mode::Chase;
            lastChaseTime = current_timer;
            reverseDirection();
        }
    }
    else if (mode == Mode::Frightened) {
        std::chrono::duration<double> elapsed_seconds = current_timer - lastFrightenedTime;
        if (elapsed_seconds.count() >= FRIGHTENED_DURATION) {
            //there are two cases
            //either before frightened the ghost was in chase mode,
            //or was in scatter mode
            if (lastChaseTime > lastScatterTime) {
                mode = Mode::Chase;

                lastChaseTime +=
                        std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<double>(FRIGHTENED_DURATION));
            }
            else {
                mode = Mode::Scatter;

                lastScatterTime +=
                        std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<double>(FRIGHTENED_DURATION));
            }
        }
    }
}

void Ghost::frighten() {
    mode = Mode::Frightened;
    lastFrightenedTime = std::chrono::system_clock::now();
    reverseDirection();
}

bool Ghost::isChaseMode() {
    return mode == Mode::Chase;
}

bool Ghost::isFrightenedMode() {
    return mode == Mode::Frightened;
}

bool Ghost::isScatterMode() {
    return mode == Mode::Scatter;
}

void Ghost::reverseDirection() {
    setDirection(opposite(getDirection()));
}

Ghost* Ghost::clone() {
    return nullptr;
}

int Ghost::getGhostId() {
    return ghostId;
}