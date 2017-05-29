//QT include
#include "ui_mainwindow.h"

#include <QObject>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/compat.hpp>

#include <jai_factory.h>
#include <VLib.h>

#include<qstring.h>

#include "QMutex"
#include <QThread>
#include <QImage>

#define NODE_NAME_WIDTH						(int8_t*)"Width"
#define NODE_NAME_HEIGHT					(int8_t*)"Height"
#define NODE_NAME_PIXELFORMAT				(int8_t*)"PixelFormat"
#define NODE_NAME_GAIN						(int8_t*)"GainRaw"
#define NODE_NAME_ACQSTART					(int8_t*)"AcquisitionStart"
#define NODE_NAME_ACQSTOP					(int8_t*)"AcquisitionStop"

#define NODE_NAME_CURRENTIP					(int8_t*)"GevCurrentIPAddress"
#define NODE_NAME_MODELNAME					(int8_t*)"DeviceModelName"
#define NODE_NAME_TEMPERATURELINEARMODE		(int8_t*)"TemperatureLinearMode"
#define NODE_NAME_CAMERAOPTIONS				(int8_t*)"CameraOptions"
#define NODE_NAME_ACQSTOP					(int8_t*)"AcquisitionStop"


class CBaseGIGeCamera: public QObject
{
    Q_OBJECT

public:
    CBaseGIGeCamera();
    CBaseGIGeCamera(int i);
   ~CBaseGIGeCamera(void);

    typedef enum {
        vMin = 1,
        vMax,
        vCurrent,
        Vinc
    } desiredValue;


   // __event void OnEventRaised(std::string* message);

        //methods related with generic GIGe Cameras
    CAM_HANDLE			m_hCamBase;
    CAM_HANDLE			*m_hCam;
    FACTORY_HANDLE		m_hFactory;     // Factory Handle
    IplImage			*p_Original;
    J_tIMAGE_INFO		m_BufferInfo;
    THRD_HANDLE			m_hThread;      // Acquisition Thread Handle
    int					i_depth, i_channels;
    std::string			windowsName;
    std::string			usb_windowsName;


    //variables related to USB3 camera
    cv::VideoCapture USBstream;



    int8_t          m_sCameraId[J_CAMERA_ID_SIZE];    // Camera ID


    int64_t			m_iWidthInc;
    int64_t			m_iHeightInc;
    bool			m_bEnableStreaming;

    uint32_t getBufferSize(void);

    bool OpenFactoryAndCamera(void);

    void ShowErrorMsg(QString message, J_STATUS_TYPE error);

    void setWindowHnd(HWND* newpbHnd, std::string windowsName, HWND* newUSBpbHnd, std::string usb_windowsName );

    void CloseStream(void);

    void ReleaseImage(void);

    QString GetCameraName(void);


    int64_t getInt64NodeValue(int8_t* nodeName, desiredValue dValue);


    //handles streaming images
    virtual void StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo);

    virtual void HandleReceivedImage(void){}

signals:
    //void sendPixmapImage(QPixmap img);
    void sendMatImage(cv::Mat img);

protected:
    HWND* hPicBox;
    HWND* usb_hPicBox;
};


