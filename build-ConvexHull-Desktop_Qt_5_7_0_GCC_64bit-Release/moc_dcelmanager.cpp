/****************************************************************************
** Meta object code from reading C++ file 'dcelmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ConvexHull/GUI/managers/dcelmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dcelmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DcelManager_t {
    QByteArrayData data[17];
    char stringdata0[435];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DcelManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DcelManager_t qt_meta_stringdata_DcelManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DcelManager"
QT_MOC_LITERAL(1, 12, 25), // "on_loadDcelButton_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 26), // "on_cleanDcelButton_clicked"
QT_MOC_LITERAL(4, 66, 25), // "on_saveDcelButton_clicked"
QT_MOC_LITERAL(5, 92, 37), // "on_wireframeDcelCheckBox_stat..."
QT_MOC_LITERAL(6, 130, 5), // "state"
QT_MOC_LITERAL(7, 136, 40), // "on_wireframeWidthDcelSlider_v..."
QT_MOC_LITERAL(8, 177, 5), // "value"
QT_MOC_LITERAL(9, 183, 35), // "on_wireframeColorDcelButton_c..."
QT_MOC_LITERAL(10, 219, 32), // "on_drawDcelCheckBox_stateChanged"
QT_MOC_LITERAL(11, 252, 32), // "on_pointsDcelRadioButton_toggled"
QT_MOC_LITERAL(12, 285, 7), // "checked"
QT_MOC_LITERAL(13, 293, 30), // "on_flatDcelRadioButton_toggled"
QT_MOC_LITERAL(14, 324, 32), // "on_smoothDcelRadioButton_toggled"
QT_MOC_LITERAL(15, 357, 37), // "on_vertexColorDcelRadioButton..."
QT_MOC_LITERAL(16, 395, 39) // "on_triangleColorDcelRadioButt..."

    },
    "DcelManager\0on_loadDcelButton_clicked\0"
    "\0on_cleanDcelButton_clicked\0"
    "on_saveDcelButton_clicked\0"
    "on_wireframeDcelCheckBox_stateChanged\0"
    "state\0on_wireframeWidthDcelSlider_valueChanged\0"
    "value\0on_wireframeColorDcelButton_clicked\0"
    "on_drawDcelCheckBox_stateChanged\0"
    "on_pointsDcelRadioButton_toggled\0"
    "checked\0on_flatDcelRadioButton_toggled\0"
    "on_smoothDcelRadioButton_toggled\0"
    "on_vertexColorDcelRadioButton_toggled\0"
    "on_triangleColorDcelRadioButton_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DcelManager[] = {

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
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    1,   77,    2, 0x08 /* Private */,
       7,    1,   80,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    1,   84,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      13,    1,   90,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,
      15,    1,   96,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,

       0        // eod
};

void DcelManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DcelManager *_t = static_cast<DcelManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_loadDcelButton_clicked(); break;
        case 1: _t->on_cleanDcelButton_clicked(); break;
        case 2: _t->on_saveDcelButton_clicked(); break;
        case 3: _t->on_wireframeDcelCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_wireframeWidthDcelSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_wireframeColorDcelButton_clicked(); break;
        case 6: _t->on_drawDcelCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pointsDcelRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_flatDcelRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_smoothDcelRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_vertexColorDcelRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_triangleColorDcelRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DcelManager::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_DcelManager.data,
      qt_meta_data_DcelManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DcelManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DcelManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DcelManager.stringdata0))
        return static_cast<void*>(const_cast< DcelManager*>(this));
    return QFrame::qt_metacast(_clname);
}

int DcelManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
