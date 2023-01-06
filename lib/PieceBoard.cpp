#include "PieceBoard.hpp"

PieceBoard::PieceBoard(const PieceBoard& pb) : pieceRepresentation{ '#', '.', 'o', ' ' } {
    width = pb.width;
    height = pb.height;
    int size = width * height;
    board = new Piece[size];
    for (int i = 0; i < size; i++) {
        board[i] = pb.board[i];
    }
    generateIntersectionBoard();
}

PieceBoard::PieceBoard(int w, int h) : pieceRepresentation{ '#', '.', 'o', ' ' } {
    width = w;
    height = h;
    //board = (Piece*)malloc(width * height * sizeof(Piece)); //we malloc the array with required space
    board = new Piece[width * height];
    intersectionBoard = nullptr;
}

PieceBoard::~PieceBoard() {
    delete[] board;
    delete[] intersectionBoard;
}

void PieceBoard::setPiece(Position pos, Piece piece) {
    board[getIndex(pos)] = piece;
}

Piece PieceBoard::getPiece(Position pos) {
    return board[getIndex(pos)];
}

void PieceBoard::setWall(Position pos) {
    setPiece(pos, Wall);
}

void PieceBoard::setBigFood(Position pos) {
    setPiece(pos, BigFood);
}

void PieceBoard::setSmallFood(Position pos) {
    setPiece(pos, Food);
}

void PieceBoard::setEmpty(Position pos) {
    setPiece(pos, Empty);
}

int PieceBoard::getIndex(Position position) const {
    return position.getY() * width + position.getX();
}

std::string PieceBoard::getRepresentation() {
    //char* representation = (char*)malloc(width * height * sizeof(char));
    //std::string representation = std::string(width * height, ' ');
    std::string representation;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int currentIndex = j * height + i;
            Piece piece = board[currentIndex];
            //representation[currentIndex] = pieceRepresentation[piece];
            representation.push_back(pieceRepresentation[piece]);
        }
    }
    return representation;
}

bool PieceBoard::isPiece(Position pos, Piece p) {
    int index = getIndex(pos);
    return board[index] == p;
}

bool PieceBoard::isWall(Position position) {
    int index = getIndex(position);
    return board[index] == Wall;
}

bool PieceBoard::isBigFood(Position position) {
    int index = getIndex(position);
    return board[index] == BigFood;
}

bool PieceBoard::isAnyFood(Position position) {
    int index = getIndex(position);
    return board[index] == BigFood || board[index] == Food;
}

bool PieceBoard::isInvalid(Position position) {
    int x = position.getX();
    int y = position.getY();
    return isWall(position) || x > width || x < 0 || y > height || y < 0;
}

void PieceBoard::generateIntersectionBoard() {
    //intersectionBoard = (bool*)malloc(width * height * sizeof(bool));
    intersectionBoard = new bool[width * height];
    int currentIndex = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (board[currentIndex] != Wall) {
                Piece up = getPiece(Position(x, y - 1));
                Piece down = getPiece(Position(x, y + 1));
                Piece left = getPiece(Position(x-1, y));
                Piece right = getPiece(Position(x+1, y));
                if ((up != Wall) + (down != Wall) + (left != Wall) + (right != Wall) >= 3) {
                    //then we are in an intersection
                    if(intersectionBoard) intersectionBoard[currentIndex] = true;
                }
                else {
                    if(intersectionBoard) intersectionBoard[currentIndex] = false;
                }
            } else {
                if(intersectionBoard) intersectionBoard[currentIndex] = false;
            }
            currentIndex++;
        }
    }
    /*
    * TEST TO CHECK IF INTERSECTION BOARD IS WORKING PROPERLY
    * currentIndex = 0;
    char* rep = getRepresentation();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (intersectionBoard[currentIndex]) rep[currentIndex] = 'X';
            currentIndex++;
        }
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int currentIndex = j * height + i;
            std::cout << rep[currentIndex];
        }
        std::cout << std::endl;
    }
    free(rep);
    */

}

bool PieceBoard::isIntersection(Position pos) {
    bool iB = false;
    if(intersectionBoard) iB = intersectionBoard[getIndex(pos)];
    return iB; //if true, the position is an intersection

}

/*
* Returns true if the given position is a dead end
* Dead ends are like ####
*					   M#
*					 ####
*/
bool PieceBoard::isDeadEnd(Position pos) {
    Position up = pos.translate(Direction::Up);
    Position down = pos.translate(Direction::Down);
    Position left = pos.translate(Direction::Left);
    Position right = pos.translate(Direction::Right);
    int isWallSum = isWall(up) + isWall(down) + isWall(left) + isWall(right);
    return isWallSum == 3;
}

bool PieceBoard::isStraightTunel(Position pos) {
    Position up = pos.translate(Direction::Up);
    Position down = pos.translate(Direction::Down);
    Position left = pos.translate(Direction::Left);
    Position right = pos.translate(Direction::Right);
    return ((isWall(up) && isWall(down) && !isWall(left) && !isWall(right)) || (isWall(left) && isWall(right) && !isWall(up) && !isWall(down)));
    //this position is not an intersection, therefore it is a tunnel,
    //and has two walls, either above and below, or to the right and to the left.
}

bool PieceBoard::isCurveTunel(Position pos) {
    Position up = pos.translate(Direction::Up);
    Position down = pos.translate(Direction::Down);
    Position left = pos.translate(Direction::Left);
    Position right = pos.translate(Direction::Right);
    return !isIntersection(pos) && (!(isWall(up) && isWall(down)) && !(isWall(left) && isWall(right)));
}

PieceBoard* PieceBoard::clone() {
    return new PieceBoard(*this);
}