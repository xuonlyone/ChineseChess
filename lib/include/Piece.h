//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_PIECE_H
#define CHINESE_CHESS_PIECE_H

#include "Position.h"
#include <vector>

enum class EnumCamp {
  unknown = 0,
  red,
  black,
};

enum class EnumIdentity {
  unknown = 0,
  rook, //车
  horse,  //马
  elephant, //象相
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

class Piece {
public:
  Piece(enum EnumCamp eCamp, enum EnumIdentity eIdentity, const Position &position);

  Piece();

  virtual ~Piece();

  bool operator==(const Piece &p) const;

  void setCamp(enum EnumCamp eCamp);

  void setRole(enum EnumIdentity eIdentity);

  void setCurPosition(const Position &position);

  void setStatus(enum EnumState eState);

  void reset();

  void setCurPosition(short rank, short file);

  virtual bool updatePosition(short rank, short file, std::vector<Piece *> &vecPiece);

  const char *name() const;

  enum EnumCamp camp() const;

  enum EnumIdentity role() const;

  enum EnumState state() const;

  Position curPosition() const;


protected:
  enum EnumCamp m_eCamp;
  enum EnumIdentity m_eIdentity;
  enum EnumState m_eState;
  Position m_initPosition;
  Position m_curPosition;
  const char *m_name;
};


#endif //CHINESE_CHESS_PIECE_H
