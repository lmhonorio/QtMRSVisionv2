#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flircamera.hpp"
#include <iostream>
#include <fstream>

#include <usbcam.hpp>
#include <exception>

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
using namespace std;

QMutex mutex1;
QTimer* mergeTime;
CFlirCamera* myFlir;
usbCam* myUSBcam;
RNG rng(12345);



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qRegisterMetaType<cv::Mat>("cv::Mat");


    ui->setupUi(this);

    myFlir = new CFlirCamera();
    myUSBcam = new usbCam();


    myUSBcam->hx = 279;
    myUSBcam->hy = 207;
    myUSBcam->px = 185;
    myUSBcam->py = 161;

    ui->qsliderIR1->setValue(myUSBcam->px);
    ui->qsliderIR2->setValue(myUSBcam->py);
    ui->qsliderUSB1->setValue(myUSBcam->hx);
    ui->qsliderUSB2->setValue(myUSBcam->hx);


//    ui->qtextIR1->setText(QString::number(ui->qsliderIR1->value()));
//    ui->qtextIR2->setText(QString::number(ui->qsliderIR2->value()));

//    ui->qtextUSB1->setText(QString::number(ui->qsliderUSB1->value()));
//    ui->qtextUSB2->setText(QString::number(ui->qsliderUSB2->value()));

    ui->qtextIR1->setText(QString::number(myUSBcam->hx));
    ui->qtextIR2->setText(QString::number(myUSBcam->hy));

    ui->qtextUSB1->setText(QString::number(myUSBcam->px));
    ui->qtextUSB2->setText(QString::number(myUSBcam->py));

    myFlir->mutex = &mutex1;
    myUSBcam->mutex1 = &mutex1;

    connect(myUSBcam,SIGNAL(newImage(Mat,qint64)),this,SLOT(processImage(Mat,qint64)));
    connect(myFlir,SIGNAL(sendMatImage(cv::Mat,qint64)),this,SLOT(processIRImage(cv::Mat,qint64)));

    mergeTime = new QTimer(this);
    mergeTime->setInterval(1000/25);
    connect(mergeTime, SIGNAL(timeout()), this, SLOT(mergeImages()));





}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btok_clicked()
{

    J_STATUS_TYPE   retval;

    myFlir->setHandler(&myFlir->m_hCamBase,16,1);
    myFlir->openStream(0);

    // Start Acquisition
    retval = J_Camera_ExecuteCommand(myFlir->m_hCamBase, NODE_NAME_ACQSTART);
    if (retval != J_ST_SUCCESS)
        qInfo("Could not initiate camera stream!\n");
    else
        qInfo("opening camera stream succeeded\n");


}

void MainWindow::fFindContours(Mat original, Mat* mcontours, double t1, double t2, int cameratype )
{
    Mat canny_output, src_gray;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    cvtColor( original, src_gray, CV_BGR2GRAY );
    Mat ccolour;

    if(cameratype==1)
    {
        Canny( src_gray, canny_output, t1, t2, 3 );
    //    imshow("ircanny",canny_output);
    }
    else
    {
        blur( src_gray, src_gray, Size(5,5));
        Canny( src_gray, canny_output, t1, t2, 3 );
      //  imshow("usbcanny",canny_output);
    }


    cvtColor(canny_output,ccolour,CV_GRAY2BGR);
    // imshow("usb",ccolour);

    *mcontours = ccolour;

}


