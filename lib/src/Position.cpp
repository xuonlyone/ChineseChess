//
// Created by xu on 2022/9/20.
//

#include "../include/Position.h"

Position::Position(int8_t rank, int8_t file) {
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

int8_t Position::rank() const {
  return m_rank;
}

int8_t Position::file() const {
  return m_file;
}

void Position::setRank(int8_t rank) {
  m_rank = rank;
}

void Position::setFile(int8_t file) {
  m_file = file;
}

bool Position::operator==(const Position &p) const {
  return (m_rank == p.m_rank) && (m_file == p.m_file);
}

Position Position::operator+(const Position &p) const {
  return {static_cast<int8_t>((m_rank + p.m_rank)),
          static_cast<int8_t>((m_file + p.m_file))};
}

void Position::setPosition(int8_t rank, int8_t file) {
  m_rank = rank;
  m_file = file;
}

void Position::setPosition(const Position &p) {
  m_rank = p.m_rank;
  m_file = p.m_file;
}




