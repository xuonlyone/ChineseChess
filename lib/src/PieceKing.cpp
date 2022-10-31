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

bool PieceKing::checked(std::vector<Piece *> &vecPiece) {
  return (checkedByPawn(vecPiece) ||
          checkedByCannon(vecPiece) ||
          checkedByHorse(vecPiece) ||
          checkedByRook(vecPiece) ||
          checkedByKing(vecPiece));
}

/**
 * The two Kings in the board must never be on the same file (vertical line)
 * without any pieces in between them. A move that puts the two Kings in such
 * a setting is illegal.
 * @param vecPiece
 * @return
 */
bool PieceKing::checkedByKing(std::vector<Piece *> &vecPiece) {
  bool meetOnSameFile = false;
  for (auto pPiece: vecPiece) {
    if (pPiece->state() == EnumState::dead)
      continue;

    Position pos = pPiece->curPosition();
    if (m_curPosition == pos)
      continue;

    if (m_curPosition.file() != pos.file())
      continue;

    if (pPiece->role() != EnumIdentity::king)
      return false;

    meetOnSameFile = true;
  }

  if (meetOnSameFile)
    return true;

  return false;
}

bool PieceKing::checkedByRook(std::vector<Piece *> &vecPiece) {
  for (auto pPiece: vecPiece) {
    if (pPiece->state() == EnumState::dead)
      continue;

    if (pPiece == this)
      continue;

    Position pos = pPiece->curPosition();
    if (m_curPosition.file() != pos.file() && m_curPosition.rank() != pos.rank())
      continue;

    if (pPiece->camp() != m_eCamp && pPiece->role() == EnumIdentity::rook) {

    }
  }
  return false;
}

bool PieceKing::checkedByPawn(std::vector<Piece *> &vecPiece) {
  return false;
}


bool PieceKing::checkedByCannon(std::vector<Piece *> &vecPiece) {
  return false;
}

bool PieceKing::checkedByHorse(std::vector<Piece *> &vecPiece) {
  return false;
}