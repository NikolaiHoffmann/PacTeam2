#include "Board.hpp"
#include "PieceBoard.hpp"
#include "ghosts/Ghost.hpp"
#include "ghosts/RedGhost.hpp"
#include "ghosts/PinkGhost.hpp"
#include "ghosts/BlueGhost.hpp"
#include "ghosts/OrangeGhost.hpp"
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*
* Board clone constructor
*/
Board::Board(const Board& board) {
    width = board.width;
    height = board.height;
    pieceBoard = board.pieceBoard->clone();
    player = board.player->clone();
    points = board.points;
    pacmanStartingPos = board.pacmanStartingPos;
    gameOver = board.gameOver;
    foodCount = board.foodCount;
    currentGameTick = board.currentGameTick;
    pacmanDeaths = board.pacmanDeaths;
    for (int i = 0; i < 4; i++) {
        Ghost* currGhost = board.ghosts[i];
        ghosts[i] = currGhost->clone();
        ghostsStartingPos[i] = board.ghostsStartingPos[i];
    }
}

/*
* Creates a Board object, given the path to the map
*/
Board::Board(string path) {
    int currentGhostId = 0;
    currentGameTick = 0;
    gameOver = false;
    pacmanDeaths = 0;
    foodCount = 0; //initially, 0 foods have been read
    ifstream map(path); //input file stream from path to the map text file
    if (!map) {
        //couldnt open file
        cout << "File not found! File: " << path << endl;
    }
    string currentLine;
    getline(map, currentLine);
    istringstream iss(currentLine);
    points = 0; //pacman starts with 0 points
    /*
    * First line of file is width and height of map
    * So first we get these values from the files and put in variables width and height
    */
    iss >> width >> height; //set width and height parameters
    pieceBoard = new PieceBoard(width, height);
    for (int j = 0; j < height; j++) {
        getline(map, currentLine);
        for (int i = 0; i < width; i++) {
            //for each character in the map file, we are going to analyse it
            Position position = Position(i, j);
            if (currentLine[i] == '#') {
                //we set the corresponding position in pieceBoard object as a wall
                pieceBoard->setWall(position);
            } else if (currentLine[i] == 'o') {
                //we set the corresponding position in pieceBoard object as a big food
                foodCount++;
                pieceBoard->setBigFood(position);
            } else if (currentLine[i] == '.') {
                //we set the corresponding position in pieceBoard object as a small food
                foodCount++;
                pieceBoard->setSmallFood(position);
            } else if (currentLine[i] == ' ') {
                //we set the corresponding position in pieceBoard object as empty
                pieceBoard->setEmpty(position);
            } else if (currentLine[i] == 'R') {
                //we set the red ghost
                pieceBoard->setEmpty(position);
                Ghost* ghost = new RedGhost(currentGhostId, 2, Position(i, j), Direction::Right, width);
                ghosts[currentGhostId] = ghost;
                ghostsStartingPos[currentGhostId] = ghost->getPosition();
                currentGhostId++;
            } else if (currentLine[i] == 'P') {
                //we set the pink ghost
                pieceBoard->setEmpty(position);
                Ghost* ghost = new PinkGhost(currentGhostId, 2, Position(i, j), Direction::Right);
                ghosts[currentGhostId] = ghost;
                ghostsStartingPos[currentGhostId] = ghost->getPosition();
                currentGhostId++;
            } else if (currentLine[i] == 'B') {
                //we set the blue ghost
                pieceBoard->setEmpty(position);
                Ghost* ghost = new BlueGhost(currentGhostId, 2, Position(i, j), Direction::Right, width);
                ghosts[currentGhostId] = ghost;
                ghostsStartingPos[currentGhostId] = ghost->getPosition();
                currentGhostId++;
            } else if (currentLine[i] == 'O') {
                //we set the orange ghost
                pieceBoard->setEmpty(position);
                Ghost* ghost = new OrangeGhost(currentGhostId, 2, Position(i, j), Direction::Right, width);
                ghosts[currentGhostId] = ghost;
                ghostsStartingPos[currentGhostId] = ghost->getPosition();
                currentGhostId++;
            } else if (currentLine[i] == '{') {
                //we set the pacman
                pieceBoard->setEmpty(position);
                player = new Entity(3, 1, Position(i, j), Direction::Right);
                pacmanStartingPos = player->getPosition();
            }
        }
    }
    //we generate the intersection board
    //intersection board contains information on whether each position is
    // a tunnel or an intersection. this is important for ghosts movement
    pieceBoard->generateIntersectionBoard();
}

/*
* Board destructor
*/
Board::~Board() {
    delete pieceBoard;
    delete player;
    for (int i = 0; i < 4; i++) {
        delete ghosts[i];
    }
}

