/****************************************************************************
** Meta object code from reading C++ file 'studentrecordsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../studentrecordsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'studentrecordsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StudentRecordsDialog_t {
    QByteArrayData data[8];
    char stringdata[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StudentRecordsDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StudentRecordsDialog_t qt_meta_stringdata_StudentRecordsDialog = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 21),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 21),
QT_MOC_LITERAL(4, 66, 22),
QT_MOC_LITERAL(5, 89, 21),
QT_MOC_LITERAL(6, 111, 23),
QT_MOC_LITERAL(7, 135, 30)
    },
    "StudentRecordsDialog\0on_buttonPrev_clicked\0"
    "\0on_buttonNext_clicked\0on_buttonWrite_clicked\0"
    "on_buttonSeek_clicked\0on_buttonDelete_clicked\0"
    "on_pushButtonAddRecord_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StudentRecordsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StudentRecordsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StudentRecordsDialog *_t = static_cast<StudentRecordsDialog *>(_o);
        switch (_id) {
        case 0: _t->on_buttonPrev_clicked(); break;
        case 1: _t->on_buttonNext_clicked(); break;
        case 2: _t->on_buttonWrite_clicked(); break;
        case 3: _t->on_buttonSeek_clicked(); break;
        case 4: _t->on_buttonDelete_clicked(); break;
        case 5: _t->on_pushButtonAddRecord_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject StudentRecordsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StudentRecordsDialog.data,
      qt_meta_data_StudentRecordsDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *StudentRecordsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StudentRecordsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StudentRecordsDialog.stringdata))
        return static_cast<void*>(const_cast< StudentRecordsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StudentRecordsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
