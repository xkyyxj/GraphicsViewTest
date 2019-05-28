#ifndef KLINEITEM_H
#define KLINEITEM_H

#include <QGraphicsItem>
#include <QRectF>

#include "stockinfo.h"

/**
 * KLineItem类，单根K线
 * 1. 需要传入QRectF类对象，代表区域
 */
class KLineItem: public QGraphicsItem {
public:
    KLineItem(QRectF, QWidget *parent = nullptr);

    void setItemInfo(StockInfo& info);

signals:
    void onClicked(StockInfo info);

protected:
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF rect;
    StockInfo itemInfo;
};

#endif // KLINEITEM_H
