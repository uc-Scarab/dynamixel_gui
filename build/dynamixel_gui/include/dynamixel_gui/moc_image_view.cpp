/****************************************************************************
** Meta object code from reading C++ file 'image_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/dynamixel_gui/include/dynamixel_gui/image_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'image_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dynamixel_gui__DynamixelGUI_t {
    QByteArrayData data[19];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dynamixel_gui__DynamixelGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dynamixel_gui__DynamixelGUI_t qt_meta_stringdata_dynamixel_gui__DynamixelGUI = {
    {
QT_MOC_LITERAL(0, 0, 27), // "dynamixel_gui::DynamixelGUI"
QT_MOC_LITERAL(1, 28, 15), // "updateTopicList"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 14), // "onTopicChanged"
QT_MOC_LITERAL(4, 60, 5), // "index"
QT_MOC_LITERAL(5, 66, 7), // "onZoom1"
QT_MOC_LITERAL(6, 74, 7), // "checked"
QT_MOC_LITERAL(7, 82, 14), // "onDynamicRange"
QT_MOC_LITERAL(8, 97, 9), // "saveImage"
QT_MOC_LITERAL(9, 107, 18), // "updateNumGridlines"
QT_MOC_LITERAL(10, 126, 14), // "onMousePublish"
QT_MOC_LITERAL(11, 141, 11), // "onMouseLeft"
QT_MOC_LITERAL(12, 153, 1), // "x"
QT_MOC_LITERAL(13, 155, 1), // "y"
QT_MOC_LITERAL(14, 157, 17), // "onPubTopicChanged"
QT_MOC_LITERAL(15, 175, 20), // "onHideToolbarChanged"
QT_MOC_LITERAL(16, 196, 4), // "hide"
QT_MOC_LITERAL(17, 201, 12), // "onRotateLeft"
QT_MOC_LITERAL(18, 214, 13) // "onRotateRight"

    },
    "dynamixel_gui::DynamixelGUI\0updateTopicList\0"
    "\0onTopicChanged\0index\0onZoom1\0checked\0"
    "onDynamicRange\0saveImage\0updateNumGridlines\0"
    "onMousePublish\0onMouseLeft\0x\0y\0"
    "onPubTopicChanged\0onHideToolbarChanged\0"
    "hide\0onRotateLeft\0onRotateRight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dynamixel_gui__DynamixelGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x09 /* Protected */,
       3,    1,   75,    2, 0x09 /* Protected */,
       5,    1,   78,    2, 0x09 /* Protected */,
       7,    1,   81,    2, 0x09 /* Protected */,
       8,    0,   84,    2, 0x09 /* Protected */,
       9,    0,   85,    2, 0x09 /* Protected */,
      10,    1,   86,    2, 0x09 /* Protected */,
      11,    2,   89,    2, 0x09 /* Protected */,
      14,    0,   94,    2, 0x09 /* Protected */,
      15,    1,   95,    2, 0x09 /* Protected */,
      17,    0,   98,    2, 0x09 /* Protected */,
      18,    0,   99,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dynamixel_gui::DynamixelGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DynamixelGUI *_t = static_cast<DynamixelGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateTopicList(); break;
        case 1: _t->onTopicChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onZoom1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onDynamicRange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->saveImage(); break;
        case 5: _t->updateNumGridlines(); break;
        case 6: _t->onMousePublish((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onMouseLeft((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->onPubTopicChanged(); break;
        case 9: _t->onHideToolbarChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onRotateLeft(); break;
        case 11: _t->onRotateRight(); break;
        default: ;
        }
    }
}

const QMetaObject dynamixel_gui::DynamixelGUI::staticMetaObject = {
    { &rqt_gui_cpp::Plugin::staticMetaObject, qt_meta_stringdata_dynamixel_gui__DynamixelGUI.data,
      qt_meta_data_dynamixel_gui__DynamixelGUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *dynamixel_gui::DynamixelGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dynamixel_gui::DynamixelGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dynamixel_gui__DynamixelGUI.stringdata0))
        return static_cast<void*>(this);
    return rqt_gui_cpp::Plugin::qt_metacast(_clname);
}

int dynamixel_gui::DynamixelGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rqt_gui_cpp::Plugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
