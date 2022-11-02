//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_KING_H
#define CHINESE_CHESS_PIECE_KING_H

#include "Piece.h"
#include "Chess.h"


class PieceKing : public Piece {
public:
  PieceKing(EnumCamp eCamp, EnumIdentity eIdentity, const Position &position);

  ~PieceKing() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;

  bool checked(Chess &chess);

private:
  bool checkedByPawn(Chess &chess);

  bool checkedByCannon(Chess &chess);

  bool checkedByHorse(Chess &chess);

  bool checkedByRook(Chess &chess);

  bool checkedByKing(Chess &chess);
};


#endif //CHINESE_CHESS_PIECE_KING_H
