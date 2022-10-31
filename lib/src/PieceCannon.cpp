//
// Created by xu on 2022/9/20.
//

#include "../include/PieceCannon.h"

PieceCannon::PieceCannon(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position &position)
    : Piece(eCamp, eIdentity, position) {
  m_name = (m_eCamp == EnumCamp::red ? "炮" : "砲");
}

/**
 * The cannons move one ore more spaces horizontally or vertically like a Rook.
 * However, in a capture move, there must be exactly one non-empty space in between the original and final position.
 * In a non-capture move, all spaces in between must be empty.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceCannon::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  if (!((rank == m_curPosition.rank() && file != m_curPosition.file()) ||
        (rank != m_curPosition.rank() && file == m_curPosition.file())))
    return false;

  unsigned rackNumber = 0;
  bool hasEnemy = false;
  Piece *pEnemyPiece = nullptr;
  for (auto pPiece: vecPiece) {
    if (pPiece == nullptr)
      continue;

    if (pPiece->state() != EnumState::live)
      continue;

    Position pos = pPiece->curPosition();
    if (m_curPosition == pos) //ignore itself
      continue;

    if (pos.rank() == rank) {
      if ((m_curPosition.file() < pos.file() && pos.file() < file) ||
          (m_curPosition.file() > pos.file() && pos.file() > file)) {
        ++rackNumber;
        continue;
      }

      if (pos.file() == file) {
        if (pPiece->camp() == m_eCamp) {
          return false;
        } else {
          hasEnemy = true;
          pEnemyPiece = pPiece;
        }
      }
    }

    if (pos.file() == file) {
      if ((m_curPosition.rank() < pos.rank() && pos.rank() < rank) ||
          (m_curPosition.rank() > pos.rank() && pos.rank() > rank)) {
        ++rackNumber;
      }

      if (pos.rank() == rank) {
        if (pPiece->camp() == m_eCamp) {
          return false;
        } else {
          hasEnemy = true;
          pEnemyPiece = pPiece;
        }
      }
    }
  }

  if (hasEnemy && rackNumber == 1) {
    pEnemyPiece->setStatus(EnumState::dead);
    pEnemyPiece->setCurPosition(-rank, -file);
    m_curPosition.setPosition(rank, file);
    return true;
  } else if (!hasEnemy && rackNumber == 0) {
    m_curPosition.setPosition(rank, file);
    return true;
  } else {
    return false;
  }
}
