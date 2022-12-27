//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include <iostream>
#include "../include/PiecePawn.h"

PiecePawn::PiecePawn(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "兵" : "卒");
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
bool PiecePawn::updatePosition(int8_t rank, int8_t file, Chess &chess) {
  if (m_initPosition.rank() == 3 && (rank < m_initPosition.rank() || rank < m_curPosition.rank()))
    return false;

  if (m_initPosition.rank() == 6 && (rank > m_initPosition.rank() || rank > m_curPosition.rank()))
    return false;

  if (abs(rank - m_curPosition.rank()) > 1)
    return false;

  // The pawn can only step forward. After crossing the river, it can step forward or on both sides, one step at a time.
  if (abs(rank - m_initPosition.rank()) <= 1) {
    if (file != m_curPosition.file() || file != m_initPosition.file())
      return false;
  } else {
    if (abs(file - m_curPosition.file()) + abs(rank - m_curPosition.rank()) > 1)
      return false;
  }

  return Piece::updatePosition(rank, file, chess);
}


bool PiecePawn::checking(Chess &chess) {
  Piece *pPieceKing = chess.getKing(!m_bCampRed);
  Position posKing = pPieceKing->curPosition();

  printf("[%s %s] %s %s at (%d %d), %s %s at (%d %d)\n", __FILE__, __func__,
         pPieceKing->camp(), pPieceKing->name(), posKing.rank(), posKing.file(),
         m_camp, m_name, m_curPosition.rank(), m_curPosition.file());

  if (abs(posKing.rank() - m_curPosition.rank()) > 1 || abs(posKing.file() - m_curPosition.file()) > 1)
    return false;

  if (m_initPosition.rank() == 3 && m_curPosition.rank() > posKing.rank()) {
    return false;
  }

  if (m_initPosition.rank() == 6 && m_curPosition.rank() < posKing.rank()) {
    return false;
  }

  if (abs(m_curPosition.rank() - posKing.rank() + abs(m_curPosition.file() - posKing.file()) != 1))
    return false;

  printf("[%s %s], %s %s is checking.\n", __FILE__, __func__, m_camp, m_name);
  return true;
}