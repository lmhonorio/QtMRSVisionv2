
#include "basegigecamera.hpp"
#include <exception>
#include <QImage>

using namespace std;


CBaseGIGeCamera::CBaseGIGeCamera(void)
{
}

CBaseGIGeCamera::CBaseGIGeCamera(int i)
{
    i = i+1;
}


CBaseGIGeCamera::~CBaseGIGeCamera(void)
{
}

uint32_t CBaseGIGeCamera::getBufferSize(void)
{
    J_STATUS_TYPE   retval;

    int64_t int64Val;
    int64_t pixelFormat;

    SIZE	ViewSize;


        //// Get Width from the camera
    retval = J_Camera_GetValueInt64(*m_hCam, NODE_NAME_WIDTH, &int64Val);
    ViewSize.cx = (LONG)int64Val;     // Set window size cx

    retval = J_Camera_GetValueInt64(*m_hCam, NODE_NAME_HEIGHT, &int64Val);
    ViewSize.cy = (LONG)int64Val;     // Set window size cy

    retval = J_Camera_GetValueInt64(*m_hCam, NODE_NAME_PIXELFORMAT, &int64Val);

    pixelFormat = int64Val;
    int bpp = J_BitsPerPixel(pixelFormat);

    return (ViewSize.cx*ViewSize.cy*bpp)/8;
}

void CBaseGIGeCamera::setWindowHnd(HWND*  newpbHnd, std::string wndName,  HWND* newUSBpbHnd, std::string usb_wndName)
{

        usb_windowsName = usb_wndName;
        usb_hPicBox = newUSBpbHnd;
        cv::namedWindow(usb_wndName, 1);
        const char * c = usb_wndName.c_str();
        HWND husbWnd = (HWND)cvGetWindowHandle(c);
 //       HWND husbParent = ::GetParent(husbWnd);
//        ::SetParent(husbWnd, *usb_hPicBox);
//        ::ShowWindow(husbParent, SW_HIDE);

        windowsName = wndName;
        hPicBox = newpbHnd;
        cv::namedWindow(wndName, 1);
        const char * d = wndName.c_str();
        HWND hWnd = (HWND)cvGetWindowHandle(d);
 //       HWND hParent = ::GetParent(hWnd);
//        ::SetParent(hWnd, *hPicBox);
//        ::ShowWindow(hParent, SW_HIDE);


}

void CBaseGIGeCamera::StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo)
{
    int success=-1;

    // We only want to create the OpenCV Image object once and we want to get the correct size from the Acquisition Info structure
    if (p_Original == NULL)
    {
        SIZE	ViewSize;

        ViewSize.cx = 800;
        ViewSize.cy = 600;

        uint64_t currentPixelFormat = pAqImageInfo->iPixelType;
        uint64_t jaiPixelFormat = 0;
        J_STATUS_TYPE iResult = J_Image_Get_PixelFormat(*m_hCam, currentPixelFormat, &jaiPixelFormat);


        if(GC_ERR_SUCCESS != iResult)
        {
            //OutputDebugString("Error with J_Image_Get_PixelFormat in CStreamThread::StreamProcess ==> BUFFER_INFO_PIXELTYPE - assuming GVSP_PIX_MONO8.\n");
            pAqImageInfo->iPixelType = GVSP_PIX_MONO8;
        }


        p_Original = cvCreateImage(cvSize(pAqImageInfo->iSizeX,pAqImageInfo->iSizeY),  i_depth, i_channels);


    }


    try
    {
        if (m_BufferInfo.pImageBuffer == NULL)
        {
            J_Image_Malloc(pAqImageInfo, &m_BufferInfo);
        }
        else
        {
            //convert bayer_extend to rgb jai format
            success = J_Image_FromRawToImageEx(pAqImageInfo, &m_BufferInfo, BAYER_EXTEND);
            if(success == J_ST_SUCCESS)
                memcpy(p_Original->imageData,m_BufferInfo.pImageBuffer,p_Original->imageSize);

        }
    }
    catch(exception& e)
    {
        qInfo("Image not created");
    }




}

QString CBaseGIGeCamera::GetCameraName()
{
    J_STATUS_TYPE   retval;
    NODE_HANDLE hNode;
    char buff[80];
    uint32_t iSize = sizeof(buff);
    retval = J_Camera_GetNodeByName(m_hCamBase, NODE_NAME_MODELNAME, &hNode);
    retval = J_Node_GetValueString(hNode, 0, (int8_t*)buff, &iSize);
    QString name = QString(buff);

    return name;

}



