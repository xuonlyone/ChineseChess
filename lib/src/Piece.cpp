//
// Created by xu on 2022/9/20.
//

#include "../include/Piece.h"

Piece::Piece(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position &position)
    : m_eCamp(eCamp), m_eIdentity(eIdentity), m_curPosition(position), m_initPosition(position) {
  m_eState = EnumState::live;
  m_name = nullptr;
}

Piece::Piece() {
  m_eCamp = EnumCamp::unknown;
  m_eIdentity = EnumIdentity::unknown;
  m_eState = EnumState::live;
  m_name = nullptr;
}

Piece::~Piece() = default;

void Piece::setCamp(enum EnumCamp eCamp) {
  m_eCamp = eCamp;
}

void Piece::setRole(enum EnumIdentity eIdentity) {
  m_eIdentity = eIdentity;
}

void Piece::setStatus(enum EnumState eState) {
  m_eState = eState;
}

void Piece::setCurPosition(const Position &position) {
  m_curPosition = position;
}

enum EnumCamp Piece::camp() const {
  return m_eCamp;
}

enum EnumIdentity Piece::role() const {
  return m_eIdentity;
}

enum EnumState Piece::state() const {
  return m_eState;
}

Position Piece::curPosition() const {
  return m_curPosition;
}

void Piece::reset() {
  m_curPosition = m_initPosition;
  m_eState = EnumState::live;
}

bool Piece::updatePosition(short rank, short file, std::vector<Piece *> &vecPiece) {
  if (rank < 0 || rank > 10 || file < 0 || file > 9)
    return false;

  for (auto pPiece: vecPiece) {
    Position pos = pPiece->curPosition();
    if (pPiece->state() != EnumState::live)
      continue;

    if (rank == pos.rank() && file == pos.file()) {
      if (pPiece->camp() == m_eCamp)
        return false;
      else {
        pPiece->setStatus(EnumState::dead);
        pPiece->setCurPosition(-rank, -file);
        m_curPosition.setPosition(rank, file);
        return true;
      }
    }
  }

  m_curPosition.setPosition(rank, file);
  return true;
}

void Piece::setCurPosition(short rank, short file) {
  m_curPosition.setPosition(rank, file);
}

bool Piece::operator==(const Piece &p) const {
  if (p.m_eCamp == m_eCamp &&
      p.m_eIdentity == m_eIdentity &&
      p.m_initPosition == m_initPosition)
    return true;

  return false;
}

const char *Piece::name() const {
  return m_name;
}



