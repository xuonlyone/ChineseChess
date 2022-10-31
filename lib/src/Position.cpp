//
// Created by xu on 2022/9/20.
//

#include "../include/Position.h"

Position::Position(short rank, short file) {
  m_rank = rank;
  m_file = file;
}

Position::Position() {
  m_file = -1;
  m_rank = -1;
}

Position::~Position() {
  m_file = -1;
  m_rank = -1;
}

short Position::rank() const {
  return m_rank;
}

short Position::file() const {
  return m_file;
}

void Position::setRank(short rank) {
  m_rank = rank;
}

void Position::setFile(short file) {
  m_file = file;
}

bool Position::operator==(const Position &p) const {
  return (m_rank == p.rank()) && (m_file == p.file());
}

void Position::setPosition(short rank, short file) {
  m_rank = rank;
  m_file = file;
}



