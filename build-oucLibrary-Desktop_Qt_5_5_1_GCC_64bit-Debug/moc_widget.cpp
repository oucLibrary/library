/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../oucLibrary/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[21];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 10), // "initResult"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "index"
QT_MOC_LITERAL(4, 25, 5), // "query"
QT_MOC_LITERAL(5, 31, 13), // "login_success"
QT_MOC_LITERAL(6, 45, 8), // "username"
QT_MOC_LITERAL(7, 54, 8), // "password"
QT_MOC_LITERAL(8, 63, 3), // "num"
QT_MOC_LITERAL(9, 67, 8), // "Identify"
QT_MOC_LITERAL(10, 76, 2), // "id"
QT_MOC_LITERAL(11, 79, 6), // "logout"
QT_MOC_LITERAL(12, 86, 10), // "showResult"
QT_MOC_LITERAL(13, 97, 4), // "page"
QT_MOC_LITERAL(14, 102, 12), // "chooseChange"
QT_MOC_LITERAL(15, 115, 10), // "returnBook"
QT_MOC_LITERAL(16, 126, 10), // "deleteUser"
QT_MOC_LITERAL(17, 137, 8), // "addUsers"
QT_MOC_LITERAL(18, 146, 14), // "QList<QString>"
QT_MOC_LITERAL(19, 161, 4), // "list"
QT_MOC_LITERAL(20, 166, 9) // "addBorrow"

    },
    "Widget\0initResult\0\0index\0query\0"
    "login_success\0username\0password\0num\0"
    "Identify\0id\0logout\0showResult\0page\0"
    "chooseChange\0returnBook\0deleteUser\0"
    "addUsers\0QList<QString>\0list\0addBorrow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x09 /* Protected */,
       1,    0,   82,    2, 0x29 /* Protected | MethodCloned */,
       4,    0,   83,    2, 0x09 /* Protected */,
       5,    4,   84,    2, 0x09 /* Protected */,
      11,    0,   93,    2, 0x09 /* Protected */,
      12,    1,   94,    2, 0x09 /* Protected */,
      12,    0,   97,    2, 0x29 /* Protected | MethodCloned */,
      14,    1,   98,    2, 0x09 /* Protected */,
      14,    0,  101,    2, 0x29 /* Protected | MethodCloned */,
      15,    0,  102,    2, 0x09 /* Protected */,
      16,    0,  103,    2, 0x09 /* Protected */,
      17,    1,  104,    2, 0x09 /* Protected */,
      20,    1,  107,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, 0x80000000 | 9,    6,    7,    8,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->initResult(); break;
        case 2: _t->query(); break;
        case 3: _t->login_success((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< Identify(*)>(_a[4]))); break;
        case 4: _t->logout(); break;
        case 5: _t->showResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->showResult(); break;
        case 7: _t->chooseChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->chooseChange(); break;
        case 9: _t->returnBook(); break;
        case 10: _t->deleteUser(); break;
        case 11: _t->addUsers((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 12: _t->addBorrow((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
