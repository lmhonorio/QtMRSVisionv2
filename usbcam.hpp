#ifndef USBCAM_H
#define USBCAM_H

#include <QObject>
#include <QTimer>
#include <QMutex>


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/compat.hpp>

using namespace cv;

class usbCam : public QObject
{
    Q_OBJECT

public:
    usbCam();
    QTimer* imageTimer;
    QMutex* mutex1;
    cv::VideoCapture USBstream;
    void runUSBCamera(void);

public slots:
    void donextFrame();

signals:
    void newImage(Mat image);
};

#endif // USBCAM_H
