#include "gamescene.h"

GameScene::GameScene() :
  intervalTimer(new QTimer(this))
{
  intervalTimer->setInterval(100);

  uniSize = 40;
  universe = new bool [(uniSize + 2) * (uniSize + 2)];
  next = new bool [(uniSize + 2) * (uniSize + 2)];

  connect(intervalTimer, SIGNAL(timeout()), this, SLOT(nextGen()));

  int i = 0;
  while (i < ((uniSize + 2) * (uniSize + 2)))
    {
      universe[i] = false;
      next[i] = false;
      i++;
    }

  /*  QColor gridColor = Qt::gray;
  QPen gridPen(gridColor);

  gridColor.setAlpha(10);
  gridPen.setWidthF(0.5);
  gridPen.setStyle(Qt::SolidLine);
  gridPen.setDashOffset(2);*/

  /*  QColor uniColor = Qt::black;
  QPen uniPen(uniColor);
  QBrush uniBrush(uniColor);

  uniPen.setWidth(1);*/

  qDebug() << "Initialized successfully";
}

void GameScene::setViewSize(double w, double h)//when resized during action, slows painfully; when launched, no way to interact
{
  viewWidth = w;
  viewHeight = h;
  paint();
}

void GameScene::setUniSize(int size)
{
  uniSize = size;
  clearUniverse();
}

void GameScene::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new bool[(uniSize + 2) * (uniSize + 2)];
    next = new bool[(uniSize + 2) * (uniSize + 2)];
    memset(universe, false, sizeof(bool)*(uniSize + 2) * (uniSize + 2));
    memset(next, false, sizeof(bool)*(uniSize + 2) * (uniSize + 2));
}

void GameScene::alterCellValue(QPoint point)
{
  int cellX = point.x()/(viewWidth/uniSize) + 1;
  int cellY = point.y()/(viewHeight/uniSize) + 1;
  int currentLocation = cellY*uniSize + cellX;

  universe[currentLocation] = !universe[currentLocation];
  paint(); //optimize, this causes whole grid to be redrawn
}

void GameScene::startUniverse()
{
  isDrawGrid = false;
  intervalTimer->start();
}

void GameScene::stopUniverse()
{
  intervalTimer->stop();
}

void GameScene::clearUniverse()
{
  this->clear();
  isDrawGrid = false;
  resetUniverse();
  paintUniverse();
}

void GameScene::raiseGridFlag()
{
  isDrawGrid = true;
  paintGrid();
}

void GameScene::paint()
{
  this->clear();
  if (isDrawGrid) paintGrid();
  paintUniverse();
}

void GameScene::paintGrid()    ///Deal with drawing, too slow!!
{
  //grid->setGeometry(0, 0, viewWidth, viewHeight);
  //this->addWidget(grid);
  //qDebug() << "Added widget";
  //!!!QPainter *p = new QPainter;
  QColor gridColor = Qt::gray;
  QPen gridPen(gridColor);

  gridColor.setAlpha(10);
  gridPen.setWidthF(0.5);
  gridPen.setStyle(Qt::SolidLine);
  gridPen.setDashOffset(2);

  //p->setPen(gridPen);

  double cellWidth = viewWidth/uniSize;
  if (cellWidth != 0)
    {
      for (double k = 0; k<=viewWidth; k+=cellWidth)
        this->addLine(k, 0, k, viewHeight, gridPen);
        //p->drawLine(k, 0, k, viewHeight);

    }
  double cellHeight = viewHeight/uniSize;
  if (cellHeight != 0)
    {
      for (double k = 0; k<=viewHeight; k+=cellHeight)
        this->addLine(0, k, viewWidth, k, gridPen);
        //p->drawLine(0, k, viewWidth, k);
    }
}

void GameScene::paintUniverse()
{
  QColor uniColor = Qt::black;
  QPen uniPen(uniColor);
  QBrush uniBrush(uniColor);
  
  uniPen.setWidth(1);

  qreal cellWidth = viewWidth/uniSize;
  qreal cellHeight = viewHeight/uniSize;

  this->addLine(0, 0, viewWidth, 0, uniPen);
  this->addLine(0, 0, 0, viewHeight, uniPen);
  this->addLine(viewWidth, viewHeight, 0, viewHeight, uniPen);
  this->addLine(viewWidth, viewHeight, viewWidth, 0, uniPen);
  
  for(int k=1; k <= uniSize; k++) {
      for(int j=1; j <= uniSize; j++) {
          if(universe[k*uniSize + j] == true) { // if there is any sense to paint it
              qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
              qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
              QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
              this->addRect(r, uniPen, uniBrush);
            }
        }
    }
}

void GameScene::nextGen()
{
  int notChanged = 0;
  for (int k = 1; k <= uniSize; k++){
    for (int j = 1; j <= uniSize; j++){
      next[k*uniSize + j] = isAlive(k ,j);
      if(next[k*uniSize + j] == universe[k*uniSize + j])
        notChanged++;
      }
    }

  if(notChanged == uniSize*uniSize){
      stopUniverse();
      gameEnds(true);
      return;
    }

  for (int k = 1; k <= uniSize; k++){
      for (int j = 1; j <= uniSize; j++){
          universe[k*uniSize + j] = next[k*uniSize + j];
        }
    }

  paint(); //optimize this thing, it causes to redraw grid each time!!
}

bool GameScene::isAlive(int k, int j)     /// Fix rules to make field toroidal
{
  int power = 0;
  power += universe[(k+1)*uniSize +  j];
  power += universe[(k-1)*uniSize + j];
  power += universe[k*uniSize + (j+1)];
  power += universe[k*uniSize + (j-1)];
  power += universe[(k+1)*uniSize + ( j-1)];
  power += universe[(k-1)*uniSize + (j+1)];
  power += universe[(k-1)*uniSize + (j-1)];
  power += universe[(k+1)*uniSize +  (j+1)];
  if (((universe[k*uniSize + j] == true) && (power == 2)) || (power == 3))
    return true;
  return false;
}
