//
// Created by xu on 2022/9/20.
//

#include <iostream>
#include "../include/PieceCannon.h"

PieceCannon::PieceCannon(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "炮" : "砲");
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
        if (pPiece->campRed() == m_bCampRed) {
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
        if (pPiece->campRed() == m_bCampRed) {
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


bool PieceCannon::checking(Chess &chess) {
  printf("[%s %s], checking the king situation.\n", __FILE__, __func__);
  Piece *pPieceKing = chess.getKing(!m_bCampRed);
  Position posKing = pPieceKing->curPosition();

  printf("[%s %s] %s %s at (%d %d), %s %s at (%d %d)\n", __FILE__, __func__,
         pPieceKing->camp(), pPieceKing->name(), posKing.rank(), posKing.file(),
         m_camp, m_name, m_curPosition.rank(), m_curPosition.file());

  if (posKing.rank() == m_curPosition.rank()) {
    short maxPos = std::max(posKing.file(), m_curPosition.file());
    short minPos = std::min(posKing.file(), m_curPosition.file());

    int count = 0;
    for (short i = minPos + 1; i < maxPos; ++i) {
      Piece *pPiece = chess.getPiece(posKing.rank(), i);
      if (pPiece != nullptr)
        ++count;
    }
    if (count != 1)
      return false;
    else {
      printf("[%s %s], %s %s is checking at rank %d.\n", __FILE__, __func__,
             m_camp, m_name, m_curPosition.rank());
      return true;
    }
  }

  if (posKing.file() == m_curPosition.file()) {
    short maxPos = std::max(posKing.rank(), m_curPosition.rank());
    short minPos = std::min(posKing.rank(), m_curPosition.rank());

    int count = 0;
    for (short i = minPos + 1; i < maxPos; ++i) {
      Piece *pPiece = chess.getPiece(i, posKing.file());
      if (pPiece != nullptr)
        ++count;
    }
    if (count != 1)
      return false;
    else {
      printf("[%s %s], %s %s is checking at file %d.\n", __FILE__, __func__,
             m_camp, m_name, m_curPosition.file());
      return true;
    }
  }

  return false;
}