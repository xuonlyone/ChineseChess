//
// Created by xu on 2022/11/17.
//

#ifndef CHINESE_CHESS_CCARETAKER_H
#define CHINESE_CHESS_CCARETAKER_H

#include <stack>
#include "CMemento.h"

class CCaretaker {
public:
  CCaretaker();

  ~CCaretaker();

  CMemento getMemento();

  void setMemento(const CMemento& m);

private:
  std::stack<CMemento> m_stackMemento;
};


#endif //CHINESE_CHESS_CCARETAKER_H
