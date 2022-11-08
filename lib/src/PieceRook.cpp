//
// Created by xu on 2022/9/20.
//

#include <iostream>
#include "../include/PieceRook.h"

PieceRook::PieceRook(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "俥" : "車");
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
  if (!((rank == m_curPosition.rank() && file != m_curPosition.file()) ||
        (rank != m_curPosition.rank() && file == m_curPosition.file())))
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
        if (pPiece->campRed() == m_bCampRed) {
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
        if (pPiece->campRed() == m_bCampRed) {
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

bool PieceRook::checking(Chess &chess) {
  Piece *pPieceKing = chess.getKing(!m_bCampRed);
  Position posKing = pPieceKing->curPosition();

  printf("[%s %s] %s %s at (%d %d), %s %s at (%d %d)\n", __FILE__, __func__,
         pPieceKing->camp(), pPieceKing->name(), posKing.rank(), posKing.file(),
         m_camp, m_name, m_curPosition.rank(), m_curPosition.file());

  if (posKing.rank() == m_curPosition.rank()) {
    short maxPos = std::max(posKing.file(), m_curPosition.file());
    short minPos = std::min(posKing.file(), m_curPosition.file());

    for (short i = minPos + 1; i < maxPos; ++i) {
      Piece *pPiece = chess.getPiece(posKing.rank(), i);
      if (pPiece != nullptr)
        return false;
    }
    printf("[%s %s], %s %s is checking at rank %d.\n", __FILE__, __func__,
           m_camp, m_name, m_curPosition.rank());
    return true;
  }

  if (posKing.file() == m_curPosition.file()) {
    short maxPos = std::max(posKing.rank(), m_curPosition.rank());
    short minPos = std::min(posKing.rank(), m_curPosition.rank());

    for (short i = minPos + 1; i < maxPos; ++i) {
      Piece *pPiece = chess.getPiece(i, posKing.file());
      if (pPiece != nullptr)
        return false;
    }

    printf("[%s %s], %s %s is checking at file %d.\n", __FILE__, __func__,
           m_camp, m_name, m_curPosition.file());
    return true;
  }


  return false;
}
