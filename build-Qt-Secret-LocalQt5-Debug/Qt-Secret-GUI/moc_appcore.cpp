/****************************************************************************
** Meta object code from reading C++ file 'appcore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Qt-Secret/Qt-Secret-GUI/appcore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appcore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppCore_t {
    QByteArrayData data[26];
    char stringdata0[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppCore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppCore_t qt_meta_stringdata_AppCore = {
    {
QT_MOC_LITERAL(0, 0, 7), // "AppCore"
QT_MOC_LITERAL(1, 8, 12), // "qmlOpenPopup"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "qmlClosePopup"
QT_MOC_LITERAL(4, 36, 15), // "wrkGenerateKeys"
QT_MOC_LITERAL(5, 52, 3), // "rsa"
QT_MOC_LITERAL(6, 56, 11), // "qmlShowKeys"
QT_MOC_LITERAL(7, 68, 6), // "pubKey"
QT_MOC_LITERAL(8, 75, 7), // "privKey"
QT_MOC_LITERAL(9, 83, 17), // "wrkEncryptMessage"
QT_MOC_LITERAL(10, 101, 7), // "message"
QT_MOC_LITERAL(11, 109, 17), // "wrkDecryptMessage"
QT_MOC_LITERAL(12, 127, 19), // "qmlShowEncDecResult"
QT_MOC_LITERAL(13, 147, 14), // "wrkSignMessage"
QT_MOC_LITERAL(14, 162, 12), // "wrkCheckSign"
QT_MOC_LITERAL(15, 175, 17), // "qmlShowSignResult"
QT_MOC_LITERAL(16, 193, 15), // "copyToClipboard"
QT_MOC_LITERAL(17, 209, 4), // "text"
QT_MOC_LITERAL(18, 214, 12), // "generateKeys"
QT_MOC_LITERAL(19, 227, 9), // "printKeys"
QT_MOC_LITERAL(20, 237, 17), // "getEncryptDecrypt"
QT_MOC_LITERAL(21, 255, 10), // "actionType"
QT_MOC_LITERAL(22, 266, 3), // "key"
QT_MOC_LITERAL(23, 270, 17), // "printEncDecResult"
QT_MOC_LITERAL(24, 288, 12), // "getSignCheck"
QT_MOC_LITERAL(25, 301, 15) // "printSignResult"

    },
    "AppCore\0qmlOpenPopup\0\0qmlClosePopup\0"
    "wrkGenerateKeys\0rsa\0qmlShowKeys\0pubKey\0"
    "privKey\0wrkEncryptMessage\0message\0"
    "wrkDecryptMessage\0qmlShowEncDecResult\0"
    "wrkSignMessage\0wrkCheckSign\0"
    "qmlShowSignResult\0copyToClipboard\0"
    "text\0generateKeys\0printKeys\0"
    "getEncryptDecrypt\0actionType\0key\0"
    "printEncDecResult\0getSignCheck\0"
    "printSignResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppCore[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    1,  101,    2, 0x06 /* Public */,
       6,    2,  104,    2, 0x06 /* Public */,
       9,    2,  109,    2, 0x06 /* Public */,
      11,    2,  114,    2, 0x06 /* Public */,
      12,    1,  119,    2, 0x06 /* Public */,
      13,    2,  122,    2, 0x06 /* Public */,
      14,    2,  127,    2, 0x06 /* Public */,
      15,    1,  132,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  135,    2, 0x0a /* Public */,
      18,    1,  138,    2, 0x0a /* Public */,
      19,    0,  141,    2, 0x0a /* Public */,
      20,    3,  142,    2, 0x0a /* Public */,
      23,    0,  149,    2, 0x0a /* Public */,
      24,    3,  150,    2, 0x0a /* Public */,
      25,    0,  157,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   10,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   21,   22,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   21,   22,   10,
    QMetaType::Void,

       0        // eod
};

void AppCore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppCore *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->qmlOpenPopup(); break;
        case 1: _t->qmlClosePopup(); break;
        case 2: _t->wrkGenerateKeys((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->qmlShowKeys((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 4: _t->wrkEncryptMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->wrkDecryptMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->qmlShowEncDecResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->wrkSignMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->wrkCheckSign((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->qmlShowSignResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->copyToClipboard((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->generateKeys((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->printKeys(); break;
        case 13: _t->getEncryptDecrypt((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 14: _t->printEncDecResult(); break;
        case 15: _t->getSignCheck((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 16: _t->printSignResult(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppCore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::qmlOpenPopup)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppCore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::qmlClosePopup)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::wrkGenerateKeys)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::qmlShowKeys)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::wrkEncryptMessage)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::wrkDecryptMessage)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::qmlShowEncDecResult)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::wrkSignMessage)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::wrkCheckSign)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AppCore::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppCore::qmlShowSignResult)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AppCore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AppCore.data,
    qt_meta_data_AppCore,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AppCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppCore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppCore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void AppCore::qmlOpenPopup()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AppCore::qmlClosePopup()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AppCore::wrkGenerateKeys(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AppCore::qmlShowKeys(QByteArray _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AppCore::wrkEncryptMessage(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AppCore::wrkDecryptMessage(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AppCore::qmlShowEncDecResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AppCore::wrkSignMessage(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AppCore::wrkCheckSign(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AppCore::qmlShowSignResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
