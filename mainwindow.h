#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMouseMovePoint(QPoint point);
    void onMouseClick(QPoint point);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
