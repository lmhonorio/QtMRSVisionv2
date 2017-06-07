#include "flircamera.hpp"
#include <exception>
#include <QTime>


using namespace std;



CFlirCamera::CFlirCamera()
{
    p_Original = NULL;
    current = cv::Mat::zeros(640,512,CV_8UC3);
}

CFlirCamera::~CFlirCamera(void)
{



}

void CFlirCamera::setHandler(CAM_HANDLE *hCam, int idepth, int ichannels)
{
    m_hCam = hCam;
    NODE_HANDLE hNode;
    J_STATUS_TYPE   retval;

    i_depth = idepth;
    i_channels = ichannels;

    T.setUnit(CTemperature::Celsius);
    unit = "°C";

    p_Original = NULL;
    m_BufferInfo.pImageBuffer = NULL;
    m_hThread = NULL;



    //get R
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"R", &hNode);
    int64_t temp;
    J_Node_GetValueInt64(hNode,0,&temp);
    m_R = (int) temp;

    //get B
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"B", &hNode);
    J_Node_GetValueDouble(hNode,0,&m_B);

    //get F
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"F", &hNode);
    J_Node_GetValueDouble(hNode,0,&m_F);

    //get O
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"O", &hNode);
    J_Node_GetValueDouble(hNode,0,&m_O);

    //get Emissivity
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"ObjectEmissivity", &hNode);
    retval = J_Node_GetValueDouble(hNode,0,&m_Emissivity);

    //Atm Temperature
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"AtmosphericTemperature", &hNode);
    retval = J_Node_GetValueDouble(hNode,0,&m_AtmTemp);

    //Ambient Temperature
    J_Camera_GetNodeByName(*m_hCam, (int8_t*)"ReflectedTemperature", &hNode);
    retval = J_Node_GetValueDouble(hNode,0,&m_AtmTemp);


    m_WT = 573.0; // Default value high gain mode
    m_W4WT = 1542.0;
    m_ExtOptTemp = m_AmbTemp;
    m_ExtOptTransm = 1.0f; // default

    // For TAU cameras we need GUI code for editing these values
    m_ObjectDistance = 10.0; // Default
    m_RelHum = 0.7; // Default


    m_J1 = 1;
    m_J0 = 0;
    // Initiate spectral response
    m_X = 1.9;
    m_alpha1 = 0.006569;
    m_beta1 = -0.002276;
    m_alpha2 = 0.01262;
    m_beta2 = -0.00667;


    doUpdateCalcConst();
}




void CFlirCamera::StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo)
{
    CBaseGIGeCamera::StreamCBFunc(pAqImageInfo);
    HandleReceivedImage();
}



