//
// Created by xu on 2022/9/20.
//

#include <cmath>
#include <iostream>
#include "../include/PieceKing.h"

PieceKing::PieceKing(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : Piece(bCampRed, eIdentity, position) {
  m_name = (m_bCampRed ? "帥" : "將");
}


/**
 * The king moves only one space at a time, either horizontally or vertically.
 * Further more, the King must always stay within the palace, which is a square marked with an X.
 * @param rank
 * @param file
 * @param vecPiece
 * @return
 */
bool PieceKing::updatePosition(int8_t rank, int8_t file, Chess &chess) {
  if (abs(rank - m_curPosition.rank()) + abs(file - m_curPosition.file()) != 1)
    return false;

  if (abs(m_initPosition.rank() - rank) > 2)
    return false;
  if (abs(file - 4) > 1)
    return false;

  return Piece::updatePosition(rank, file, chess);
}



//bool PieceKing::checked(Chess &chess) {
//  return (checkedByPawn(chess) ||
//          checkedByCannon(chess) ||
//          checkedByKnight(chess) ||
//          checkedByRook(chess) ||
//          checkedByKing(chess));
//}

/**
 * The two Kings in the board must never be on the same file (vertical line)
 * without any pieces in between them. A move that puts the two Kings in such
 * a setting is illegal.
 * @param vecPiece
 * @return
 */

bool PieceKing::checking(Chess &chess) {
  Piece *pPieceKing = chess.getKing(!m_bCampRed);
  Position posKing = pPieceKing->curPosition();

  if (posKing.file() != m_curPosition.file())
    return false;

  int8_t maxPos = std::max(posKing.rank(), m_curPosition.rank());
  int8_t minPos = std::min(posKing.rank(), m_curPosition.rank());

  for (int8_t i = minPos + 1; i < maxPos; ++i) {
    Piece *pPiece = chess.getPiece(posKing.rank(), i);
    if (pPiece != nullptr)
      return false;
  }

  printf("[%s %s], the king faces each other.\n", __FILE__, __func__);
  return true;
}

//bool PieceKing::checkedByKing(Chess &chess) {
//  int8_t rank = m_curPosition.rank();
//  if (rank < 3) {
//    for (int8_t i = rank + 1; i < 10; ++i) {
//      Piece *pPiece = chess.getPiece(i, m_curPosition.file());
//      if (pPiece == nullptr)
//        continue;
//
//      if (pPiece->state() != EnumState::live)
//        continue;
//
//      if (pPiece->role() != EnumIdentity::king)
//        return false;
//      else
//        return true;
//    }
//  }
//  if (rank > 6) {
//    for (int8_t i = 1; i < rank; ++i) {
//      Piece *pPiece = chess.getPiece(rank - i, m_curPosition.file());
//      if (pPiece == nullptr)
//        continue;
//
//      if (pPiece->state() != EnumState::live)
//        continue;
//
//      if (pPiece->role() != EnumIdentity::king)
//        return false;
//      else
//        return true;
//    }
//  }
//  return false;
//}
//
//
//bool PieceKing::checkedByRook(Chess &chess) {
//  int8_t rank = m_curPosition.rank();
//  int8_t file = m_curPosition.file();
//
//  for (int8_t i = 0; i < rank; ++i) {
//    Piece *pPiece = chess.getPiece(rank - i - 1, file);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  for (int8_t i = rank; i < 10; ++i) {
//    Piece *pPiece = chess.getPiece(i + 1, file);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  for (int8_t i = 0; i < file; ++i) {
//    Piece *pPiece = chess.getPiece(rank, file - i - 1);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  for (int8_t i = file; i < 9; ++i) {
//    Piece *pPiece = chess.getPiece(rank, i + 1);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  return false;
//}
//
//
//bool PieceKing::checkedByCannon(Chess &chess) {
//  int8_t rank = m_curPosition.rank();
//  int8_t file = m_curPosition.file();
//
//  int count = 0;
//  for (int8_t i = 0; i < rank; ++i) {
//    Piece *pPiece = chess.getPiece(rank - i - 1, file);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (count == 0) {
//      ++count;
//      continue;
//    }
//
//    if (pPiece->role() == EnumIdentity::cannon && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  count = 0;
//  for (int8_t i = rank; i < 10; ++i) {
//    Piece *pPiece = chess.getPiece(i + 1, file);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (count == 0) {
//      ++count;
//      continue;
//    }
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  count = 0;
//  for (int8_t i = 0; i < file; ++i) {
//    Piece *pPiece = chess.getPiece(rank, file - i - 1);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (count == 0) {
//      ++count;
//      continue;
//    }
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  count = 0;
//  for (int8_t i = file; i < 9; ++i) {
//    Piece *pPiece = chess.getPiece(rank, i + 1);
//    if (pPiece == nullptr)
//      continue;
//
//    if (pPiece->state() != EnumState::live)
//      continue;
//
//    if (count == 0) {
//      ++count;
//      continue;
//    }
//
//    if (pPiece->role() == EnumIdentity::rook && pPiece->campRed() == m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//
//  return false;
//}
//
//
//bool PieceKing::checkedByPawn(Chess &chess) {
//  int8_t rank = m_curPosition.rank();
//  int8_t file = m_curPosition.file();
//  Piece *pPiece = chess.getPiece(rank, file + 1);
//  if (pPiece != nullptr &&
//      pPiece->role() == EnumIdentity::pawn &&
//      pPiece->state() == EnumState::live &&
//      pPiece->campRed() != m_bCampRed) {
//    return true;
//  }
//
//  pPiece = chess.getPiece(rank, file - 1);
//  if (pPiece != nullptr &&
//      pPiece->role() == EnumIdentity::pawn &&
//      pPiece->state() == EnumState::live &&
//      pPiece->campRed() != m_bCampRed) {
//    return true;
//  }
//
//  if (rank < 3) {
//    pPiece = chess.getPiece(rank + 1, file);
//    if (pPiece != nullptr &&
//        pPiece->role() == EnumIdentity::pawn &&
//        pPiece->state() == EnumState::live &&
//        pPiece->campRed() != m_bCampRed) {
//      return true;
//    }
//  } else if (rank > 6) {
//    pPiece = chess.getPiece(rank - 1, file);
//    if (pPiece != nullptr &&
//        pPiece->role() == EnumIdentity::pawn &&
//        pPiece->state() == EnumState::live &&
//        pPiece->campRed() != m_bCampRed) {
//      return true;
//    } else
//      return false;
//  }
//  return false;
//}
//
//
//bool PieceKing::checkedByKnight(Chess &chess) {
//  int8_t rank = m_curPosition.rank();
//  int8_t file = m_curPosition.file();
//  Position posCheck[] = {{-1, -2},
//                         {-1, 2},
//                         {1,  -2},
//                         {1,  2},
//                         {-2, -1},
//                         {-2, 1},
//                         {2,  -1},
//                         {2,  1}
//  };
//  Position posLame[] = {{-1, -1},
//                        {-1, 1},
//                        {1,  -1},
//                        {1,  1}
//  };
//
//  for (int i = 0; i < 8; ++i) {
//    Piece *pPiece = chess.getPiece(m_curPosition + posCheck[i]);
//    if (pPiece != nullptr &&
//        pPiece->role() == EnumIdentity::knight &&
//        pPiece->state() == EnumState::live &&
//        pPiece->campRed() != m_bCampRed &&
//        chess.getPiece(m_curPosition + posLame[i % 4]) == nullptr)
//      return true;
//  }
//  return false;
//}