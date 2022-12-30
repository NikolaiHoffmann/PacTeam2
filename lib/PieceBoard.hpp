#ifndef PACTEAM2_PIECEBOARD_HPP
#define PACTEAM2_PIECEBOARD_HPP

#include "Position.hpp"

enum Piece { Wall = 0, Food, BigFood, Empty };

class PieceBoard {
private:
    int width;
    int height;
    Piece* board; //matrix of Pieces
    bool* intersectionBoard;
    char pieceRepresentation[4];
    Piece getPiece(Position pos);
    void setPiece(Position pos, Piece piece);
public:
    PieceBoard(const PieceBoard& pb);
    PieceBoard(int w, int h);
    int getIndex(Position position);
    void setWall(Position pos);
    void setBigFood(Position pos);
    void setSmallFood(Position pos);
    void setEmpty(Position pos);
    char* getRepresentation();
    bool isPiece(Position pos, Piece p);
    bool isWall(Position position);
    bool isBigFood(Position pos);
    bool isInvalid(Position position);
    void generateIntersectionBoard();
    bool isIntersection(Position pos);
    bool isDeadEnd(Position pos);
    bool isStraightTunel(Position pos);
    bool isCurveTunel(Position pos);
    PieceBoard* clone();
};


#endif //PACTEAM2_PIECEBOARD_HPP
