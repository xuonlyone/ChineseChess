//
// Created by xu on 2022/9/21.
//

#ifndef CHINESE_CHESS_CHESS_H
#define CHINESE_CHESS_CHESS_H

#include <vector>
#include "Board.h"
#include "Piece.h"

class Piece;

class Chess {
public:
  Chess();

  ~Chess();

  void reset();

  bool movePiece(int8_t rankSrc, int8_t fileSrc, int8_t rankDst, int8_t fileDst);

  Piece *getPiece(int8_t rank, int8_t file);

  Piece *getPiece(const Position& pos);

  Piece *getKing(bool bCampRed);

  bool checking(bool bRedTurn);

  std::vector<Piece *> &getAllPieces();

  void switchTurn();

  bool redTurn();

private:
  const static int8_t PIECE_COUNT = 16;
  Board m_board;

  bool m_redTurn;
  std::vector<Piece *> m_vecPiece;
};


#endif //CHINESE_CHESS_CHESS_H
