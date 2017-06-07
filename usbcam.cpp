#include "usbcam.hpp"
#include <QTime>

using namespace cv;

usbCam::usbCam()
{
    imageTimer = new QTimer(this);
    imageTimer->setInterval(1000/25);
    connect(imageTimer, SIGNAL(timeout()), this, SLOT(donextFrame()));

    current = cv::Mat::zeros(640,512,CV_8UC3);

    USBstream.open(0);

}


void usbCam::runUSBCamera()
{
    //VideoCapture USBstream;
    USBstream.open(0);

    if (!USBstream.isOpened()) { //check if video device has been initialised
        std::cout << "cannot open camera";
        return;
    }

    //unconditional loop
    while (true) {
        Mat cameraFrame;
        USBstream.read(cameraFrame);
        imshow("cam", cameraFrame);
        if (waitKey(10) >= 0)
            break;
    }
}


void usbCam::donextFrame()
{

    timestamp = QDateTime().currentMSecsSinceEpoch();
    QString text;
    text.sprintf("%d",timestamp);

    QByteArray ba = text.toLatin1();
    const char *c_str2 = ba.data();
    int fontFace = FONT_HERSHEY_PLAIN;
    double fontScale = 2;
    int thickness = 3;
    int baseline=0;
    Size textSize = getTextSize(c_str2, fontFace,fontScale, thickness, &baseline);

    Point textOrg(5, 50);


    mutex1->lock();
    if(USBstream.isOpened())
    {
        Mat framergb;
        Mat cameraFrame;
        USBstream.read(cameraFrame);

        cv::Mat redImg;
        cv::Rect myROI(px, py, hx, hy);
        redImg = cameraFrame(myROI);

        cv::resize(redImg, redImg, cv::Size(640,512), 0, 0, CV_INTER_LINEAR);
        current = redImg.clone();
        putText(redImg, c_str2, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);




        newImage(redImg,timestamp);
        //newImage(cameraFrame);
    }
    else
    {
        USBstream.open(0);
    }
    mutex1->unlock();

}
