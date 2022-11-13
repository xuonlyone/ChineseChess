//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_KING_H
#define CHINESE_CHESS_PIECE_KING_H

#include "Piece.h"


class PieceKing : public Piece {
public:
  PieceKing(bool bCampRed, EnumIdentity eIdentity, const Position &position);

  ~PieceKing() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;

  bool checking(Chess &chess) override;

//  bool checked(Chess &chess);

private:
//  bool checkedByPawn(Chess &chess);
//
//  bool checkedByCannon(Chess &chess);
//
//  bool checkedByKnight(Chess &chess);
//
//  bool checkedByRook(Chess &chess);
//
//  bool checkPositionOfRook(Chess &chess);
//
//  bool checkedByKing(Chess &chess);

};


#endif //CHINESE_CHESS_PIECE_KING_H