bool CBaseGIGeCamera::OpenFactoryAndCamera()
{
    J_STATUS_TYPE   retval;
    uint32_t        iSize;
    uint32_t        iNumDev;
    bool8_t         bHasChange;

    m_bEnableStreaming = false;

    // Open factory
    retval = J_Factory_Open((const int8_t *)"" , &m_hFactory);
    if (retval != J_ST_SUCCESS)
    {
        ShowErrorMsg(QString("Could not open factory!"), retval);
        return FALSE;
    }
    qInfo("Opening factory succeeded\n");

    //Update camera list
    retval = J_Factory_UpdateCameraList(m_hFactory, &bHasChange);
    if (retval != J_ST_SUCCESS)
    {
        ShowErrorMsg(QString("Could not update camera list!"), retval);
        return FALSE;
    }
    qInfo("Updating camera list succeeded\n");

    // Get the number of Cameras
    retval = J_Factory_GetNumOfCameras(m_hFactory, &iNumDev);
    if (retval != J_ST_SUCCESS)
    {
        ShowErrorMsg(QString("Could not get the number of cameras!"), retval);
        return FALSE;
    }

    if (iNumDev == 0)
    {
        ShowErrorMsg(QString("Invalid number of cameras!"), retval);
        return FALSE;
    }
    qInfo("%d cameras were found\n", iNumDev);

    // Get camera ID
    iSize = (uint32_t)sizeof(m_sCameraId);
    retval = J_Factory_GetCameraIDByIndex(m_hFactory, 0, m_sCameraId, &iSize);
    if (retval != J_ST_SUCCESS)
    {
        ShowErrorMsg(QString("Could not get the camera ID!"), retval);
        return FALSE;
    }
    qInfo("Camera ID: %s\n", m_sCameraId);


    // Open camera
    retval = J_Camera_Open(m_hFactory, m_sCameraId, &m_hCamBase);
    if (retval != J_ST_SUCCESS)
    {
        ShowErrorMsg(QString("Could not open the camera!"), retval);
        return FALSE;
    }

    //Make sure streaming is supported!
    uint32_t numStreams = 0;
    retval = J_Camera_GetNumOfDataStreams(m_hCamBase, &numStreams);
    if (retval != J_ST_SUCCESS)
    {
        ShowErrorMsg(QString("Error with J_Camera_GetNumOfDataStreams."), retval);
        return FALSE;
    }

    if(0 == numStreams)
    {
        m_bEnableStreaming = false;
    }
    else
    {
        m_bEnableStreaming = true;
    }

    if(iNumDev > 0 && m_hCamBase != 0)
    {
        qInfo("Opening camera succeeded\n");
    }
    else
    {
        ShowErrorMsg(QString("Invalid number of Devices!"), iNumDev);
        return FALSE;
    }

    return TRUE;
}

void CBaseGIGeCamera::ShowErrorMsg(QString message, J_STATUS_TYPE error)
{
    QString errorMsg;
//    errorMsg.
//    errorMsg.Format(_T("%s: Error = %d: "), message, error);

    switch(error)
    {
    case J_ST_INVALID_BUFFER_SIZE:	errorMsg += "Invalid buffer size ";	                break;
    case J_ST_INVALID_HANDLE:		errorMsg += "Invalid handle ";		                break;
    case J_ST_INVALID_ID:			errorMsg += "Invalid ID ";			                break;
    case J_ST_ACCESS_DENIED:		errorMsg += "Access denied ";		                break;
    case J_ST_NO_DATA:				errorMsg += "No data ";				                break;
    case J_ST_ERROR:				errorMsg += "Generic error ";		                break;
    case J_ST_INVALID_PARAMETER:	errorMsg += "Invalid parameter ";	                break;
    case J_ST_TIMEOUT:				errorMsg += "Timeout ";				                break;
    case J_ST_INVALID_FILENAME:		errorMsg += "Invalid file name ";	                break;
    case J_ST_INVALID_ADDRESS:		errorMsg += "Invalid address ";		                break;
    case J_ST_FILE_IO:				errorMsg += "File IO error ";		                break;
    case J_ST_GC_ERROR:				errorMsg += "GenICam error ";		                break;
    case J_ST_VALIDATION_ERROR:		errorMsg += "Settings File Validation Error ";		break;
    case J_ST_VALIDATION_WARNING:	errorMsg += "Settings File Validation Warning ";    break;
    }

    //AfxMessageBox(errorMsg, MB_OKCANCEL | MB_ICONINFORMATION);

}


int64_t CBaseGIGeCamera::getInt64NodeValue(int8_t* nodeName, desiredValue dValue)
{
    NODE_HANDLE hNode;
    int64_t int64Val;
    //const char *cnodename = reinterpret_cast<char*> (nodeName);
    //std::string snomename(cnodename);


    BOOL retval = J_Camera_GetNodeByName(m_hCamBase, nodeName, &hNode);
    if (retval == J_ST_SUCCESS)
    {
        // Get/Set
        if (dValue == desiredValue::vMin)
            retval = J_Node_GetMinInt64(hNode, &int64Val);
        if (dValue == desiredValue::vMax)
            retval = J_Node_GetMaxInt64(hNode, &int64Val);
        if (dValue == desiredValue::vCurrent)
            retval = J_Node_GetValueInt64(hNode, false, &int64Val);
        if (dValue == desiredValue::Vinc)
            retval = J_Node_GetInc(hNode, &int64Val);

        return int64Val;
    }
    else
    {
        ShowErrorMsg(QString("Could not get node:" ), retval);

        return -1;
    }
}


void CBaseGIGeCamera::CloseStream()
{
    if(!m_bEnableStreaming)
    {
        return;
    }

    if (m_hCamBase) {
        //J_Camera_ExecuteCommand(m_hCamBase, NODE_NAME_ACQSTOP);
    }

    if (m_hCam)
    {
        // Close camera
        //J_Camera_ExecuteCommand(m_hCam, NODE_NAME_ACQSTOP);
        J_Camera_Close(m_hCam);
        m_hCam = NULL;
        //TRACE("Closed camera\n");
    }




    try
    {
        if (m_hThread) {
            //J_Image_CloseStream(m_hThread);
            //m_hThread = NULL;

        }
    }
    catch (exception e)
    {

    }


    return;





    //ReleaseImage();
}

void CBaseGIGeCamera::ReleaseImage()
{
    cvReleaseImage(&p_Original);
}
