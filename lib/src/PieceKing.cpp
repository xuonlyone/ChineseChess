//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include <iostream>
#include "../include/PieceKing.h"

PieceKing::PieceKing(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position &position)
    : Piece(eCamp, eIdentity, position) {
  m_name = (m_eCamp == EnumCamp::red ? "帥" : "將");
  std::cout << m_name << std::endl;
}


/**
 * The king moves only one space at a time, either horizontally or vertically.
 * Further more, the King must always stay within the palace, which is a square marked with an X.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceKing::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  if (abs(rank - m_curPosition.rank()) + abs(file - m_curPosition.file()) != 1)
    return false;

  if (abs(m_initPosition.rank() - rank) > 2)
    return false;
  if (abs(file - 4) > 1)
    return false;

  return Piece::updatePosition(rank, file, vecPiece);
}

bool PieceKing::checked(Chess &chess) {
  return (checkedByPawn(chess) ||
          checkedByCannon(chess) ||
          checkedByHorse(chess) ||
          checkedByRook(chess) ||
          checkedByKing(chess));
}

/**
 * The two Kings in the board must never be on the same file (vertical line)
 * without any pieces in between them. A move that puts the two Kings in such
 * a setting is illegal.
 * @param vecPiece
 * @return
 */
bool PieceKing::checkedByKing(Chess &chess) {
  short rank = m_curPosition.rank();
  if (rank < 3) {
    for (short i = rank + 1; i < 10; ++i) {
      Piece *pPiece = chess.getPiece(i, m_curPosition.file());
      if (pPiece == nullptr)
        continue;

      if (pPiece->state() != EnumState::live)
        continue;

      if (pPiece->role() != EnumIdentity::king)
        return false;
      else
        return true;
    }
  }
  if (rank > 6) {
    for (short i = 1; i < rank; ++i) {
      Piece *pPiece = chess.getPiece(rank - i, m_curPosition.file());
      if (pPiece == nullptr)
        continue;

      if (pPiece->state() != EnumState::live)
        continue;

      if (pPiece->role() != EnumIdentity::king)
        return false;
      else
        return true;
    }
  }
  return false;
}


bool PieceKing::checkedByRook(Chess &chess) {
  short rank = m_curPosition.rank();
  short file = m_curPosition.file();

  for (short i = 0; i < rank; ++i) {
    Piece *pPiece = chess.getPiece(rank - i - 1, file);
    if (pPiece == nullptr)
      continue;

    if (pPiece->state() != EnumState::live)
      continue;

    if (pPiece->role() == EnumIdentity::rook && pPiece->camp() == m_eCamp) {
      return true;
    } else
      return false;
  }

  for (short i = rank; i < 10; ++i) {
    Piece *pPiece = chess.getPiece(i + 1, file);
    if (pPiece == nullptr)
      continue;

    if (pPiece->state() != EnumState::live)
      continue;

    if (pPiece->role() == EnumIdentity::rook && pPiece->camp() == m_eCamp) {
      return true;
    } else
      return false;
  }

  for (short i = 0; i < file; ++i) {
    Piece *pPiece = chess.getPiece(rank, file - i - 1);
    if (pPiece == nullptr)
      continue;

    if (pPiece->state() != EnumState::live)
      continue;

    if (pPiece->role() == EnumIdentity::rook && pPiece->camp() == m_eCamp) {
      return true;
    } else
      return false;
  }

  for (short i = file; i < 9; ++i) {
    Piece *pPiece = chess.getPiece(rank, i + 1);
    if (pPiece == nullptr)
      continue;

    if (pPiece->state() != EnumState::live)
      continue;

    if (pPiece->role() == EnumIdentity::rook && pPiece->camp() == m_eCamp) {
      return true;
    } else
      return false;
  }

  return false;
}

bool PieceKing::checkedByPawn(Chess &chess) {

  return false;
}


bool PieceKing::checkedByCannon(Chess &chess) {
  return false;
}

bool PieceKing::checkedByHorse(Chess &chess) {
  return false;
}