//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include <iostream>
#include "../include/PiecePawn.h"

PiecePawn::PiecePawn(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position &position)
    : Piece(eCamp, eIdentity, position) {
  m_name = (m_eCamp == EnumCamp::red ? "兵" : "卒");
}


/**
 * The pawns (soldiers) move one space at a time. If a pawn does not cross the river yet,
 * it can only move forward vertically. Once crossing the river, the pawn can also
 * move horizontally.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PiecePawn::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  if (m_initPosition.rank() == 3 && (rank < m_initPosition.rank() || rank < m_curPosition.rank()))
    return false;

  if (m_initPosition.rank() == 6 && (rank > m_initPosition.rank() || rank > m_curPosition.rank()))
    return false;

  if (abs(rank - m_curPosition.rank()) > 1)
    return false;

  // The pawn can only step forward. After crossing the river, it can step forward or on both sides, one step at a time.
  if (abs(rank - m_initPosition.rank()) <= 1) {
    std::cout<<"crossed the river"<<m_initPosition.rank()<<std::endl;
    if (file != m_curPosition.file() || file != m_initPosition.file())
      return false;
  } else {
    if (abs(file - m_curPosition.file()) + abs(rank - m_curPosition.rank()) > 1)
      return false;
  }

  return Piece::updatePosition(rank, file, vecPiece);
}
