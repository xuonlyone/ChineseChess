//
// Created by xu on 2022/9/20.
//

#include <iostream>
#include "../include/Piece.h"

Piece::Piece(bool bCampRed, enum EnumIdentity eIdentity, const Position &position)
    : m_bCampRed(bCampRed), m_eIdentity(eIdentity), m_initPosition(position), m_curPosition(position) {
  m_eState = EnumState::live;
  m_camp = (m_bCampRed ? "red" : "black");
  m_name = nullptr;
}

Piece::Piece() {
  m_bCampRed = true;
  m_eIdentity = EnumIdentity::unknown;
  m_eState = EnumState::live;
  m_name = nullptr;
}

Piece::~Piece() = default;

void Piece::setCampRed(bool bCampRed) {
  m_bCampRed = bCampRed;
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

bool Piece::campRed() const {
  return m_bCampRed;
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

bool Piece::updatePosition(int8_t rank, int8_t file, Chess &chess) {
  if (rank < 0 || rank > 10 || file < 0 || file > 9) {
    printf("[%s %s], out of range, rank: %d file: %d\n", __FILE__, __func__, rank, file);
    return false;
  }

  std::vector<Piece *> &vecPiece = chess.getAllPieces();
  for (auto pPiece: vecPiece) {
    Position pos = pPiece->curPosition();
    if (pPiece->state() != EnumState::live)
      continue;

    if (rank == pos.rank() && file == pos.file()) {
      if (pPiece->campRed() == m_bCampRed) {
        printf("[%s %s], %s occupy this position, can't move here.\n", __FILE__, __func__, pPiece->name());
        return false;
      } else {
        pPiece->setStatus(EnumState::dead);
        pPiece->setCurPosition(-rank, -file);
        m_curPosition.setPosition(rank, file);
        printf("[%s %s], %s is captured.\n", __FILE__, __func__, pPiece->name());
        return true;
      }
    }
  }

  m_prePosition.setPosition(m_curPosition);
  m_curPosition.setPosition(rank, file);
  return true;
}

void Piece::setCurPosition(int8_t rank, int8_t file) {
  m_curPosition.setPosition(rank, file);
}

bool Piece::operator==(const Piece &p) const {
  if (p.m_bCampRed == m_bCampRed &&
      p.m_eIdentity == m_eIdentity &&
      p.m_initPosition == m_initPosition) {
    return true;
  }

  return false;
}


const char *Piece::name() const {
  return m_name;
}

bool Piece::checking(Chess &chess) {
  return false;
}

const char *Piece::camp() const {
  return m_camp;
}

void Piece::setData(bool bCampRed, EnumState state, const Position &position) {
  m_bCampRed = bCampRed;
  m_curPosition = position;
  m_eState = state;
}




