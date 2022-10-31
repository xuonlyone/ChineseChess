#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>

#include "BoardWidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget mainWidget;

  QHBoxLayout *horizontalLayout = new QHBoxLayout(&mainWidget);
  horizontalLayout->addWidget(new BoardWidget);

  mainWidget.setWindowTitle(QObject::tr("Chinese Chess"));
  mainWidget.resize(1024, 968);

  //Ui::Form_Board uiBoard;
  //uiBoard.setupUi(&mainWidget);

  mainWidget.show();
  return QApplication::exec();
}