void CFlirCamera::HandleReceivedImage(void)
{




    cv::Mat imat_thermalSignal= cv::Mat(m_BufferInfo.iSizeX,m_BufferInfo.iSizeY, CV_16U );
    cv::Mat Img_8Bit_Gray(m_BufferInfo.iSizeX,m_BufferInfo.iSizeY,CV_8U);


    imat_thermalSignal = cv::cvarrToMat(p_Original);
    //cv::imshow("converted opencv",imat_thermalSignal);


    //find max and min values

    uint16_t minvalue = 99999999;
    uint16_t maxvalue = 0; //16000


    double sum=0;
    for(int i = 0; i < imat_thermalSignal.rows; i++)
    {
        const uint16_t* Mi = imat_thermalSignal.ptr<uint16_t>(i);
        for(int j = 0; j < imat_thermalSignal.cols; j++)
        {
            if (Mi[j] > maxvalue)
                maxvalue = Mi[j];
            if (Mi[j] > 500 && Mi[j] < minvalue)
                minvalue = Mi[j];
        }
    }

//    minvalue = (uint16_t)8000;
//    maxvalue = (uint16_t)10000;


    uint16_t spam = maxvalue - minvalue + 1;


    imat_thermalSignal.convertTo(Img_8Bit_Gray,CV_8U, 127.0/(maxvalue - minvalue), -minvalue * 127.0/(maxvalue - minvalue));

    //cv::imshow("IDC_OUTPICTURE",Img_8Bit_Gray);


    cv::Mat Img_Iron = cv::Mat::zeros(m_BufferInfo.iSizeY,m_BufferInfo.iSizeX,CV_8UC3);



    int channels = Img_Iron.channels();

    int nRows = Img_Iron.rows;
    int nCols = Img_Iron.cols ;


    if (Img_Iron.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    uchar* from;
    for( i = 0; i < nRows; ++i)
    {
        from = Img_8Bit_Gray.ptr<uchar>(i);
        p = Img_Iron.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            RGB_T c = iron[(int)floor(from[j])];
            //RGB_T gray[1] = {{(int)floor(from[j]),(int)floor(from[j]),(int)floor(from[j])}};
            //RGB_T c = gray[0];

            p[j*3+0] = c.b;
            p[j*3+1] = c.g;
            p[j*3+2] = c.r;
        }
    }

    T.setUnit(CTemperature::Celsius);
    T = TauToTemp(maxvalue/4);

    CTemperature Tmin;
    Tmin.setUnit(CTemperature::Celsius);
    Tmin = TauToTemp(minvalue/4);

    timestamp = QDateTime().currentMSecsSinceEpoch();

    QString text;
    text.sprintf("%.1f, %.1f, %d, %d", T.Value(),Tmin.Value(),(int)minvalue, (int)maxvalue);
    QByteArray ba = text.toLatin1();
    const char *c_str2 = ba.data();
    int fontFace = cv::FONT_HERSHEY_PLAIN;
    double fontScale = 1.5;
    int thickness = 2;
    int baseline=0;
    cv::Size textSize = cv::getTextSize(c_str2, fontFace,fontScale, thickness, &baseline);

    cv::Point textOrg(5, 50);

    //QString Sm;
    //Sm.Format(_T("%.1f C"),T.Value());
    //CW2A pszConvertedAnsiString (Sm);
    //std::string strStd (pszConvertedAnsiString);

    //QString(T.Value());

    //cv::putText(Img_8Bit_Gray, std::to_string(minvalue/4) + " " + std::to_string(spam/4)  + " real max = " + strStd  ,cv::Point2f(50,50), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(100,200,200,200),2);
    //cv::imshow("converted gray8",Img_8Bit_Gray);

    //MOSTRA A IMAGEM NO PICTUREBOX DA JANELA ATRAVES DO HANDLER
    //cv::imshow(windowsName,Img_Iron);
    //cv::imshow("iron8",Img_Iron);


    mutex->lock();
    cv::Mat redImg = Img_Iron;
    //cv::resize(Img_Iron, redImg, cv::Size(Img_Iron.cols * 0.5,Img_Iron.rows * 0.5), 0, 0, CV_INTER_LINEAR);
    //sendMatImage(Img_Iron);
    current = redImg.clone();
    putText(redImg, c_str2, textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness, 8);
    sendMatImage(redImg,timestamp);

    cv::waitKey(10);
    mutex->unlock();


    cv::waitKey(1);
}


J_STATUS_TYPE  CFlirCamera::openStream(uint32_t iChannel)
{

    uint32_t iBufferSize = getBufferSize();

    //setWindowHnd(newpbHnd, wndName, newusbpbHnd, wndusbName);
    J_STATUS_TYPE retval = J_Image_OpenStream(*m_hCam, 0, reinterpret_cast<J_IMG_CALLBACK_OBJECT>(this), reinterpret_cast<J_IMG_CALLBACK_FUNCTION>(&CFlirCamera::StreamCBFunc), &m_hThread, iBufferSize);

    if (retval != J_ST_SUCCESS) {
        qInfo("Could not open stream!\n");
        return retval;
    }
    qInfo("Opening stream succeeded\n");


    return retval;

}





