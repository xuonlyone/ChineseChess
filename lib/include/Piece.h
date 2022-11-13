//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_H
#define CHINESE_CHESS_PIECE_H

#include <vector>
#include "Position.h"
#include "Chess.h"


enum class EnumIdentity {
  unknown = 0,
  rook, //车
  knight,  //马
  minister, //象相
  adviser,  //士仕
  king, //将帅
  cannon, //炮
  pawn, //兵卒
};


enum class EnumState {
  unknown = 0,
  live,
  dead,
};

class Chess;

class Piece {
public:
  Piece(bool bCampRed, enum EnumIdentity eIdentity, const Position &position);

  Piece();

  virtual ~Piece();

  bool operator==(const Piece &p) const;

  void setCampRed(bool bCampRed);

  void setRole(enum EnumIdentity eIdentity);

  void setCurPosition(const Position &position);

  void setStatus(enum EnumState eState);

  void reset();

  void setCurPosition(int8_t rank, int8_t file);

  virtual bool updatePosition(int8_t rank, int8_t file, Chess &chess);

  const char *name() const;

  bool campRed() const;

  const char* camp() const;

  enum EnumIdentity role() const;

  enum EnumState state() const;

  Position curPosition() const;

  virtual bool checking(Chess &chess);


protected:
  bool m_bCampRed;
  enum EnumIdentity m_eIdentity;
  enum EnumState m_eState;
  Position m_initPosition;
  Position m_curPosition;
  Position m_prePosition;
  const char *m_name;
  const char *m_camp;
};


#endif //CHINESE_CHESS_PIECE_H
