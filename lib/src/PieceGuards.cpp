//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include "../include/PieceGuards.h"


PieceGuards::PieceGuards(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "仕" : "士");
}


/**
 * The guards (advisors) move only one space at a time diagonally. Similar to the king,
 * the guards must stay within the palace.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceGuards::updatePosition(int8_t rank, int8_t file, Chess &chess) {
  if (abs(rank - m_curPosition.rank()) != 1 || abs(file - m_curPosition.file()) != 1)
    return false;

  if (abs(m_initPosition.rank() - rank) > 2)
    return false;
  if (abs(file - 4) > abs(m_initPosition.file() - 4))
    return false;

  return Piece::updatePosition(rank, file, chess);
}

