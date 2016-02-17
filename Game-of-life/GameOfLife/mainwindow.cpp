#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //asm ("movl $1, %eax");

  game = new GameScene();
  ui->graphicsView->setScene(game);

  ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->viewport()->installEventFilter(this);
  ui->graphicsView->viewport()->setMouseTracking(true);

  connect(ui->numberOfCells, SIGNAL(valueChanged(int)), game, SLOT(setUniSize(int)));
  connect(ui->clearButton, SIGNAL(pressed()), game, SLOT(clearUniverse()));
  connect(ui->stopButton, SIGNAL(pressed()), game, SLOT(stopUniverse()));
  connect(ui->startButton, SIGNAL(pressed()), game, SLOT(startUniverse()));
  connect(game, SIGNAL(gameEnds(bool)), this, SLOT(stopMessage()));
  connect(ui->gridButton, SIGNAL(pressed()), game, SLOT(raiseGridFlag()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
  if (event->type() == QEvent::Resize)
    {
      QResizeEvent *res = reinterpret_cast<QResizeEvent*>(event);
      game->setViewSize(res->size().width(),
                        res->size().height());
      return true;
    }

  if (event->type() == QEvent::MouseMove)
    {
      //qDebug() << event;
      return true;
    }

  if (event->type() == QEvent::MouseButtonPress)
    {
      qDebug() << event;
      /*QResizeEvent *res = reinterpret_cast<QResizeEvent*>(event);    -- bad, bad!
      game->setViewSize(res->size().width(),
                        res->size().height());                */
      game->alterCellValue(ui->graphicsView->mapFromGlobal(QCursor::pos()));
      return true;
    }

  if (event->type() == QEvent::Paint)
    {
      //qDebug() << event;
    }
  return false;
}

void MainWindow::stopMessage()
{
  QMessageBox::information(this,
                           tr("Game Over"),
                           tr("The End. Following generations will stay the same."),
                           QMessageBox::Ok);
}
