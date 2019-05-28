#include "klineitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

KLineItem::KLineItem(QRectF rect, QWidget* parent) {
    this->rect = rect;
    setFlags(QGraphicsItem::ItemIsSelectable);
}

QRectF KLineItem::boundingRect()const {
    return rect;
}

void KLineItem::setItemInfo(StockInfo& info) {
    itemInfo = info;
}

void KLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 判定用什么颜色的画笔
    QPen pen;
    QColor color;
    if(itemInfo.close > itemInfo.open) {
        color.setRgb(217, 58, 24);
    }
    else {
        color.setRgb(7, 122, 50);
    }
    pen.setColor(color);
    painter->setPen(pen);

    float delta = itemInfo.high - itemInfo.low;
    double width = rect.width(), height = rect.height(), x = rect.x(), y = rect.y();

    // 计算并绘制上影线部分
    float up_delta = itemInfo.high - (itemInfo.open > itemInfo.close ? itemInfo.open : itemInfo.close);
    float up_pct = up_delta / delta;
    float up_start_x, up_start_y, up_end_y;
    up_start_x = x + width / 2;
    up_start_y = y;
    up_end_y = y + static_cast<int>(height * up_pct);
    QLine upLine(up_start_x, up_start_y, up_start_x, up_end_y);
    painter->drawLine(upLine);

    //计算并绘制实体部分
    float main_delta = itemInfo.open > itemInfo.close ? itemInfo.open - itemInfo.close : itemInfo.close - itemInfo.open;
    float main_pct = main_delta / delta;
    float main_start_y = up_end_y, mainHeight = static_cast<int>(main_pct * height);
    QRect mainRect(x, main_start_y, width, mainHeight);
    painter->drawRect(mainRect);
    if(itemInfo.close < itemInfo.open) {
        painter->fillRect(mainRect, color);
    }

    // 计算并绘制下影线部分
    float down_start_y = main_start_y + mainHeight, down_end_y = y + height;
    QLine downLine(up_start_x, down_start_y, up_start_x, down_end_y);
    painter->drawLine(downLine);
}

void KLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        std::cout << "left clicked" << std::endl;
    }
}
