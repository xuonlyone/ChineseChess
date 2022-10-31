//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_GUARDS_H
#define CHINESE_CHESS_PIECE_GUARDS_H


#include "Piece.h"

class PieceGuards : public Piece{

public:
  PieceGuards(EnumCamp eCamp, EnumIdentity eIdentity, const Position& position);

  ~PieceGuards() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;
};


#endif //CHINESE_CHESS_PIECE_GUARDS_H
