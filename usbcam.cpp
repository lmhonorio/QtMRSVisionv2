#include "usbcam.hpp"

using namespace cv;

usbCam::usbCam()
{
    imageTimer = new QTimer(this);
    imageTimer->setInterval(1000/25);
    connect(imageTimer, SIGNAL(timeout()), this, SLOT(donextFrame()));

}


void usbCam::runUSBCamera()
{
    VideoCapture USBstream;
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


    mutex1->lock();
    if(USBstream.isOpened())
    {
        Mat framergb;
        Mat cameraFrame;
        USBstream.read(cameraFrame);
        newImage(cameraFrame);
    }
    else
    {
        USBstream.open(0);
    }
    mutex1->unlock();

}
