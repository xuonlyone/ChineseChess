//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_KNIGHT_H
#define CHINESE_CHESS_PIECE_KNIGHT_H

#include "Piece.h"
class PieceKnight: public Piece{

public:
  PieceKnight(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position& position);

  ~PieceKnight() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;
};


#endif //CHINESE_CHESS_PIECE_KNIGHT_H
