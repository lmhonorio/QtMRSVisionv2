/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "processImage"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "Mat"
QT_MOC_LITERAL(4, 29, 5), // "image"
QT_MOC_LITERAL(5, 35, 14), // "processIRImage"
QT_MOC_LITERAL(6, 50, 7), // "cv::Mat"
QT_MOC_LITERAL(7, 58, 13), // "fFindContours"
QT_MOC_LITERAL(8, 72, 8), // "original"
QT_MOC_LITERAL(9, 81, 4), // "Mat*"
QT_MOC_LITERAL(10, 86, 9), // "mcontours"
QT_MOC_LITERAL(11, 96, 2), // "t1"
QT_MOC_LITERAL(12, 99, 2), // "t2"
QT_MOC_LITERAL(13, 102, 10), // "cameratype"
QT_MOC_LITERAL(14, 113, 15), // "on_btok_clicked"
QT_MOC_LITERAL(15, 129, 22), // "on_bFindCamera_clicked"
QT_MOC_LITERAL(16, 152, 18), // "on_busbCam_clicked"
QT_MOC_LITERAL(17, 171, 26), // "on_bLoadFlirConfig_clicked"
QT_MOC_LITERAL(18, 198, 26), // "on_qsliderIR1_valueChanged"
QT_MOC_LITERAL(19, 225, 5), // "value"
QT_MOC_LITERAL(20, 231, 26), // "on_qsliderIR2_valueChanged"
QT_MOC_LITERAL(21, 258, 27), // "on_qsliderUSB1_valueChanged"
QT_MOC_LITERAL(22, 286, 27) // "on_qsliderUSB2_valueChanged"

    },
    "MainWindow\0processImage\0\0Mat\0image\0"
    "processIRImage\0cv::Mat\0fFindContours\0"
    "original\0Mat*\0mcontours\0t1\0t2\0cameratype\0"
    "on_btok_clicked\0on_bFindCamera_clicked\0"
    "on_busbCam_clicked\0on_bLoadFlirConfig_clicked\0"
    "on_qsliderIR1_valueChanged\0value\0"
    "on_qsliderIR2_valueChanged\0"
    "on_qsliderUSB1_valueChanged\0"
    "on_qsliderUSB2_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       5,    1,   72,    2, 0x0a /* Public */,
       7,    5,   75,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    0,   87,    2, 0x0a /* Public */,
      16,    0,   88,    2, 0x0a /* Public */,
      17,    0,   89,    2, 0x0a /* Public */,
      18,    1,   90,    2, 0x08 /* Private */,
      20,    1,   93,    2, 0x08 /* Private */,
      21,    1,   96,    2, 0x08 /* Private */,
      22,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9, QMetaType::Double, QMetaType::Double, QMetaType::Int,    8,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processImage((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 1: _t->processIRImage((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 2: _t->fFindContours((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat*(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 3: _t->on_btok_clicked(); break;
        case 4: _t->on_bFindCamera_clicked(); break;
        case 5: _t->on_busbCam_clicked(); break;
        case 6: _t->on_bLoadFlirConfig_clicked(); break;
        case 7: _t->on_qsliderIR1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_qsliderIR2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_qsliderUSB1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_qsliderUSB2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
