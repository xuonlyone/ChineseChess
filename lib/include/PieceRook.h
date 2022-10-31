//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_ROOK_H
#define CHINESE_CHESS_PIECE_ROOK_H

#include "Piece.h"

class PieceRook : public Piece {
public:
  PieceRook(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position& position);

  ~PieceRook() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;

};


#endif //CHINESE_CHESS_PIECE_ROOK_H
