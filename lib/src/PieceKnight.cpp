//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include <iostream>
#include "../include/PieceKnight.h"

PieceKnight::PieceKnight(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "傌" : "馬");
}


/**
 * The Knights (Horses) move two spaces horizontally and one space vertically (or respectively 2
 * spaces vertically and one space horizontally). If there is a piece next to the knight
 * in the horizontal (vertical) direction, the knight is blocked and the move is not allowed.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceKnight::updatePosition(int8_t rank, int8_t file, Chess &chess) {
  unsigned val1 = abs(rank - m_curPosition.rank());
  unsigned val2 = abs(file - m_curPosition.file());

  if (!((val1 + val2 == 3) && (val1 != 0) && (val2 != 0)))
    return false;

  std::vector<Piece *> &vecPiece = chess.getAllPieces();
  //consider the lame knight
  if (val1 > val2) {
    auto lame = (rank + m_curPosition.rank()) / 2;
    for (auto pPiece: vecPiece) {
      Position pos = pPiece->curPosition();
      if (m_curPosition == pos)
        continue;

      if (lame == pos.rank() && m_curPosition.file() == pos.file())
        return false;
    }
  } else {
    auto lame = (file + m_curPosition.file()) / 2;
    for (auto pPiece: vecPiece) {
      Position pos = pPiece->curPosition();
      if (m_curPosition == pos) //ignore itself
        continue;;

      if (lame == pos.file() && m_curPosition.rank() == pos.rank())
        return false;
    }
  }

  return Piece::updatePosition(rank, file, chess);
}

bool PieceKnight::checking(Chess &chess) {
  Piece *pPieceKing = chess.getKing(!m_bCampRed);
  Position posKing = pPieceKing->curPosition();

  unsigned val1 = abs(posKing.rank() - m_curPosition.rank());
  unsigned val2 = abs(posKing.file() - m_curPosition.file());

  if (!((val1 + val2 == 3) && (val1 != 0) && (val2 != 0)))
    return false;

  //consider the lame knight
  if (val1 > val2) {
    auto lame = (posKing.rank() + m_curPosition.rank()) / 2;
    Piece *pPieceLame = chess.getPiece(lame, m_curPosition.file());
    if (pPieceLame != nullptr)
      return false;
  } else {
    auto lame = (posKing.file() + m_curPosition.file()) / 2;
    Piece *pPieceLame = chess.getPiece(m_curPosition.rank(), lame);
    if (pPieceLame != nullptr)
      return false;
  }

  printf("[%s %s], %s %s is checking.\n", __FILE__, __func__, m_camp, m_name);
  return true;
}
