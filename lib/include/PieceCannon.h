//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_CANNON_H
#define CHINESE_CHESS_PIECE_CANNON_H

#include "Piece.h"

class PieceCannon : public Piece {
public:
  PieceCannon(EnumCamp eCamp, EnumIdentity eIdentity, const Position& position);

  ~PieceCannon() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;
};


#endif //CHINESE_CHESS_PIECE_CANNON_H
