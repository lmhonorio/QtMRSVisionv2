#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QTimer>
#include <QMutex>
#include <QImage>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //void runUSBCamera(void);

    ~MainWindow();

public slots:
    void processImage(Mat image);
    void processIRImage(cv::Mat image);
    //void processIRQImage(QPixmap image);
    void fFindContours(Mat original, Mat* mcontours );
    void on_btok_clicked();
    void on_bFindCamera_clicked();
    void on_busbCam_clicked();
    void on_bLoadFlirConfig_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
