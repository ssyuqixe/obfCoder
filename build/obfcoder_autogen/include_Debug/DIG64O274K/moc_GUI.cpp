/****************************************************************************
** Meta object code from reading C++ file 'GUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../inc/GUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI_t {
    QByteArrayData data[18];
    char stringdata0[380];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 0, 3), // "GUI"
QT_MOC_LITERAL(1, 4, 20), // "on_addButton_clicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 21), // "on_loadButton_clicked"
QT_MOC_LITERAL(4, 48, 21), // "on_saveButton_clicked"
QT_MOC_LITERAL(5, 70, 17), // "on_encBox_changed"
QT_MOC_LITERAL(6, 88, 17), // "on_delBox_changed"
QT_MOC_LITERAL(7, 106, 18), // "on_addJunk_changed"
QT_MOC_LITERAL(8, 125, 21), // "on_chgLoopBox_changed"
QT_MOC_LITERAL(9, 147, 20), // "on_chgVarBox_changed"
QT_MOC_LITERAL(10, 168, 21), // "on_openButton_clicked"
QT_MOC_LITERAL(11, 190, 23), // "on_JunkerSumBox_changed"
QT_MOC_LITERAL(12, 214, 23), // "on_JunkerSubBox_changed"
QT_MOC_LITERAL(13, 238, 23), // "on_JunkerMulBox_changed"
QT_MOC_LITERAL(14, 262, 29), // "on_JunkerConnectedBox_changed"
QT_MOC_LITERAL(15, 292, 33), // "on_JunkerSemiConnectedBox_cha..."
QT_MOC_LITERAL(16, 326, 29), // "on_JunkerNonConnected_changed"
QT_MOC_LITERAL(17, 356, 23) // "on_JunkerIncBox_changed"

    },
    "GUI\0on_addButton_clicked\0\0"
    "on_loadButton_clicked\0on_saveButton_clicked\0"
    "on_encBox_changed\0on_delBox_changed\0"
    "on_addJunk_changed\0on_chgLoopBox_changed\0"
    "on_chgVarBox_changed\0on_openButton_clicked\0"
    "on_JunkerSumBox_changed\0on_JunkerSubBox_changed\0"
    "on_JunkerMulBox_changed\0"
    "on_JunkerConnectedBox_changed\0"
    "on_JunkerSemiConnectedBox_changed\0"
    "on_JunkerNonConnected_changed\0"
    "on_JunkerIncBox_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_addButton_clicked(); break;
        case 1: _t->on_loadButton_clicked(); break;
        case 2: _t->on_saveButton_clicked(); break;
        case 3: _t->on_encBox_changed(); break;
        case 4: _t->on_delBox_changed(); break;
        case 5: _t->on_addJunk_changed(); break;
        case 6: _t->on_chgLoopBox_changed(); break;
        case 7: _t->on_chgVarBox_changed(); break;
        case 8: _t->on_openButton_clicked(); break;
        case 9: _t->on_JunkerSumBox_changed(); break;
        case 10: _t->on_JunkerSubBox_changed(); break;
        case 11: _t->on_JunkerMulBox_changed(); break;
        case 12: _t->on_JunkerConnectedBox_changed(); break;
        case 13: _t->on_JunkerSemiConnectedBox_changed(); break;
        case 14: _t->on_JunkerNonConnected_changed(); break;
        case 15: _t->on_JunkerIncBox_changed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject GUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_GUI.data,
    qt_meta_data_GUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
