//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_CANNON_H
#define CHINESE_CHESS_PIECE_CANNON_H

#include "Piece.h"

class PieceCannon : public Piece {
public:
  PieceCannon(bool bCampRed, EnumIdentity eIdentity, const Position& position);

  ~PieceCannon() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;

  bool checking(Chess &chess) override;
};


#endif //CHINESE_CHESS_PIECE_CANNON_H
