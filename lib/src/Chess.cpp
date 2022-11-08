//
// Created by xu on 2022/9/21.
//

#include <iostream>
#include "../include/Chess.h"
#include "../include/PieceGuards.h"
#include "../include/PieceCannon.h"
#include "../include/PieceRook.h"
#include "../include/PieceMinister.h"
#include "../include/PieceKnight.h"
#include "../include/PieceKing.h"
#include "../include/PiecePawn.h"

Chess::Chess() {
  m_redTurn = true;
  const Position posArr[PIECE_COUNT * 2] = {{0, 0},
                                            {0, 1},
                                            {0, 2},
                                            {0, 3},
                                            {0, 4},
                                            {0, 5},
                                            {0, 6},
                                            {0, 7},
                                            {0, 8},
                                            {2, 1},
                                            {2, 7},
                                            {3, 0},
                                            {3, 2},
                                            {3, 4},
                                            {3, 6},
                                            {3, 8},
                                            {9, 0},
                                            {9, 1},
                                            {9, 2},
                                            {9, 3},
                                            {9, 4},
                                            {9, 5},
                                            {9, 6},
                                            {9, 7},
                                            {9, 8},
                                            {7, 1},
                                            {7, 7},
                                            {6, 0},
                                            {6, 2},
                                            {6, 4},
                                            {6, 6},
                                            {6, 8}};
  const EnumIdentity identityArr[PIECE_COUNT] = {EnumIdentity::rook,
                                                 EnumIdentity::knight,
                                                 EnumIdentity::minister,
                                                 EnumIdentity::adviser,
                                                 EnumIdentity::king,
                                                 EnumIdentity::adviser,
                                                 EnumIdentity::minister,
                                                 EnumIdentity::knight,
                                                 EnumIdentity::rook,
                                                 EnumIdentity::cannon,
                                                 EnumIdentity::cannon,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn};

  for (int i = 0; i < 2; ++i) {
    bool bCampRed = i;

    for (int j = 0; j < PIECE_COUNT; ++j) {
      Piece *pPiece = nullptr;
      switch (identityArr[j]) {
        case EnumIdentity::rook:
          pPiece = new PieceRook(bCampRed, EnumIdentity::rook, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::knight:
          pPiece = new PieceKnight(bCampRed, EnumIdentity::knight, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::minister:
          pPiece = new PieceMinister(bCampRed, EnumIdentity::minister, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::adviser:
          pPiece = new PieceGuards(bCampRed, EnumIdentity::adviser, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::king:
          pPiece = new PieceKing(bCampRed, EnumIdentity::king, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::cannon:
          pPiece = new PieceCannon(bCampRed, EnumIdentity::cannon, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::pawn:
          pPiece = new PiecePawn(bCampRed, EnumIdentity::cannon, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::unknown:
        default:
          continue;
      }
      m_vecPiece.push_back(pPiece);
    }
  }
}


Chess::~Chess() {
  for (auto &pPiece: m_vecPiece) {
    delete pPiece;
  }
}


Piece *Chess::getPiece(short rank, short file) {
  if (rank < 0 || rank >= 10 || file < 0 || file >= 9) {
    printf("[%s %s], out of range, rank: %d file: %d\n", __FILE__, __func__, rank, file);
    return nullptr;
  }

  for (auto pPiece: m_vecPiece) {
    if (pPiece == nullptr) {
      continue;
    }

    Position pos = pPiece->curPosition();
    if (pPiece->state() != EnumState::live)
      continue;

    if (rank == pos.rank() && file == pos.file()) {
      printf("[%s %s], get piece %s in position (%d, %d)\n", __FILE__, __func__, pPiece->name(), rank, file);
      return pPiece;
    }
  }

  printf("[%s %s], no piece in position (%d, %d)\n", __FILE__, __func__, rank, file);
  return nullptr;
}

Piece *Chess::getPiece(const Position &pos) {
  return getPiece(pos.rank(), pos.file());
}


void Chess::reset() {
  for (auto pPiece : m_vecPiece) {
    if (pPiece == nullptr)
      continue;

    pPiece->reset();
  }

  //todo
}


bool Chess::movePiece(short rankSrc, short fileSrc, short rankDst, short fileDst) {
  Piece *pPiece = getPiece(rankSrc, fileSrc);
  if (pPiece == nullptr)
    return false;

  printf("[%s %s], %s %s moves from position (%d, %d) to (%d, %d)\n", __FILE__, __func__,
         pPiece->camp(), pPiece->name(), rankSrc, fileSrc, rankDst, fileDst);

  if (pPiece->campRed() ^ m_redTurn) {
    printf("[%s %s], it's %s turn, the camp of %s %s is not match.\n", __FILE__, __func__,
           m_redTurn ? "red" : "black", pPiece->camp(), pPiece->name());
    return false;
  }

  bool ret = pPiece->updatePosition(rankDst, fileDst, m_vecPiece);
  if (ret)
    m_redTurn = !m_redTurn;

  return ret;
}


std::vector<Piece *> &Chess::getAllPieces() {
  return m_vecPiece;
}


Piece *Chess::getKing(bool bCampRed) {
  printf("[%s %s], get %s king.\n", __FILE__, __func__, bCampRed ? "red" : "black");
  for (auto pPiece: m_vecPiece) {
    if (pPiece->campRed() == bCampRed && pPiece->role() == EnumIdentity::king)
      return pPiece;
  }
  return nullptr;
}


bool Chess::checking() {
  printf("[%s %s], checking the king situation.\n", __FILE__, __func__);
  for (auto pPiece : m_vecPiece) {
    if (pPiece->campRed() != m_redTurn || pPiece->state() != EnumState::live)
      continue;

    if (pPiece->checking(*this)) {
      printf("[%s %s], %s camp is checking.\n", __FILE__, __func__, m_redTurn ? "red" : "black");
      return true;
    }
  }

  return false;
}
