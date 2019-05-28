#ifndef STOCKVIEW_H
#define STOCKVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>

#include "stockinfo.h"
#include "klineitem.h"

class StockView: public QGraphicsView {
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
public:
    StockView(QWidget* parent = nullptr);

    void setStockInfo(StockBatchInfo batchInfo);

private:
    void initKLineItems();

signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);

private:
    QGraphicsScene* scene;
    StockBatchInfo baseInfo;
    int sceneWidth = 0, sceneHeight = 0;
    double eachItemSceneWidth;  // 每个Item在场景当中的宽度
    QRectF displayRect;

    QPoint moveStartPoint;

};

#endif // STOCKVIEW_H