void Board::printBoard() {
    std::string representation = pieceBoard->getRepresentation();

    Position playerPosition = player->getPosition ();
    //we set pacman representation as character 'X'
    representation[pieceBoard->getIndex(playerPosition)] = 'X';

    for (int j = 0; j < 4; j++)
    {
        Ghost* ghost = ghosts[j];
        Position ghostPosition = ghosts[j]->getPosition();
        if (ghost->isFrightenedMode()) {
            //if the ghost is in frightened mode, it is represented
            // as the character '?'
            representation[pieceBoard->getIndex(ghostPosition)] = '?';
        }
        else {
            if (j == 0) { representation[pieceBoard->getIndex(ghostPosition)] = 'R'; }
            else if (j == 1) { representation[pieceBoard->getIndex(ghostPosition)] = 'B'; }
            else if (j == 2) { representation[pieceBoard->getIndex(ghostPosition)] = 'O'; }
            else if (j == 3) { representation[pieceBoard->getIndex(ghostPosition)] = 'P'; }
        }
        
    }

    //print out the representation
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int currentIndex = j * height + i;
            cout << representation[currentIndex];
        }
        cout << endl;
    }
    cout << "Deaths: " << pacmanDeaths << endl;
    cout << "Points: " << points << endl << endl;
}

/*
* If the next position isn't a wall, moves the player in the current direction,
* eating the next piece (if there is)
*/
void Board::movePlayer() {
    Direction currentDirection = player->getDirection();
    Position currentPosition = player->getPosition();
    Position newPosition = currentPosition.translate(currentDirection);

    points--; //time penalty so that agents prioritize ending the game quicker
    if (!pieceBoard->isWall(newPosition)) {
        if (pieceBoard->isAnyFood(newPosition)) {
            if (foodCount == 1) {
                //in this case, pacman eats the last food, and the game ends
                //we add 5000 points so that the agent always go for this state, if it
                // is in range
                gameOver = true;
                points += 5000;
            }

            if (pieceBoard->isBigFood(newPosition)) {
                //if it is a big food, we set all the ghost's modes to Frightened.
                // and we increase points by a lot
                for (int i = 0; i < 4; i++) {
                    if (ghosts[i] == nullptr) {
                        std::cout << "invalid ghost" << std::endl;
                    }
                    ghosts[i]->frighten();
                }
                points += 200;
            } else points += 10;
            foodCount--;
        }
        
        //set pacman's position to the new position
        player->setPosition(newPosition);
        Ghost* g;
        if (g = collisionGhosts(newPosition)) {
            //if there is a collision and the ghost is not frightened, the ghost eats pacman
            //otherwise pacman eats ghost
            if (g->isFrightenedMode()) pacmanEatGhost(g);
            else ghostEatPacman();
        }
        pieceBoard->setEmpty(newPosition);
    }
}

/*
* If the next position isn't a wall, moves the ghost in the current direction
*/
void Board::moveGhost(int ghostId) {
    Ghost* ghost = ghosts[ghostId];
    Direction currentDirection = ghost->getDirection();
    Position currentPosition = ghost->getPosition();
    Position newPosition = currentPosition.translate(currentDirection);
    if (!pieceBoard->isWall(newPosition)) {
        //if next position isnt a wall, update ghost position to this next position
        ghost->setPosition(newPosition);
        if (newPosition.equals(player->getPosition())) {
            //if there is a collision and the ghost is not frightened, the ghost eats pacman
            //otherwise pacman eats ghost
            if (ghost->isFrightenedMode()) pacmanEatGhost(ghost);
            else ghostEatPacman();
        }
    }
}

/*
* Change the player's direction to the given direction
*/
void Board::changePlayerDirection(Direction newDirection) {
    Position nextPosition = player->getPosition().translate(newDirection);
    if (!pieceBoard->isWall(nextPosition)) {
        player->setDirection(newDirection);
    }
}

/*
* Change the given ghost's direction to the given direction
*/
void Board::changeGhostDirection(int ghostId, Direction newDirection) {
    ghosts[ghostId]->setDirection(newDirection);
}

/*
* Updates the position of every ghost
*/
void Board::updateGhosts() {

    for (int ghostId = 0; ghostId < 4; ghostId++) {
        Ghost* ghost = ghosts[ghostId];
        //in frightened mode, ghosts move every two game ticks (half speed)
        //therefore, we check if the current ghost is in frightened mode,
        //and if the currentGameTick is even. In this case we dont update the ghost
        if (ghost->isFrightenedMode() && currentGameTick % 2 == 0) continue;
        Ghost* redGhost = ghosts[0];
        //we update the ghost's mode
        ghost->checkMode();
        Position ghostPos = ghost->getPosition();
        if (pieceBoard->isIntersection(ghostPos)) {
            /*
            * ghost is in an intersection
            * intersections have 3 or more surrounding squares
            */
            //we get the next direction of this ghost
            Direction newDirection = ghost->getNextDirection(pieceBoard, player, redGhost);
            ghost->setDirection(newDirection);
        } else if (pieceBoard->isDeadEnd(ghostPos)) {
            /*
            * In case of dead end, reverse the direction of the ghost
            */
            ghost->setDirection(opposite(ghost->getDirection()));
        } else {
            Direction currentDirection = ghost->getDirection();
            Position forwardPos = ghostPos.translate(currentDirection);
            if (!pieceBoard->isWall(forwardPos)) {
                //if the next position isnt a wall, we dont change the direction
            }
            else if (pieceBoard->isDeadEnd(ghostPos)) {
                /*
                * In case of dead end, reverse the direction of the ghost
                */
                ghost->setDirection(opposite(ghost->getDirection()));
            } else {
                //here ghosts are in tunnel type 1 or 2, and they're facing a wall
                setCurveDirection(ghost);
            }

            /*
            *
            * tunnels can be of type 1  # #   or of type 2  # #
            *						    #M#			        #M
            *						    # #			        ###
            *
            */
            
        }
        //we move the ghost in the current direction (direction was updates above)
        moveGhost(ghostId);
    }
}

