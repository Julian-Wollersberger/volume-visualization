/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[17];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 7), // "cleanup"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 19), // "volumeTextureLoaded"
QT_MOC_LITERAL(4, 38, 7), // "Volume*"
QT_MOC_LITERAL(5, 46, 6), // "volume"
QT_MOC_LITERAL(6, 53, 7), // "paintGL"
QT_MOC_LITERAL(7, 61, 12), // "initializeGL"
QT_MOC_LITERAL(8, 74, 8), // "resizeGL"
QT_MOC_LITERAL(9, 83, 1), // "w"
QT_MOC_LITERAL(10, 85, 1), // "h"
QT_MOC_LITERAL(11, 87, 11), // "fileChanged"
QT_MOC_LITERAL(12, 99, 4), // "path"
QT_MOC_LITERAL(13, 104, 17), // "addFilesToWatcher"
QT_MOC_LITERAL(14, 122, 19), // "handleLoggedMessage"
QT_MOC_LITERAL(15, 142, 19), // "QOpenGLDebugMessage"
QT_MOC_LITERAL(16, 162, 3) // "msg"

    },
    "GLWidget\0cleanup\0\0volumeTextureLoaded\0"
    "Volume*\0volume\0paintGL\0initializeGL\0"
    "resizeGL\0w\0h\0fileChanged\0path\0"
    "addFilesToWatcher\0handleLoggedMessage\0"
    "QOpenGLDebugMessage\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    1,   55,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x09 /* Protected */,
       7,    0,   59,    2, 0x09 /* Protected */,
       8,    2,   60,    2, 0x09 /* Protected */,
      11,    1,   65,    2, 0x09 /* Protected */,
      13,    0,   68,    2, 0x09 /* Protected */,
      14,    1,   69,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cleanup(); break;
        case 1: _t->volumeTextureLoaded((*reinterpret_cast< Volume*(*)>(_a[1]))); break;
        case 2: _t->paintGL(); break;
        case 3: _t->initializeGL(); break;
        case 4: _t->resizeGL((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->fileChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->addFilesToWatcher(); break;
        case 7: _t->handleLoggedMessage((*reinterpret_cast< const QOpenGLDebugMessage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_GLWidget.data,
    qt_meta_data_GLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
