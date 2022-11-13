//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_ROOK_H
#define CHINESE_CHESS_PIECE_ROOK_H

#include "Piece.h"

class PieceRook : public Piece {
public:
  PieceRook(bool bCampRed, enum EnumIdentity eIdentity, const Position& position);

  ~PieceRook() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;

  bool checking(Chess &chess) override;
};


#endif //CHINESE_CHESS_PIECE_ROOK_H