//necessary B,R,O,F and powTobojSignal
float CFlirCamera::TauToTemp(USHORT sig)
{
    float T;
    double objSig;
    objSig = powToObjSig((double)sig);
    T = (float)(m_B / log(m_R /(objSig - m_O) + m_F));
    return T;
}


double CFlirCamera::powToObjSig(double dPow)
{
    return (m_K1 * dPow - m_K2);
}


void CFlirCamera::doUpdateCalcConst(void)
{
    m_AtmTao = doCalcAtmTao();

    m_K1 = doCalcK1();

    m_K2 = doCalcK2(tempToObjSig(m_AmbTemp),
        tempToObjSig(m_AtmTemp),
        tempToObjSig(m_ExtOptTemp));
}

double CFlirCamera::doCalcAtmTao(void)
{
    double tao, dtao;
    double H, T, sqrtD, X, a1, b1, a2, b2;
    double sqrtH2O;
    double TT;
    double a1b1sqH2O, a2b2sqH2O, exp1, exp2;
    CTemperature C(CTemperature::Celsius);

#define H2O_K1 +1.5587e+0
#define H2O_K2 +6.9390e-2
#define H2O_K3 -2.7816e-4
#define H2O_K4 +6.8455e-7
#define TAO_TATM_MIN -30.0
#define TAO_TATM_MAX  90.0
#define TAO_SQRTH2OMAX 6.2365
#define TAO_COMP_MIN 0.400
#define TAO_COMP_MAX 1.000

    H = m_RelHum;
    C = m_AtmTemp;
    T = C.Value();        // We need Celsius to use constants defined above
    sqrtD = sqrt(m_ObjectDistance);
    X  = m_X;
    a1 = m_alpha1;
    b1 = m_beta1;
    a2 = m_alpha2;
    b2 = m_beta2;

    if (T < TAO_TATM_MIN)
        T = TAO_TATM_MIN;
    else if (T > TAO_TATM_MAX)
        T = TAO_TATM_MAX;

    TT = T*T;

    sqrtH2O = sqrt(H*exp(H2O_K1 + H2O_K2*T + H2O_K3*TT + H2O_K4*TT*T));

    if ( sqrtH2O > TAO_SQRTH2OMAX )
        sqrtH2O = TAO_SQRTH2OMAX;

    a1b1sqH2O = (a1+b1*sqrtH2O);
    a2b2sqH2O = (a2+b2*sqrtH2O);
    exp1    = exp(-sqrtD*a1b1sqH2O);
    exp2    = exp(-sqrtD*a2b2sqH2O);

    tao     = X*exp1 + (1-X)*exp2;
    dtao    = -(a1b1sqH2O*X*exp1+a2b2sqH2O*(1-X)*exp2);
    // The real D-derivative is also divided by 2 and sqrtD.
    // Here we only want the sign of the slope! */

    if (tao < TAO_COMP_MIN)
        tao = TAO_COMP_MIN;      // below min value, clip

    else if (tao > TAO_COMP_MAX)
    {
        // check tao at 1 000 000 m dist
        tao  = X*exp(-(1.0E3)*a1b1sqH2O)+(1.0-X)*exp(-(1.0E3)*a2b2sqH2O);

        if ( tao > 1.0 )    // above max, staying up, assume \/-shape
            tao = TAO_COMP_MIN;
        else
            tao = TAO_COMP_MAX; // above max, going down, assume /\-shape
    }
    else if ( dtao > 0.0 && m_ObjectDistance > 0.0)
        tao = TAO_COMP_MIN;   // beween max & min, going up, assume \/

    // else between max & min, going down => OK as it is, ;-)

    return( tao);
}


