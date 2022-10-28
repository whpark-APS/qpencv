#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gsl/gsl"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


struct xWaitCursor {
    MainWindow& wndMain;
    QCursor cursorPrev;
    xWaitCursor(MainWindow& wndMain) : wndMain(wndMain), cursorPrev(wndMain.cursor()) {
        wndMain.setCursor(QCursor(Qt::WaitCursor));
    }
    ~xWaitCursor() {
        wndMain.setCursor(cursorPrev);
    }
};

void MainWindow::on_pushButton_clicked()
{
    xWaitCursor wc(*this);

    // Make Test Image
    static cv::Mat img;
    if (img.empty()) {
        if constexpr (true) {
            // color band
            img = cv::Mat::zeros(3'000, 4'000, CV_8UC3);
            img(cv::Rect{0, 0*img.rows/3, img.cols, img.rows/3}) = cv::Scalar(0, 0, 255);
            img(cv::Rect{0, 1*img.rows/3, img.cols, img.rows/3}) = cv::Scalar(0, 255, 0);
            img(cv::Rect{0, 2*img.rows/3, img.cols, img.rows/3}) = cv::Scalar(255, 0, 0);
        } else {
            // load from file
            img = cv::imread(R"(Z:\Images\차세대 IT 대면적\2022-09-29 IT\2022_09_29__16_09_59_camera2\LinescanImage.png)");
        }
    }

    QImage image{img.data, img.cols, img.rows, (qsizetype)(size_t)img.step, QImage::Format::Format_BGR888};

    if (m_pixmapItem) {
        m_scene.removeItem(m_pixmapItem.get());
    }
    m_pixmapItem.reset(m_scene.addPixmap(QPixmap::fromImage(std::move(image))));

    //m_scene.addRect({0, 0, 200, 200});
    //ui->graphicsView->fitInView(m_scene.sceneRect());
    ui->graphicsView->setScene(&m_scene);

}

