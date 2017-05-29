#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flircamera.hpp"
#include <iostream>
#include <fstream>

#include <usbcam.hpp>

#include <QTimer>
#include<QWindow>
#include<QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QFileDialog>
#include <QMessageBox>
#include<QPixelFormat>
#include<QImage>
#include<QPixmap>


//CBaseGIGeCamera myGCam;
using namespace cv;
QMutex mutex1;

CFlirCamera* myFlir;
usbCam* myUSBcam;
RNG rng(12345);


void fFindContours(Mat original, Mat* mcontours )
{
    Mat canny_output, src_gray;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor( original, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Detect edges using canny

    Canny( src_gray, canny_output, 50, 100, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }

    *mcontours = drawing;

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qRegisterMetaType<cv::Mat>("cv::Mat");


    ui->setupUi(this);

    myFlir = new CFlirCamera();

    myUSBcam = new usbCam();
    myFlir->mutex = &mutex1;
    myUSBcam->mutex1 = &mutex1;

    connect(myUSBcam,SIGNAL(newImage(Mat)),this,SLOT(processImage(Mat)));
    //connect(myFlir,SIGNAL(newImage(cv::Mat)),this,SLOT(processIRImage(cv::Mat)));
    connect(myFlir,SIGNAL(sendPixmapImage(QPixmap)),this,SLOT(processIRQImage(QPixmap)));
    connect(myFlir,SIGNAL(sendMatImage(cv::Mat)),this,SLOT(processIRImage(cv::Mat)));


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btok_clicked()
{

    J_STATUS_TYPE   retval;

    myFlir->setHandler(&myFlir->m_hCamBase,16,1);
    myFlir->openStream(0, ui->imageContourUSBLabel );

    // Start Acquisition
    retval = J_Camera_ExecuteCommand(myFlir->m_hCamBase, NODE_NAME_ACQSTART);
    if (retval != J_ST_SUCCESS)
        qInfo("Could not initiate camera stream!\n");
    else
        qInfo("opening camera stream succeeded\n");


}


void MainWindow::processImage(Mat cameraFrame)
{
    Mat framergb;
    cv::cvtColor(cameraFrame, framergb, CV_RGB2BGR);
    QImage im = QImage((const unsigned char*) framergb.data, framergb.cols, framergb.rows, QImage::Format_RGB888);
    ui->ImageUSBLabel->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::processIRQImage(QPixmap image)
{

    ui->imageIRlabel->setPixmap(image);


     //ui->imagelabel->setPixmap(QPixmap::fromImage(image));

}


void MainWindow::processIRImage(cv::Mat Img_Iron)
{
//    qInfo("aqui");
//    imshow("iron8",Img_Iron);


    Mat framergb;
//    //fFindContours(Img_Iron, &framergb );
    cv::cvtColor(Img_Iron, framergb, CV_RGB2BGR);
    QImage im = QImage((const unsigned char*) framergb.data, framergb.cols, framergb.rows, QImage::Format_RGB888);
    ui->imageCountourIRlabel->setPixmap(QPixmap::fromImage(im));
}



void MainWindow::on_busbCam_clicked()
{

    if( myUSBcam->imageTimer->isActive() )
    {
        myUSBcam->imageTimer->stop();
    }
    else
    {
        myUSBcam->imageTimer->start(40);
    }
}




void MainWindow::on_bFindCamera_clicked()
{
    myFlir->OpenFactoryAndCamera();
    //myGCam.OpenFactoryAndCamera();
    ui->lb_cameraname->setText(myFlir->GetCameraName());

}

void MainWindow::on_bLoadFlirConfig_clicked()
{

    Mat imLena,framergb;
    imLena = imread("C:\\Users\\usuario\\Dropbox\\Projetos\\VisualProcessing\\Qtprojects\\QtMRSVision\\lena2.jpg",1);
    cv::cvtColor(imLena, framergb, CV_RGB2BGR);
    QImage im = QImage((uchar*) framergb.data, framergb.cols, framergb.rows, QImage::Format_RGB888);
    //imshow("iron8",imLena);
    ui->ImageUSBLabel->setPixmap(QPixmap::fromImage(im));

//    qInfo("conectando");
//    connect(myUSBcam,SIGNAL(newImage(cv::Mat)),this,SLOT(processImage(cv::Mat)));
//    connect(myFlir,SIGNAL(newImage(cv::Mat)),this,SLOT(processIRImage(cv::Mat)));

//    QFileDialog dialog;
//    QString fileName = "not configured";
//    dialog.setNameFilter(tr("Configuration Files (*.txt *.TXT)"));
//    dialog.setDirectory(tr(".\\"));

//    QMessageBox msgBox;


//    if (dialog.exec())
//    {
//         fileName = dialog.selectedFiles()[0];
//         QByteArray ba = fileName.toLatin1();
//         const char *c_str2 = ba.data();

//         J_STATUS_TYPE retval = J_Camera_LoadSettings(myFlir.m_hCamBase, reinterpret_cast<LPCWSTR> ("FlirA65settings.txt"),(J_LOAD_SETTINGS_FLAG)2);
//         if (retval != J_ST_SUCCESS)
//         {
//             msgBox.setText("Erro na leitura da configuração.");
//         }
//         else
//         {
//             msgBox.setText("Configuração carregada.");
//         }
//         msgBox.exec();
//    }

    return;
}
