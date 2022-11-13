//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_MINISTER_H
#define CHINESE_CHESS_PIECE_MINISTER_H

#include "Piece.h"

class PieceMinister : public Piece {
public:
  PieceMinister(bool bCampRed, enum EnumIdentity eIdentity, const Position& position);

  ~PieceMinister() override = default;

  bool updatePosition(int8_t rank, int8_t file, Chess &chess) override;
};


#endif //CHINESE_CHESS_PIECE_MINISTER_H
