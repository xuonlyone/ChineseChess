//
// Created by xu on 2022/10/17.
//

#ifndef CHINESECHESS_BOARDWIDGET_H
#define CHINESECHESS_BOARDWIDGET_H

#include "ui/ui_ui_Board.h"
#include "lib/include/Chess.h"
QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class BoardWidget : public  QWidget{
public:
  explicit BoardWidget(QWidget *parent = nullptr);
  ~BoardWidget() override;

protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
private:
  Ui::Form_Board uiFormBoard;
  Chess m_Chess;

  int m_origin;
  int m_spacing;
  QPoint m_eventPoint;

  void paintEvent(QPaintEvent *);
};


#endif //CHINESECHESS_BOARDWIDGET_H
