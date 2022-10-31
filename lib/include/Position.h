//
// Created by xu on 2022/9/20.
//

#ifndef CHINESE_CHESS_POSITION_H
#define CHINESE_CHESS_POSITION_H


class Position {
public:
  Position(short rank, short file);

  Position();

  ~Position();

  bool operator==(const Position &p) const;

  short rank() const;

  short file() const;

  void setRank(short rank);

  void setFile(short file);

  void setPosition(short rank, short file);

private:
  short m_rank;  //横线
  short m_file;  //直线

};

#endif //CHINESE_CHESS_POSITION_H
