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
    void mergeImages();
    void processImage(Mat image, qint64 timestamp);
    void processIRImage(cv::Mat image, qint64 timestamp);
    //void processIRQImage(QPixmap image);
    void fFindContours(Mat original, Mat* mcontours , double t1, double t2, int cameratype);
    void on_btok_clicked();
    void on_bFindCamera_clicked();
    void on_busbCam_clicked();
    void on_bLoadFlirConfig_clicked();

private slots:
    void on_qsliderIR1_valueChanged(int value);

    void on_qsliderIR2_valueChanged(int value);

    void on_qsliderUSB1_valueChanged(int value);

    void on_qsliderUSB2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
