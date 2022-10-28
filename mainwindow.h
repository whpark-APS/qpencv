#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QImage>
#include <QPixmap>

#include "opencv2/opencv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QGraphicsScene m_scene;
    std::unique_ptr<QGraphicsPixmapItem> m_pixmapItem;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui{};
};
#endif // MAINWINDOW_H