double CFlirCamera::tempToObjSig(double dblKelvin)
{
    double objSign = 0.0;
    double dbl_reg = dblKelvin;

    // objSign = R / (exp(B/T) - F)

    if (dbl_reg > 0.0) {

        dbl_reg = m_B / dbl_reg;

        if (dbl_reg < EXP_SAFEGUARD) {
            dbl_reg = exp(dbl_reg);

            if (m_F <= 1.0) {
                if ( dbl_reg < ASY_SAFEGUARD )
                    dbl_reg = ASY_SAFEGUARD; // Don't get above a R/(1-F)
                // (horizontal) asymptote
            }
            else
            {
                // F > 1.0
                if ( dbl_reg < m_F*ASY_SAFEGUARD )
                    dbl_reg = m_F*ASY_SAFEGUARD;
                // Don't get too close to a B/ln(F) (vertical) asymptote
            }

            objSign = m_R/(dbl_reg - m_F);
        }
    }

    return( objSign);
}


double CFlirCamera::doCalcK1(void)
{
    double dblVal = 1.0;

    dblVal = m_AtmTao * m_Emissivity * m_ExtOptTransm;

    if (dblVal > 0.0)
        dblVal = 1/dblVal;

    return (dblVal);
}

double CFlirCamera::doCalcK2(double dAmbObjSig, double dAtmObjSig, double dExtOptTempObjSig)
{
    double emi;
    double temp1 = 0.0;
    double temp2 = 0.0;
    double temp3 = 0.0;

    emi  = m_Emissivity;

    if (emi > 0.0)
    {
        temp1 = (1.0 - emi)/emi * dAmbObjSig;

        if (m_AtmTao > 0.0) {
            temp2 = (1.0 - m_AtmTao)/(emi*m_AtmTao)* dAtmObjSig;

            if (m_ExtOptTransm > 0.0 && m_ExtOptTransm < 1.0) {
                temp3 = (1.0 - m_ExtOptTransm)/
                    (emi*m_AtmTao*m_ExtOptTransm)* dExtOptTempObjSig;
            }
        }
    }

    return (temp1 + temp2 + temp3);
}































