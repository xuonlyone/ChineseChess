//
// Created by xu on 2022/10/17.
//

#ifndef CHINESECHESS_BOARDWIDGET_H
#define CHINESECHESS_BOARDWIDGET_H

#include <QTimer>
#include "ui/ui_ui_Board.h"
#include "lib/include/Chess.h"
#include "lib/include/CCaretaker.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;

class QDropEvent;

QT_END_NAMESPACE

class BoardWidget : public QWidget {
Q_OBJECT

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
  CCaretaker m_caretaker;
  QTimer *m_timer;

  void paintEvent(QPaintEvent *) override;

  void showMsg(const char *msg);

private slots:

  void hideMsg();
};


#endif //CHINESECHESS_BOARDWIDGET_H
