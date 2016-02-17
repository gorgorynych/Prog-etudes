#ifndef GAMESCENE_H
#define GAMESCENE_H

//#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
//#include <QGraphicsRectItem>
//#include <QGraphicsLineItem>

#include <QMouseEvent>
#include <QPoint>
#include <QTimer>

#include <QBrush>
#include <QColor>
#include <QDebug>

//Q_OBJECT required for connect() function


class GameScene : public QGraphicsScene
{
  Q_OBJECT
public:
  GameScene();

protected:

public slots:
  void setViewSize(double w, double h); /////Do I really need this? Maybe there's a way around it//////
  void setUniSize(int size);
  void alterCellValue(QPoint point);

  void startUniverse(); //start
  void stopUniverse();  //stop
  void clearUniverse(); //clear
  void raiseGridFlag();

private slots:
  void paint();
  void paintUniverse();
  void paintGrid();
  void nextGen();

signals:
  //void universeChanged(bool ok);
  void gameEnds(bool ok);

private:
  bool *universe, *next;
  int uniSize;
  bool isDrawGrid;
  double viewWidth, viewHeight;
  QTimer *intervalTimer;
  //QWidget *grid;
  QPainter *p;

  void resetUniverse();
  bool isAlive(int k, int j);

};

#endif // GAMESCENE_H
