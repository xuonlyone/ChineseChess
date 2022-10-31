//
// Created by xu on 2022/10/17.
//

#include <QPainter>
#include <QLabel>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include <iostream>
#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
  m_origin = 60;
  m_spacing = 90;

  setMinimumSize(20, 20);
  setAcceptDrops(true);

  std::vector<Piece *> vecPiece = m_Chess.getAllPieces();
  for (auto &pPiece : vecPiece) {
    if (pPiece->state() != EnumState::live)
      continue;

    Position pos = pPiece->curPosition();

    QImage image(":/res/piece.png");

    QFont font;
    font.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
    font.setPointSize(32);
    QPainter *painter = new QPainter(&image);
    painter->setFont(font);
    if (pPiece->camp() == EnumCamp::red)
      painter->setPen(Qt::red);
    painter->drawText(image.rect(), Qt::AlignCenter, QString::fromLocal8Bit(pPiece->name()));
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    //imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->move(m_origin + pos.file() * m_spacing - image.rect().center().x(),
                     m_origin + pos.rank() * m_spacing - image.rect().center().y());

    std::cout << "piece" << pPiece->name() << " " << imageLabel << std::endl;

//    QLabel *pieceIcon1 = new QLabel(this);
//    pieceIcon1->setPixmap(QPixmap(":/res/piece.png"));
//    QFont font;
//    font.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
//    font.setPointSize(40);
//    pieceIcon1->setFont(font);
//    pieceIcon1->setText(QString::fromLocal8Bit(pPiece->name()));
//
//    pieceIcon1->setMaximumSize(100, 100);
//
//    pieceIcon1->move(m_origin + pos.file() * m_spacing, m_origin + pos.rank() * m_spacing);
//    pieceIcon1->show();
//    pieceIcon1->setAttribute(Qt::WA_DeleteOnClose);
  }


  uiFormBoard.setupUi(this);
}


void BoardWidget::paintEvent(QPaintEvent *) {
  QPainter paint(this);

  for (int i = 0; i < 10; ++i)
    paint.drawLine(QPoint(m_origin, m_origin + i * m_spacing),
                   QPoint(m_origin + 8 * m_spacing, m_origin + i * m_spacing));

  for (int i = 0; i < 9; ++i) {
    if (i == 0 || i == 8) {
      paint.drawLine(QPoint(m_origin + i * m_spacing, m_origin),
                     QPoint(m_origin + i * m_spacing, m_origin + 9 * m_spacing));
      continue;
    }

    paint.drawLine(QPoint(m_origin + i * m_spacing, m_origin),
                   QPoint(m_origin + i * m_spacing, m_origin + 4 * m_spacing));
    paint.drawLine(QPoint(m_origin + i * m_spacing, m_origin + 5 * m_spacing),
                   QPoint(m_origin + i * m_spacing, m_origin + 9 * m_spacing));
  }

  paint.drawLine(QPoint(m_origin + 3 * m_spacing, m_origin),
                 QPoint(m_origin + 5 * m_spacing, m_origin + 2 * m_spacing));
  paint.drawLine(QPoint(m_origin + 5 * m_spacing, m_origin),
                 QPoint(m_origin + 3 * m_spacing, m_origin + 2 * m_spacing));
  paint.drawLine(QPoint(m_origin + 3 * m_spacing, m_origin + 7 * m_spacing),
                 QPoint(m_origin + 5 * m_spacing, m_origin + 9 * m_spacing));
  paint.drawLine(QPoint(m_origin + 5 * m_spacing, m_origin + 7 * m_spacing),
                 QPoint(m_origin + 3 * m_spacing, m_origin + 9 * m_spacing));


  QRect rectChuHe(m_origin + m_spacing, m_origin + 4 * m_spacing, m_spacing * 4, m_spacing);
  QRect rectHanJie(m_origin + 5 * m_spacing, m_origin + 4 * m_spacing, m_spacing * 4, m_spacing);
  QFont font;
  font.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
  font.setPointSize(58);
  paint.setFont(font);
  paint.drawText(rectChuHe, QString::fromLocal8Bit("楚 河"), QTextOption(Qt::AlignVCenter));
  paint.drawText(rectHanJie, QString::fromLocal8Bit("漢 界"), QTextOption(Qt::AlignVCenter));

//  //*******************绘画棋子*******************
//  for(int i = 0; i < 32; i++)
//    drawChessPieces(painter, i);
//  //绘制上次移动棋子的起止位置
//  if(m_bIsShowStep)
//    drawLastStep(painter,m_ChessSteps);
//
//  //绘制文本棋谱
//  drawTextStep();
}

BoardWidget::~BoardWidget() = default;

void BoardWidget::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void BoardWidget::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void BoardWidget::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    int rankSrc = (m_eventPoint.y() - m_origin + pixmap.rect().center().y()) / m_spacing;
    int fileSrc = (m_eventPoint.x() - m_origin + pixmap.rect().center().x()) / m_spacing;
    int rankDst = (event->position().toPoint().y() - m_origin + pixmap.rect().center().y()) / m_spacing;
    int fileDst = (event->position().toPoint().x() - m_origin + pixmap.rect().center().x()) / m_spacing;
    std::cout << "point origin " << rankSrc << ", " << fileSrc << std::endl;
    std::cout << "point target " << rankDst << ", " << fileDst << std::endl;
    bool bMove = m_Chess.MovePiece(rankSrc, fileSrc, rankDst, fileDst);
    if (bMove) {
      auto *child = dynamic_cast<QLabel *>(childAt(m_origin + fileDst * m_spacing,
                                                   m_origin + rankDst * m_spacing));
      std::cout << child << std::endl;
      if (child) {
        child->clear();
      }

      auto *newIcon = new QLabel(this);
      newIcon->setPixmap(pixmap);
      newIcon->move(m_origin + fileDst * m_spacing - pixmap.rect().center().x(),
                    m_origin + rankDst * m_spacing - pixmap.rect().center().y());
      newIcon->show();
      newIcon->setAttribute(Qt::WA_DeleteOnClose);
    }

    if (event->source() == this) {
      if (bMove) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
      } else {
        event->setDropAction(Qt::IgnoreAction);
        event->ignore();
      }

    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void BoardWidget::mousePressEvent(QMouseEvent *event) {
  QLabel *child = dynamic_cast<QLabel *>(childAt(event->position().toPoint()));
  if (!child)
    return;

  QPixmap pixmap = child->pixmap(Qt::ReturnByValue);

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());
  m_eventPoint = event->position().toPoint();
//! [1]

//! [2]
  QMimeData *mimeData = new QMimeData;
  mimeData->setData("application/x-dnditemdata", itemData);
//! [2]

//! [3]
  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(event->position().toPoint() - child->pos());
//! [3]

  QPixmap tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  //painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  child->setPixmap(tempPixmap);

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
    child->close();
  } else {
    child->show();
    child->setPixmap(pixmap);
  }
}
