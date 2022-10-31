//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_KING_H
#define CHINESE_CHESS_PIECE_KING_H

#include "Piece.h"

class PieceKing : public Piece {
public:
  PieceKing(EnumCamp eCamp, EnumIdentity eIdentity, const Position &position);

  ~PieceKing() override = default;

  bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) override;

  bool checked(std::vector<Piece *> &vecPiece);

private:
  bool checkedByPawn(std::vector<Piece *> &vecPiece);

  bool checkedByCannon(std::vector<Piece *> &vecPiece);

  bool checkedByHorse(std::vector<Piece *> &vecPiece);

  bool checkedByRook(std::vector<Piece *> &vecPiece);

  bool checkedByKing(std::vector<Piece *> &vecPiece);
};


#endif //CHINESE_CHESS_PIECE_KING_H
