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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btok;
    QLabel *imagelabel;
    QPushButton *bFindCamera;
    QLabel *lb_cameraname;
    QPushButton *busbCam;
    QLabel *usbImageLabel;
    QPushButton *bLoadFlirConfig;
    QLabel *usbContourLabel;
    QLabel *irContourLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(888, 777);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btok = new QPushButton(centralWidget);
        btok->setObjectName(QStringLiteral("btok"));
        btok->setGeometry(QRect(220, 680, 111, 31));
        imagelabel = new QLabel(centralWidget);
        imagelabel->setObjectName(QStringLiteral("imagelabel"));
        imagelabel->setGeometry(QRect(20, 10, 421, 321));
        imagelabel->setFrameShape(QFrame::Panel);
        imagelabel->setScaledContents(false);
        bFindCamera = new QPushButton(centralWidget);
        bFindCamera->setObjectName(QStringLiteral("bFindCamera"));
        bFindCamera->setGeometry(QRect(20, 680, 91, 31));
        lb_cameraname = new QLabel(centralWidget);
        lb_cameraname->setObjectName(QStringLiteral("lb_cameraname"));
        lb_cameraname->setGeometry(QRect(30, 660, 181, 21));
        busbCam = new QPushButton(centralWidget);
        busbCam->setObjectName(QStringLiteral("busbCam"));
        busbCam->setGeometry(QRect(760, 670, 111, 31));
        usbImageLabel = new QLabel(centralWidget);
        usbImageLabel->setObjectName(QStringLiteral("usbImageLabel"));
        usbImageLabel->setGeometry(QRect(450, 10, 421, 321));
        usbImageLabel->setFrameShape(QFrame::WinPanel);
        usbImageLabel->setFrameShadow(QFrame::Plain);
        usbImageLabel->setScaledContents(false);
        bLoadFlirConfig = new QPushButton(centralWidget);
        bLoadFlirConfig->setObjectName(QStringLiteral("bLoadFlirConfig"));
        bLoadFlirConfig->setGeometry(QRect(120, 680, 91, 31));
        usbContourLabel = new QLabel(centralWidget);
        usbContourLabel->setObjectName(QStringLiteral("usbContourLabel"));
        usbContourLabel->setGeometry(QRect(450, 340, 421, 311));
        usbContourLabel->setFrameShape(QFrame::Box);
        irContourLabel = new QLabel(centralWidget);
        irContourLabel->setObjectName(QStringLiteral("irContourLabel"));
        irContourLabel->setGeometry(QRect(20, 340, 421, 311));
        irContourLabel->setFrameShape(QFrame::Box);
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
        imagelabel->setText(QString());
        bFindCamera->setText(QApplication::translate("MainWindow", "PROCURAR", Q_NULLPTR));
        lb_cameraname->setText(QApplication::translate("MainWindow", "SEM CAMERAS ENCONTRADAS", Q_NULLPTR));
        busbCam->setText(QApplication::translate("MainWindow", "CONECTAR USB", Q_NULLPTR));
        usbImageLabel->setText(QString());
        bLoadFlirConfig->setText(QApplication::translate("MainWindow", "CONFIGURAR", Q_NULLPTR));
        usbContourLabel->setText(QString());
        irContourLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
