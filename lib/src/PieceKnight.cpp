//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include "../include/PieceKnight.h"

PieceKnight::PieceKnight(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position& position)
    : Piece(eCamp, eIdentity, position) {
  m_name = (m_eCamp == EnumCamp::red ? "傌" : "馬");
}


/**
 * The Knights (Horses) move two spaces horizontally and one space vertically (or respectively 2
 * spaces vertically and one space horizontally). If there is a piece next to the knight
 * in the horizontal (vertical) direction, the knight is blocked and the move is not allowed.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceKnight::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  unsigned val1 = abs(rank - m_curPosition.rank());
  unsigned val2 = abs(file - m_curPosition.file());

  if (!((val1 + val2 == 3) && (val1 != 0) && (val2 != 0)))
    return false;

  //consider the lame horse
  if (val1 > val2) {
    auto lame = (rank + m_curPosition.rank()) / 2;
    for (auto pPiece: vecPiece) {
      Position pos = pPiece->curPosition();
      if (m_curPosition == pos)
        continue;

      if (lame == pos.rank() && m_curPosition.file() == pos.file())
        return false;
    }
  } else {
    auto lame = (file + m_curPosition.file()) / 2;
    for (auto pPiece: vecPiece) {
      Position pos = pPiece->curPosition();
      if (m_curPosition == pos) //ignore itself
        continue;;

      if (lame == pos.file() && m_curPosition.rank() == pos.rank())
        return false;
    }
  }

  return Piece::updatePosition(rank, file, vecPiece);
}
