//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_GUARDS_H
#define CHINESE_CHESS_PIECE_GUARDS_H


#include "Piece.h"

class PieceGuards : public Piece{

public:
  PieceGuards(bool bCampRed, EnumIdentity eIdentity, const Position& position);

  ~PieceGuards() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;
};


#endif //CHINESE_CHESS_PIECE_GUARDS_H