void MainWindow::processImage(Mat cameraFrame, qint64 timestamp)
{
    int thr1 = ui->qsliderUSB1->value();
    int thr2 = ui->qsliderUSB2->value();

    Mat framergb, irContours, irBGR;
    cv::cvtColor(cameraFrame, framergb, CV_RGB2BGR);
    QImage im = QImage((const unsigned char*) framergb.data, framergb.cols, framergb.rows, QImage::Format_RGB888);
    ui->ImageUSBLabel->setPixmap(QPixmap::fromImage(im));


    //blending 2 images
    //double alpha = 0.5; double beta = 0.5; double input = 0.5;
    //Mat blended, blendedBBR;


    //addWeighted( myUSBcam->current, alpha, myFlir->current, beta, 0.0, blended);
    //cv::cvtColor(blended, blendedBBR, CV_RGB2BGR);
    //QImage im2 = QImage((const unsigned char*) blendedBBR.data, blendedBBR.cols, blendedBBR.rows, QImage::Format_RGB888);
    //ui->imageContourUSBLabel->setPixmap(QPixmap::fromImage(im2));


    //cv::cvtColor(irContours, irBGR, CV_RGB2BGR);
    //cv::cvtColor(myUSBcam->current, irBGR, CV_RGB2BGR);
    //QImage im2 = QImage((const unsigned char*) irBGR.data, irBGR.cols, irBGR.rows, QImage::Format_RGB888);
    //ui->imageContourUSBLabel->setPixmap(QPixmap::fromImage(im2));

}



void MainWindow::processIRImage(cv::Mat Img_Iron, qint64 timestamp)
{


    Mat framergb, irContours, iRGBContours;

    //show imagem original
    cv::cvtColor(Img_Iron, framergb, CV_RGB2BGR);
    QImage im = QImage((const unsigned char*) framergb.data, framergb.cols, framergb.rows, QImage::Format_RGB888);
    ui->imageIRlabel->setPixmap(QPixmap::fromImage(im));



    //show contorno
//    int thr1 = ui->qsliderIR1->value();
//    int thr2 = ui->qsliderIR2->value();
//    fFindContours(Img_Iron, &irContours, thr1, thr2,1 );
//    cv::cvtColor(irContours, iRGBContours, CV_RGB2BGR);
//    QImage imr = QImage((const unsigned char*) iRGBContours.data, iRGBContours.cols, iRGBContours.rows, QImage::Format_RGB888);
//    ui->imageCountourIRlabel->setPixmap(QPixmap::fromImage(imr));
}



void MainWindow::on_busbCam_clicked()
{

    if( myUSBcam->imageTimer->isActive() )
    {
        myUSBcam->imageTimer->stop();
        mergeTime->stop();
    }
    else
    {
        myUSBcam->imageTimer->start(40);
        mergeTime->start(100);
    }
}

void MainWindow::mergeImages()
{



    //blending 2 images
    double alpha = 0.5; double beta = 0.5; double input = 0.5;
    Mat blended, blendedBBR;


    mutex1.lock();
    addWeighted( myUSBcam->current, alpha, myFlir->current, beta, 0.0, blended);
    mutex1.unlock();

    cv::cvtColor(blended, blendedBBR, CV_RGB2BGR);
    QImage im2 = QImage((const unsigned char*) blendedBBR.data, blendedBBR.cols, blendedBBR.rows, QImage::Format_RGB888);
    ui->imageContourUSBLabel->setPixmap(QPixmap::fromImage(im2));


    //cv::cvtColor(irContours, irBGR, CV_RGB2BGR);
    //cv::cvtColor(myUSBcam->current, irBGR, CV_RGB2BGR);
    //QImage im2 = QImage((const unsigned char*) irBGR.data, irBGR.cols, irBGR.rows, QImage::Format_RGB888);
    //ui->imageContourUSBLabel->setPixmap(QPixmap::fromImage(im2));



}




void MainWindow::on_bFindCamera_clicked()
{
    myFlir->OpenFactoryAndCamera();
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

void MainWindow::on_qsliderIR1_valueChanged(int value)
{
    myUSBcam->hx = value;
    ui->qtextIR1->setText(QString::number(value));
}

void MainWindow::on_qsliderIR2_valueChanged(int value)
{
    myUSBcam->hy = value;
    ui->qtextIR2->setText(QString::number(value));
}

void MainWindow::on_qsliderUSB1_valueChanged(int value)
{
    myUSBcam->px = value;
    ui->qtextUSB1->setText(QString::number(value));
}

void MainWindow::on_qsliderUSB2_valueChanged(int value)
{
    myUSBcam->py = value;
    ui->qtextUSB2->setText(QString::number(value));
}
