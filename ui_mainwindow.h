/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btok;
    QLabel *imageIRlabel;
    QPushButton *bFindCamera;
    QLabel *lb_cameraname;
    QPushButton *busbCam;
    QLabel *ImageUSBLabel;
    QPushButton *bLoadFlirConfig;
    QLabel *imageContourUSBLabel;
    QLabel *imageCountourIRlabel;
    QSlider *qsliderUSB1;
    QSlider *qsliderUSB2;
    QSlider *qsliderIR1;
    QSlider *qsliderIR2;
    QLabel *qtextIR1;
    QLabel *qtextIR2;
    QLabel *qtextUSB1;
    QLabel *qtextUSB2;
    QPushButton *btoffgige;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(888, 796);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btok = new QPushButton(centralWidget);
        btok->setObjectName(QStringLiteral("btok"));
        btok->setGeometry(QRect(220, 700, 111, 31));
        imageIRlabel = new QLabel(centralWidget);
        imageIRlabel->setObjectName(QStringLiteral("imageIRlabel"));
        imageIRlabel->setGeometry(QRect(20, 10, 401, 301));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageIRlabel->sizePolicy().hasHeightForWidth());
        imageIRlabel->setSizePolicy(sizePolicy);
        imageIRlabel->setFrameShape(QFrame::Panel);
        imageIRlabel->setScaledContents(true);
        bFindCamera = new QPushButton(centralWidget);
        bFindCamera->setObjectName(QStringLiteral("bFindCamera"));
        bFindCamera->setGeometry(QRect(20, 700, 91, 31));
        lb_cameraname = new QLabel(centralWidget);
        lb_cameraname->setObjectName(QStringLiteral("lb_cameraname"));
        lb_cameraname->setGeometry(QRect(30, 680, 181, 21));
        busbCam = new QPushButton(centralWidget);
        busbCam->setObjectName(QStringLiteral("busbCam"));
        busbCam->setGeometry(QRect(760, 690, 111, 31));
        ImageUSBLabel = new QLabel(centralWidget);
        ImageUSBLabel->setObjectName(QStringLiteral("ImageUSBLabel"));
        ImageUSBLabel->setGeometry(QRect(450, 10, 421, 301));
        ImageUSBLabel->setFrameShape(QFrame::WinPanel);
        ImageUSBLabel->setFrameShadow(QFrame::Plain);
        ImageUSBLabel->setScaledContents(true);
        bLoadFlirConfig = new QPushButton(centralWidget);
        bLoadFlirConfig->setObjectName(QStringLiteral("bLoadFlirConfig"));
        bLoadFlirConfig->setGeometry(QRect(120, 700, 91, 31));
        imageContourUSBLabel = new QLabel(centralWidget);
        imageContourUSBLabel->setObjectName(QStringLiteral("imageContourUSBLabel"));
        imageContourUSBLabel->setGeometry(QRect(450, 320, 421, 301));
        imageContourUSBLabel->setFrameShape(QFrame::Box);
        imageContourUSBLabel->setScaledContents(true);
        imageCountourIRlabel = new QLabel(centralWidget);
        imageCountourIRlabel->setObjectName(QStringLiteral("imageCountourIRlabel"));
        imageCountourIRlabel->setGeometry(QRect(20, 320, 401, 301));
        imageCountourIRlabel->setFrameShape(QFrame::Box);
        imageCountourIRlabel->setScaledContents(false);
        qsliderUSB1 = new QSlider(centralWidget);
        qsliderUSB1->setObjectName(QStringLiteral("qsliderUSB1"));
        qsliderUSB1->setGeometry(QRect(490, 630, 160, 16));
        qsliderUSB1->setMaximum(400);
        qsliderUSB1->setValue(185);
        qsliderUSB1->setOrientation(Qt::Horizontal);
        qsliderUSB2 = new QSlider(centralWidget);
        qsliderUSB2->setObjectName(QStringLiteral("qsliderUSB2"));
        qsliderUSB2->setGeometry(QRect(660, 630, 160, 16));
        qsliderUSB2->setMaximum(400);
        qsliderUSB2->setValue(161);
        qsliderUSB2->setOrientation(Qt::Horizontal);
        qsliderIR1 = new QSlider(centralWidget);
        qsliderIR1->setObjectName(QStringLiteral("qsliderIR1"));
        qsliderIR1->setGeometry(QRect(60, 630, 160, 16));
        qsliderIR1->setMaximum(400);
        qsliderIR1->setValue(279);
        qsliderIR1->setOrientation(Qt::Horizontal);
        qsliderIR2 = new QSlider(centralWidget);
        qsliderIR2->setObjectName(QStringLiteral("qsliderIR2"));
        qsliderIR2->setGeometry(QRect(230, 630, 160, 16));
        qsliderIR2->setMaximum(400);
        qsliderIR2->setValue(207);
        qsliderIR2->setOrientation(Qt::Horizontal);
        qtextIR1 = new QLabel(centralWidget);
        qtextIR1->setObjectName(QStringLiteral("qtextIR1"));
        qtextIR1->setGeometry(QRect(120, 650, 47, 13));
        qtextIR2 = new QLabel(centralWidget);
        qtextIR2->setObjectName(QStringLiteral("qtextIR2"));
        qtextIR2->setGeometry(QRect(270, 650, 47, 13));
        qtextUSB1 = new QLabel(centralWidget);
        qtextUSB1->setObjectName(QStringLiteral("qtextUSB1"));
        qtextUSB1->setGeometry(QRect(550, 650, 47, 13));
        qtextUSB2 = new QLabel(centralWidget);
        qtextUSB2->setObjectName(QStringLiteral("qtextUSB2"));
        qtextUSB2->setGeometry(QRect(710, 650, 47, 13));
        btoffgige = new QPushButton(centralWidget);
        btoffgige->setObjectName(QStringLiteral("btoffgige"));
        btoffgige->setGeometry(QRect(340, 700, 111, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 888, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MRS VISION SYSTEM", Q_NULLPTR));
        btok->setText(QApplication::translate("MainWindow", "CONECTAR GIGe", Q_NULLPTR));
        imageIRlabel->setText(QString());
        bFindCamera->setText(QApplication::translate("MainWindow", "PROCURAR", Q_NULLPTR));
        lb_cameraname->setText(QApplication::translate("MainWindow", "SEM CAMERAS ENCONTRADAS", Q_NULLPTR));
        busbCam->setText(QApplication::translate("MainWindow", "CONECTAR USB", Q_NULLPTR));
        ImageUSBLabel->setText(QString());
        bLoadFlirConfig->setText(QApplication::translate("MainWindow", "CONFIGURAR", Q_NULLPTR));
        imageContourUSBLabel->setText(QString());
        imageCountourIRlabel->setText(QString());
        qtextIR1->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        qtextIR2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        qtextUSB1->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        qtextUSB2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        btoffgige->setText(QApplication::translate("MainWindow", "DESCONECTAR GIGe", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
