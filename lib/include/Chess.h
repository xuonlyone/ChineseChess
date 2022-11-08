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

  bool movePiece(short rankSrc, short fileSrc, short rankDst, short fileDst);

  Piece *getPiece(short rank, short file);

  Piece *getPiece(const Position& pos);

  Piece *getKing(bool bCampRed);

  bool checking();

  std::vector<Piece *> &getAllPieces();

private:
  const static short PIECE_COUNT = 16;
  Board m_board;

  bool m_redTurn;
  std::vector<Piece *> m_vecPiece;
};


#endif //CHINESE_CHESS_CHESS_H
