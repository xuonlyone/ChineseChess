//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_PAWN_H
#define CHINESE_CHESS_PIECE_PAWN_H

#include "Piece.h"
class PiecePawn: public Piece{
public:
  PiecePawn(bool bCampRed, EnumIdentity eIdentity, const Position& position);

  ~PiecePawn() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;

  bool checking(Chess &chess) override;
};


#endif //CHINESE_CHESS_PIECE_PAWN_H