/*
* This function gets as input an entity that is assumed to be in a curved tunnel, and
* sets the direction of the entity to the direction that doesn't have a wall, in order
* for the entity to keep moving
*/
void Board::setCurveDirection(Ghost* ghost) {
    //Assuming we are in a curve tunnel, this function gets as input the entity that is in a
    // type 2 tunnel, and retrieves the
    Position currentPosition = ghost->getPosition();
    Direction currentDirection = ghost->getDirection();
    //if the piece in the current direction isnt a wall, we dont change the direction
    Direction adjacent1, adjacent2;
    /*
    * If the entity's current direction is up or down, the positions to check are to the left
    * and to the right, and vice-versa.
    */
    if (currentDirection == Direction::Up || currentDirection == Direction::Down) {
        adjacent1 = Direction::Left;
        adjacent2 = Direction::Right;
    }
    else {
        adjacent1 = Direction::Up;
        adjacent2 = Direction::Down;
    }

    Position pos1 = currentPosition.translate(adjacent1);
    if (pieceBoard->isWall(pos1)) ghost->setDirection(adjacent2);
    else ghost->setDirection(adjacent1);
}

Board* Board::clone() {
    return new Board(*this);
}

/*
* Returns a vector with every possible state coming from pacman
* moving to any possible direction
*/
std::vector<Board*> Board::getPacmanChildStates() {
    std::vector<Board*> possibleStates;
    std::vector<Direction> possibleDirections;
    Position pacmanPos = player->getPosition();
    for (int i = 0; i < 4; i++) {
        Direction currentDirection = (Direction)i;
        Position newPos = pacmanPos.translate(currentDirection);
        if (!pieceBoard->isWall(newPos)) {
            possibleDirections.push_back(currentDirection);
        }
    }
    //at this point, possibleDirections contains all possible directions to move
    //directions in which the next position isnt a wall
    std::vector<Direction>::iterator it = possibleDirections.begin();
    for (; it != possibleDirections.end(); ++it) {
        //for each possible direction, we clone the current state,
        //and we move the pacman in the cloned state to the current direction.
        Direction currentDirection = *it;
        Board* newState = this->clone();
        newState->changePlayerDirection(currentDirection);
        newState->movePlayer();
        possibleStates.push_back(newState);
    }
    return possibleStates;
}

/*
* Returns a vector with every possible state coming from ghosts
* moving to any possible direction
* At this point, it is just returning the state where the ghosts are moving next
*/
std::vector<Board*> Board::getGhostsChildStates() {
    std::vector<Board*> possibleStates;
    Board* newState = this->clone();
    newState->updateGhosts();
    possibleStates.push_back(newState);
    return possibleStates;
}

Entity* Board::getPacman() {
    return player;
}

PieceBoard* Board::getPieceBoard() {
    return pieceBoard;
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

int Board::getPoints() {
    return points;
}

/*
* Returns a ghost if pacman is in the same position as him.
* Otherwise returns the null pointer.
*/
Ghost* Board::collisionGhosts(Position pos) {
    for (int i = 0; i < 4; i++) {
        Position posGhost = ghosts[i]->getPosition();
        if (pos.equals(posGhost)) return ghosts[i];
    }
    return nullptr;
}

/*
* Ghost eats Pacman. In this case we increase death count, we decrease the points,
* and we reset pacman's position to the initial position
* We also reset the ghosts' positions
*/
void Board::ghostEatPacman() {
    pacmanDeaths += 1;
    points -= 500;
    player->setPosition(pacmanStartingPos);
    for (int i = 0; i < 4; i++) {
        ghosts[i]->setPosition(ghostsStartingPos[i]);
    }
}

/*
* Pacman eats a Ghost. In this case we increase the points and we set the ghost's position
* to his starting position
*/
void Board::pacmanEatGhost(Ghost* g) {
    points += 500;
    g->setPosition(ghostsStartingPos[g->getGhostId()]);
}

bool Board::isGameOver() {
    return gameOver;
}

void Board::increaseGameTick() {
    currentGameTick++;
}

int Board::getGameTick() {
    return currentGameTick;
}