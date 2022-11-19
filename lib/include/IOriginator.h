//
// Created by xu on 2022/11/13.
//

#ifndef CHINESE_CHESS_IORIGINATOR_H
#define CHINESE_CHESS_IORIGINATOR_H

#include "CMemento.h"

class CMemento;

class IOriginator {
public:
  virtual CMemento setMemento() = 0;

  virtual void createMemento(CMemento m) = 0;
};


#endif //CHINESE_CHESS_IORIGINATOR_H
