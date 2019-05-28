#include "stockview.h"
#include <QMouseEvent>
#include <iostream>

StockView::StockView(QWidget* parent): QGraphicsView (parent){
    eachItemSceneWidth = 0;
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void StockView::mouseMoveEvent(QMouseEvent* event) {
    QPoint point = event->pos();
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}

void StockView::mouseClickEvent(QMouseEvent* event) {
    QPoint point = event->pos();
    moveStartPoint = point;
    emit mouseClicked(point);
    QGraphicsView::mousePressEvent(event);
}

void StockView::keyPressEvent(QKeyEvent *event) {
    QPoint currPoint(this->width() / 2, this->height() / 2);
    QPointF retPoint = this->mapToScene(currPoint);
    QTransform transform;
    switch(event->key()) {
    case Qt::Key_Down:
        this->scale(1 - 0.1, 1 - 0.1);
        break;
    case Qt::Key_Up:
        this->scale(1 + 0.1, 1 + 0.1);
        break;
    case Qt::Key_Left:
        retPoint.setX(retPoint.x() - 500);
        //this->setSceneRect(currRect);
        this->translate(-eachItemSceneWidth, 0);
        //this->centerOn(retPoint);
        break;
    case Qt::Key_Right:
        currPoint = QPoint();
        retPoint = QPointF();
        transform.translate(100,100);
        this->setTransform(transform);
        break;
    }
}

void StockView::setStockInfo(StockBatchInfo batchInfo) {
    baseInfo = batchInfo;
    // QGraphicsScene的长宽由需要展示的条目数决定
    sceneWidth = baseInfo.info_list.size() * 10;
    float maxPrice = 0, minPrice = 10000;
    if(baseInfo.info_list.size() > 0) {
        // 计算一下最高价和最低价
        for(int i = 0;i < baseInfo.info_list.size();i++) {
            minPrice = minPrice > baseInfo.info_list[i].low ? baseInfo.info_list[i].low : minPrice;
            maxPrice = maxPrice < baseInfo.info_list[i].high ? baseInfo.info_list[i].high : maxPrice;
        }
    }

    // 最小变动价格单位为分，每分显示一个像素，需要结合考虑QGraphicsView的高度，以保证能够正好容纳到一个窗口当中
    sceneHeight = static_cast<int>((maxPrice - minPrice) * 100);
    QRectF rect(0, 0, sceneWidth, sceneHeight);
    scene = new QGraphicsScene(rect);
    this->setScene(scene);

    // 下面一行是关键，避免显示滚动条
    this->setStyleSheet("padding:0px;border:0px");
    initKLineItems();
}

void StockView::initKLineItems() {

    // 计算一下最高最低价的价差
    float minPrice = 100000, maxPrice = 0, delta = 0;;
    for(int i = 0;i < baseInfo.info_list.size();i++) {
        minPrice = minPrice > baseInfo.info_list[i].low ? baseInfo.info_list[i].low : minPrice;
        maxPrice = maxPrice < baseInfo.info_list[i].high ? baseInfo.info_list[i].high : maxPrice;
    }
    delta = maxPrice - minPrice;

    double eachWidth = sceneWidth / (baseInfo.info_list.size() > 0 ? baseInfo.info_list.size() : 1);
    eachItemSceneWidth = eachWidth;
    if(baseInfo.info_list.size() > 0) {
        for(int i = 0;i < baseInfo.info_list.size();i++) {
            // 计算一下该根K线的顶部距离是多少，以及该根K线的高度
            double top = (maxPrice - baseInfo.info_list[i].high) / delta * sceneHeight;
            double height = (baseInfo.info_list[i].high - baseInfo.info_list[i].low) / delta * sceneHeight;
            QRectF tempRect(i * eachWidth, top, eachWidth, height);
            KLineItem* item = new KLineItem(tempRect);
            StockInfo info;
            info.low = baseInfo.info_list[i].low;
            info.high = baseInfo.info_list[i].high;
            info.open = baseInfo.info_list[i].open;
            info.close = baseInfo.info_list[i].close;
            item->setItemInfo(info);
            item->setPos(i * eachWidth + eachWidth / 2, 0);
            scene->addItem(item);
        }
    }

    // 设置一下显示区域
    QRectF displayRect(sceneWidth - this->width(), sceneHeight - this->height(), this->width(), this->height());
    //this->setSceneRect(displayRect);
    this->displayRect = displayRect;
}
