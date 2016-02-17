#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QGraphicsItem>
//#include <QGraphicsRectItem>

#include <QMouseEvent>
#include <QResizeEvent>

#include <QColor>
#include <QMessageBox>

#include "gamescene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  void stopMessage();

protected:


private:
    bool eventFilter(QObject *, QEvent *event) Q_DECL_OVERRIDE;
    Ui::MainWindow *ui;
    GameScene *game;
    QColor currentColor;
};

#endif // MAINWINDOW_H
