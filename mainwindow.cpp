#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "klineitem.h"

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(scene);*/

    /*QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-50, -50, 100, 100);
    item->setPos(0,0);
    scene->addItem(item);*/
    QGraphicsEllipseItem* item;

    QSqlDatabase defaultDatabase = QSqlDatabase::addDatabase("QMYSQL");
    defaultDatabase.setHostName("localhost");
    defaultDatabase.setDatabaseName("stock");
    defaultDatabase.setUserName("root");
    defaultDatabase.setPassword("123");
    defaultDatabase.open();

    StockBatchInfo batchInfo;
    QSqlQuery query;
    QString querySql("select * from stock_base_info where ts_code=? and trade_date>'20181001' and trade_date<'20181010'");
    query.prepare(querySql);
    query.addBindValue(QVariant("000001.SZ"));
    query.exec();
    batchInfo.addSingleDayInfos(query);

    ui->graphicsView->setStockInfo(batchInfo);

    connect(ui->graphicsView, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(onMouseMovePoint(QPoint)));

}

void MainWindow::onMouseMovePoint(QPoint point) {
    std::cout << "on Mouse move Event" << std::endl;
    std::cout << point.x() << std::endl;
}

void MainWindow::onMouseClick(QPoint point) {

}

MainWindow::~MainWindow()
{
    delete ui;
}
