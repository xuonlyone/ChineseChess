//
// Created by xu on 2022/9/20.
//

#include "../include/PieceRook.h"

PieceRook::PieceRook(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position &position)
    : Piece(eCamp, eIdentity, position) {
  m_name = (m_eCamp == EnumCamp::red ? "俥" : "車");
}


/**
 * The Rooks (Chariots) move one or more spaces horizontally or vertically provide that
 * all positions between the original and final positions are empty.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceRook::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  if (!(rank == m_curPosition.rank() && file != m_curPosition.file() ||
        rank != m_curPosition.rank() && file == m_curPosition.file()))
    return false;

  for (auto pPiece : vecPiece) {
    if (pPiece->state() != EnumState::live)
      continue;

    Position pos = pPiece->curPosition();
    if (m_curPosition == pos)  //ignore itself
      continue;

    if (pos.rank() == rank) {
      if ((m_curPosition.file() < pos.file() && pos.file() < file) ||
          (m_curPosition.file() > pos.file() && pos.file() > file)) {
        return false;
      }

      if (pos.file() == file) {
        if (pPiece->camp() == m_eCamp) {
          return false;
        } else {
          pPiece->setStatus(EnumState::dead);
          pPiece->setCurPosition(-rank, -file);
          m_curPosition.setPosition(rank, file);
          return true;
        }
      }
    }

    if (pos.file() == file) {
      if ((m_curPosition.rank() < pos.rank() && pos.rank() < rank) ||
          (m_curPosition.rank() > pos.rank() && pos.rank() > rank)) {
        return false;
      }

      if (pos.rank() == rank) {
        if (pPiece->camp() == m_eCamp) {
          return false;
        } else {
          pPiece->setStatus(EnumState::dead);
          pPiece->setCurPosition(-rank, -file);
          m_curPosition.setPosition(rank, file);
          return true;
        }
      }
    }
  }

  m_curPosition.setPosition(rank, file);
  return true;
}