//J_STATUS_TYPE  CFlirCamera::openStream(uint32_t iChannel,  uint32_t iBufferSize, HWND* pbHnd)
//{
//	hPicBox  = pbHnd;
//	cv::namedWindow("IDC_OUTPICTURE",1);
//	HWND hWnd = (HWND) cvGetWindowHandle("IDC_OUTPICTURE");
//	HWND hParent = ::GetParent(hWnd);
//     ::SetParent(hWnd, *hPicBox);
//     ::ShowWindow(hParent, SW_HIDE);
//	return J_Image_OpenStream(*m_hCam, 0, reinterpret_cast<J_IMG_CALLBACK_OBJECT>(this), reinterpret_cast<J_IMG_CALLBACK_FUNCTION>(&CFlirCamera::StreamCBFunc), &m_hThread, iBufferSize);
//
//}
//
//void CFlirCamera::StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo)
//{
//	int success=-1;
//
//	// We only want to create the OpenCV Image object once and we want to get the correct size from the Acquisition Info structure
//	if (p_Original == NULL)
//	{
//		SIZE	ViewSize;
//
//		ViewSize.cx = 800;
//		ViewSize.cy = 600;
//
//		uint64_t currentPixelFormat = pAqImageInfo->iPixelType;
//		uint64_t jaiPixelFormat = 0;
//		J_STATUS_TYPE iResult = J_Image_Get_PixelFormat(*m_hCam, currentPixelFormat, &jaiPixelFormat);
//
//
//
//		if(GC_ERR_SUCCESS != iResult)
//		{
//			OutputDebugString(_T("Error with J_Image_Get_PixelFormat in CStreamThread::StreamProcess ==> BUFFER_INFO_PIXELTYPE - assuming GVSP_PIX_MONO8.\n"));
//			pAqImageInfo->iPixelType = GVSP_PIX_MONO8;
//		}
//
//
//		p_Original = cvCreateImage(cvSize(pAqImageInfo->iSizeX,pAqImageInfo->iSizeY),  16, 1);
//
//
//	}
//
//	//create opencv c++ container
//	cv::Mat imat_thermalSignal= cv::Mat(pAqImageInfo->iSizeX,pAqImageInfo->iSizeY, CV_16U );
//
//
//	try
//	{
//		if (m_BufferInfo.pImageBuffer == NULL)
//		{
//			J_Image_Malloc(pAqImageInfo, &m_BufferInfo);
//		}
//		else
//		{
//			//convert bayer_extend to rgb jai format
//			success = J_Image_FromRawToImageEx(pAqImageInfo, &m_BufferInfo, BAYER_EXTEND);
//		}
//	}
//	catch(exception& e)
//	{
//		TRACE("RGB Image not created");
//	}
//
//
//
//
//	if(success == J_ST_SUCCESS)
//	{
//
//		//copy to opencv format
//		memcpy(p_Original->imageData,m_BufferInfo.pImageBuffer,p_Original->imageSize);
//		imat_thermalSignal = cv::cvarrToMat(p_Original);
//		//cv::imshow("converted opencv",imat_thermalSignal);
//
//
//		//find max and min values
//
//		uint16_t minvalue = 999999;
//		uint16_t maxvalue = 0; //16000
//
//
//		double sum=0;
//		for(int i = 0; i < imat_thermalSignal.rows; i++)
//		{
//			const uint16_t* Mi = imat_thermalSignal.ptr<uint16_t>(i);
//			for(int j = 0; j < imat_thermalSignal.cols; j++)
//			{
//				if (Mi[j] > maxvalue)
//					maxvalue = Mi[j];
//				if (Mi[j] > 500 && Mi[j] < minvalue)
//					minvalue = Mi[j];
//			}
//		}
//		uint16_t spam = maxvalue - minvalue + 1;
//
//
//		cv::Mat Img_8Bit_Gray(pAqImageInfo->iSizeX,pAqImageInfo->iSizeY,CV_8U);
//		imat_thermalSignal.convertTo(Img_8Bit_Gray,CV_8U, 127.0/(maxvalue - minvalue), -minvalue * 127.0/(maxvalue - minvalue));
//
//
//		cv::Mat Img_Iron = cv::Mat::zeros(pAqImageInfo->iSizeY,pAqImageInfo->iSizeX,CV_8UC3);
//
//		int channels = Img_Iron.channels();
//
//		int nRows = Img_Iron.rows;
//		int nCols = Img_Iron.cols ;
//
//		if (Img_Iron.isContinuous())
//		{
//			nCols *= nRows;
//			nRows = 1;
//		}
//
//		int i,j;
//		uchar* p;
//		uchar* from;
//		for( i = 0; i < nRows; ++i)
//		{
//			from = Img_8Bit_Gray.ptr<uchar>(i);
//			p = Img_Iron.ptr<uchar>(i);
//			for ( j = 0; j < nCols; ++j)
//			{
//				RGB_T c = iron[(int)floor(from[j])];
//				p[j*3+0] = c.b;
//				p[j*3+1] = c.g;
//				p[j*3+2] = c.r;
//			}
//		}
//
//		T.setUnit(CTemperature::Celsius);
//		T = TauToTemp(maxvalue/4);
//
//		CString Sm;
//		Sm.Format(_T("%.1f C"),T.Value());
//		CW2A pszConvertedAnsiString (Sm);
//		std::string strStd (pszConvertedAnsiString);
//
//
//		cv::putText(Img_8Bit_Gray, std::to_string(minvalue/4) + " " + std::to_string(spam/4)  + " real max = " + strStd  ,cv::Point2f(50,50), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(100,200,200,200),2);
//		cv::imshow("converted gray8",Img_8Bit_Gray);
//		cv::imshow("IDC_OUTPICTURE",Img_Iron);
//
//	}
//
//
//
//
//
//	try
//	{
//		//cvEqualizeHist(m_pImg,m_pOutputImg);
//
//	}
//	catch(exception& e)
//	{
//		TRACE(e.what());
//	}
//
//
//	//cvShowImage("Source", m_pImg);
//
//	//cv::imshow("output",output);
//	cv::waitKey(1);
//
//
//
//}
//

