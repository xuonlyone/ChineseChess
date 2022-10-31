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
                                                 EnumIdentity::horse,
                                                 EnumIdentity::elephant,
                                                 EnumIdentity::adviser,
                                                 EnumIdentity::king,
                                                 EnumIdentity::adviser,
                                                 EnumIdentity::elephant,
                                                 EnumIdentity::horse,
                                                 EnumIdentity::rook,
                                                 EnumIdentity::cannon,
                                                 EnumIdentity::cannon,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn,
                                                 EnumIdentity::pawn};

  for (int i = 0; i < 2; ++i) {
    auto eCamp = static_cast<EnumCamp>(i + 1);

    for (int j = 0; j < PIECE_COUNT; ++j) {
      Piece *pPiece = nullptr;
      switch (identityArr[j]) {
        case EnumIdentity::rook:
          pPiece = new PieceRook(eCamp, EnumIdentity::rook, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::horse:
          pPiece = new PieceKnight(eCamp, EnumIdentity::horse, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::elephant:
          pPiece = new PieceMinister(eCamp, EnumIdentity::elephant, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::adviser:
          pPiece = new PieceGuards(eCamp, EnumIdentity::adviser, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::king:
          pPiece = new PieceKing(eCamp, EnumIdentity::king, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::cannon:
          pPiece = new PieceCannon(eCamp, EnumIdentity::cannon, posArr[i * PIECE_COUNT + j]);
          break;
        case EnumIdentity::pawn:
          pPiece = new PiecePawn(eCamp, EnumIdentity::cannon, posArr[i * PIECE_COUNT + j]);
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
  std::cout << __func__ << std::endl;
  if (rank < 0 || rank > 9 || file < 0 || file > 8)
    return nullptr;

  for (auto pPiece: m_vecPiece) {
    if (pPiece == nullptr) {
      std::cout << " null piece " << std::endl;
      continue;
    }

    Position pos = pPiece->curPosition();
    std::cout << pPiece->name() << "111 " << pos.rank() << " " << pos.file() << std::endl;
    if (pPiece->state() != EnumState::live)
      continue;

    if (rank == pos.rank() && file == pos.file()) {
      std::cout << pPiece->name() << " " << pos.rank() << " " << pos.file() << std::endl;
      return pPiece;
    }
  }

  std::cout << " no piece " << std::endl;
  return nullptr;
}


void Chess::reset() {
  for (auto pPiece : m_vecPiece) {
    if (pPiece == nullptr)
      continue;

    pPiece->reset();
  }

  //todo
}


bool Chess::MovePiece(short rankSrc, short fileSrc, short rankDst, short fileDst) {
  Piece *pPiece = getPiece(rankSrc, fileSrc);
  std::cout << "name: " << pPiece->name() << " camp: " << (int) pPiece->camp() << " " << m_redTurn << std::endl;
  if (((pPiece->camp() == EnumCamp::red) ^ m_redTurn))
    return false;

  bool ret = pPiece->updatePosition(rankDst, fileDst, m_vecPiece);
  if (ret)
    m_redTurn = !m_redTurn;

  return ret;
}

std::vector<Piece *> &Chess::getAllPieces() {
  return m_vecPiece;
}

