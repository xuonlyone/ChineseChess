//
// Created by xu on 2022/11/13.
//

#ifndef CHINESE_CHESS_C_MEMENTO_H
#define CHINESE_CHESS_C_MEMENTO_H

#include "Chess.h"

class Piece;

class CMemento {
public:
  CMemento(bool redTurn, std::vector<Piece> vecPiece);

  CMemento(const CMemento &m);

  ~CMemento();

  bool getStateTurn();

  std::vector<Piece> getStatePiece();

  void setState(bool redTurn, std::vector<Piece> vecPiece);

private:
  bool m_redTurn;
  std::vector<Piece> m_vecPiece;

};


#endif //CHINESE_CHESS_C_MEMENTO_H
