//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_PAWN_H
#define CHINESE_CHESS_PIECE_PAWN_H

#include "Piece.h"
class PiecePawn: public Piece{
public:
  PiecePawn(EnumCamp eCamp, EnumIdentity eIdentity, const Position& position);

  ~PiecePawn() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;
};


#endif //CHINESE_CHESS_PIECE_PAWN_H
