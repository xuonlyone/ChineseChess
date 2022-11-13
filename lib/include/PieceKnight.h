//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_KNIGHT_H
#define CHINESE_CHESS_PIECE_KNIGHT_H

#include "Piece.h"
class PieceKnight: public Piece{

public:
  PieceKnight(bool bCampRed, enum EnumIdentity eIdentity, const Position& position);

  ~PieceKnight() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;

  bool checking(Chess &chess) override;
};


#endif //CHINESE_CHESS_PIECE_KNIGHT_H
