/****************************************************************************
** Meta object code from reading C++ file 'test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../oucLibrary/test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_test_t {
    QByteArrayData data[17];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_t qt_meta_stringdata_test = {
    {
QT_MOC_LITERAL(0, 0, 4), // "test"
QT_MOC_LITERAL(1, 5, 23), // "on_password_textChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "arg1"
QT_MOC_LITERAL(4, 35, 19), // "on_name_textChanged"
QT_MOC_LITERAL(5, 55, 20), // "on_email_textChanged"
QT_MOC_LITERAL(6, 76, 20), // "on_phone_textChanged"
QT_MOC_LITERAL(7, 97, 18), // "on_age_textChanged"
QT_MOC_LITERAL(8, 116, 21), // "on_c_password_clicked"
QT_MOC_LITERAL(9, 138, 17), // "on_c_name_clicked"
QT_MOC_LITERAL(10, 156, 16), // "on_c_sex_clicked"
QT_MOC_LITERAL(11, 173, 18), // "on_c_email_clicked"
QT_MOC_LITERAL(12, 192, 18), // "on_c_phone_clicked"
QT_MOC_LITERAL(13, 211, 16), // "on_c_age_clicked"
QT_MOC_LITERAL(14, 228, 18), // "on_confirm_clicked"
QT_MOC_LITERAL(15, 247, 17), // "on_cancel_clicked"
QT_MOC_LITERAL(16, 265, 10) // "deleteThis"

    },
    "test\0on_password_textChanged\0\0arg1\0"
    "on_name_textChanged\0on_email_textChanged\0"
    "on_phone_textChanged\0on_age_textChanged\0"
    "on_c_password_clicked\0on_c_name_clicked\0"
    "on_c_sex_clicked\0on_c_email_clicked\0"
    "on_c_phone_clicked\0on_c_age_clicked\0"
    "on_confirm_clicked\0on_cancel_clicked\0"
    "deleteThis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    1,   87,    2, 0x08 /* Private */,
       5,    1,   90,    2, 0x08 /* Private */,
       6,    1,   93,    2, 0x08 /* Private */,
       7,    1,   96,    2, 0x08 /* Private */,
       8,    0,   99,    2, 0x08 /* Private */,
       9,    0,  100,    2, 0x08 /* Private */,
      10,    0,  101,    2, 0x08 /* Private */,
      11,    0,  102,    2, 0x08 /* Private */,
      12,    0,  103,    2, 0x08 /* Private */,
      13,    0,  104,    2, 0x08 /* Private */,
      14,    0,  105,    2, 0x08 /* Private */,
      15,    0,  106,    2, 0x08 /* Private */,
      16,    0,  107,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
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

void test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        test *_t = static_cast<test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_password_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_name_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_email_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_phone_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_age_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_c_password_clicked(); break;
        case 6: _t->on_c_name_clicked(); break;
        case 7: _t->on_c_sex_clicked(); break;
        case 8: _t->on_c_email_clicked(); break;
        case 9: _t->on_c_phone_clicked(); break;
        case 10: _t->on_c_age_clicked(); break;
        case 11: _t->on_confirm_clicked(); break;
        case 12: _t->on_cancel_clicked(); break;
        case 13: _t->deleteThis(); break;
        default: ;
        }
    }
}

const QMetaObject test::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_test.data,
      qt_meta_data_test,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_test.stringdata0))
        return static_cast<void*>(const_cast< test*>(this));
    return QDialog::qt_metacast(_clname);
}

int test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
