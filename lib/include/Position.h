//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_POSITION_H
#define CHINESE_CHESS_POSITION_H


#include <cstdint>

class Position {
public:
  Position(int8_t rank, int8_t file);

  Position();

  ~Position();

  bool operator==(const Position &p) const;

  Position operator+(const Position &p) const;

  int8_t rank() const;

  int8_t file() const;

  void setRank(int8_t rank);

  void setFile(int8_t file);

  void setPosition(int8_t rank, int8_t file);

  void setPosition(const Position &p);

private:
  int8_t m_rank;  //横线
  int8_t m_file;  //直线

};

#endif //CHINESE_CHESS_POSITION_H
