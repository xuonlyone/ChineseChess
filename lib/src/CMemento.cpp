//
// Created by xu on 2022/11/13.
//

#include "../include/CMemento.h"

#include <utility>

CMemento::CMemento(bool redTurn, std::vector<Piece> vecPiece) : m_redTurn(redTurn), m_vecPiece(std::move(vecPiece)) {

}

CMemento::CMemento(const CMemento &m) {
  m_redTurn = m.m_redTurn;
  m_vecPiece.assign(m.m_vecPiece.begin(), m.m_vecPiece.end());
}

CMemento::~CMemento() {
  m_vecPiece.clear();
}

bool CMemento::getStateTurn() {
  return m_redTurn;
}

std::vector<Piece> CMemento::getStatePiece() {
  return m_vecPiece;
}

void CMemento::setState(bool redTurn, std::vector<Piece> vecPiece) {
  m_redTurn = redTurn;
  m_vecPiece.assign(vecPiece.begin(), vecPiece.end());
}



