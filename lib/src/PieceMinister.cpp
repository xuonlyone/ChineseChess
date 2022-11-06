//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include "../include/PieceMinister.h"

PieceMinister::PieceMinister(bool bCampRed, enum EnumIdentity eIdentity, const Position& position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "相" : "象");
}


/**
 * The Ministers (Elephants) move two spaces at a time diagonally (i.e. 2 spaces left/right
 * and 2 spaces up/down in a move). They must stay within their own side of the river. If there
 * is a piece midway between the original and final intended position of a minister, the minister
 * is blocked and the move is not allowed.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceMinister::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  if (abs(rank - m_curPosition.rank()) != 2 || abs(file - m_curPosition.file()) != 2)
    return false;

  if (abs(m_initPosition.rank() - rank) > 4) //can not cross river
    return false;

  auto lameRank = static_cast<short>((rank + m_curPosition.rank()) / 2);
  auto lameFile = static_cast<short>((file + m_curPosition.file()) / 2);
  Position posLame(lameRank, lameFile);
  for (auto pPiece: vecPiece) {
    if (pPiece->state() != EnumState::live)
      continue;

    Position pos = pPiece->curPosition();
    if (m_curPosition == pos) //ignore itself
      continue;

    if (pos == posLame)
      return false;
  }

  return Piece::updatePosition(rank, file, vecPiece);
}
