//
// Created by xu on 2022/11/17.
//

#include <iostream>
#include "../include/CCaretaker.h"

CCaretaker::CCaretaker() {
}

CCaretaker::~CCaretaker() {
  while (!m_stackMemento.empty()) {
    m_stackMemento.pop();
  }
}

CMemento CCaretaker::getMemento() {
  printf("[%s %s]get the last turn data\n", __FILE__, __func__);
  CMemento memento(m_stackMemento.top());
  m_stackMemento.pop();
  return memento;
}

void CCaretaker::setMemento(const CMemento& m) {
  m_stackMemento.push(m);
}

